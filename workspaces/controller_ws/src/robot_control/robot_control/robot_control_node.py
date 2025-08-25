import numpy as np
import math

from enum import Enum

import rclpy
from rclpy.action import ActionClient
from rclpy.node import Node
from rclpy.qos import QoSProfile, HistoryPolicy, ReliabilityPolicy, DurabilityPolicy

import cv2

from cv_bridge import CvBridge

from sensor_msgs.msg import Image

from robot_interfaces.msg import Odometry, Velocity, Angle, Command

from robot_interfaces.action import Planner

class CLIENT_STATES(Enum):
    IDLE = 0
    IN_PROGRESS = 1
    SUCCESS = 2
    FAIL = 3

class CONTROLLER_STATES(Enum):
    SLEEP = 0
    MISSION_IN_PROGRESS = 1
    
class RobotControlNode(Node):
    def __init__(self):
        super().__init__("robot_control_node")

###################################################################################################
        self.bridge = CvBridge()
        self.img = None
        self.state = CONTROLLER_STATES.SLEEP
        self.robot_position = Odometry(x=0, y=0, theta=0)
        self.robot_velocity = Velocity(linear_velocity=0, angular_velocity=0)
        self.robot_servo_angle = Angle(angle=0.0)
        self.rubble = []
###################################################################################################

###################################################################################################
        self.path_planning_action_client_state = CLIENT_STATES.IDLE
        self.path_planning_action_client = ActionClient(self, Planner, 'path_planning_action')
        self.path_planning_action_client
###################################################################################################
    
###################################################################################################
        self.robot_velocity_publisher = self.create_publisher(
            Velocity, 
            'robot_velocity', 
            10
        )        
        self.robot_velocity_publisher
        

        self.robot_servo_angle_publisher = self.create_publisher(
            Angle, 
            'servo_angle', 
            10
        )        
        self.robot_servo_angle_publisher
###################################################################################################

###################################################################################################
        video_qos_profile = QoSProfile(
            history=HistoryPolicy.KEEP_LAST, 
            reliability=ReliabilityPolicy.BEST_EFFORT, 
            durability=DurabilityPolicy.VOLATILE, 
            depth=1
        )

        self.image_subscription = self.create_subscription(
            Image,
            'processed_image',
            self.image_callback,
            video_qos_profile)
        self.image_subscription  # prevent unused variable warning

        self.robot_position_subscription = self.create_subscription(
            Odometry,
            'robot_position',
            self.robot_position_callback,
            10
        )
        self.robot_position_subscription


        self.robot_command_subscription = self.create_subscription(
            Command,
            'robot_command',
            self.robot_command_callback,
            10
        )
        self.robot_position_subscription
###################################################################################################

###################################################################################################
    def run(self):
        while True:
            rclpy.spin_once(self, timeout_sec=1)
            #self.get_logger().info(f'{self.state}')
            self.get_logger().info(f'{self.state}')
            match self.state:
                case CONTROLLER_STATES.MISSION_IN_PROGRESS:
                    self.mission()
                case _:
                    continue


    def detect_rubble(self):

        binary_img = self.img         

        grid_rows = binary_img.shape[0]
        grid_cols = binary_img.shape[1]
        
        #invert image
        inverted_binary_img = cv2.bitwise_not(binary_img)
        
        inverted_binary_img_no_robot = self.remove_rectangle_from_matrix(inverted_binary_img, (self.robot_position.x, self.robot_position.y), 200, 200, self.robot_position.theta)

        '''
        padding = 40
        cv2.rectangle(inverted_binary_img_no_robot,(0,0),(padding,grid_cols),255,-1)
        cv2.rectangle(inverted_binary_img_no_robot,(grid_rows - padding,0),(grid_rows,grid_cols),255,-1)
        cv2.rectangle(inverted_binary_img_no_robot,(0,0),(grid_rows, padding),255,-1)
        cv2.rectangle(inverted_binary_img_no_robot,(0,grid_cols - padding),(grid_rows, grid_cols),255,-1)
        '''

        #find contours
        contours, _ = cv2.findContours(inverted_binary_img_no_robot, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        img_copy = cv2.cvtColor(inverted_binary_img_no_robot, cv2.COLOR_GRAY2BGR)
        cv2.drawContours(img_copy, contours, -1, (0, 255, 0), 2)       
        # loop through contours
        for index in range(len(contours)):
            self.get_logger().info(f'{index}')
            # take contour
            cnt=contours[index]
            # find coordinates
            x,y,w,h = cv2.boundingRect(cnt)
            # if object is rubble
            if w < 30 and h < 30:
                self.get_logger().info(f'{x}, {y}')
                self.rubble.append([[int(x), int(y), 0], [int(x), int(y), 0]])
        '''
        cv2.imshow('i', img_copy)
        cv2.waitKey(0)
        '''

        for r in self.rubble:
            dx = 0
            dy = 0
            if r[1][0] > (grid_cols / 2):
                r[1][0] -= 70
                dx = 70
            else:
                r[1][0] += 70
                dx = -70

            if r[1][1] > (grid_rows / 2):
                r[1][1] -= 70
                dy = -70
            else:
                r[1][1] += 70
                dy = 70
            r[1][2] = math.atan2(dy, dx) * 180 / math.pi

    def mission(self):
        rclpy.spin_once(self, timeout_sec=0.1)

        # init
        self.robot_servo_angle = Angle(angle=0.0)
        self.publish_robot_servo_angle()
        
        self.detect_rubble()
        
        for r in self.rubble:
            self.send_goal(Odometry(x=float(r[1][0]), y=float(r[1][1]), theta=float(r[1][2])))
            
            while not self.path_planning_action_client_state == CLIENT_STATES.SUCCESS:
                rclpy.spin_once(self, timeout_sec=0.1)
            
            self.robot_servo_angle = Angle(angle=45.0)
            self.publish_robot_servo_angle()
            
            self.send_goal(Odometry(x=float(r[0][0]), y=float(r[0][1]), theta=float(r[0][2])))
            
            while not self.path_planning_action_client_state == CLIENT_STATES.SUCCESS:
                rclpy.spin_once(self, timeout_sec=0.1)

            self.robot_servo_angle = Angle(angle=0.0)
            self.publish_robot_servo_angle()
    
        '''
        self.send_goal(Odometry(x=200.0, y=200.0, theta=0.0))
        while not self.path_planning_action_client_state == CLIENT_STATES.SUCCESS:
            rclpy.spin_once(self, timeout_sec=0.1)

        self.send_goal(Odometry(x=350.0, y=350.0, theta=0.0))
        while not self.path_planning_action_client_state == CLIENT_STATES.SUCCESS:
            rclpy.spin_once(self, timeout_sec=0.1)
        '''
        self.state = CONTROLLER_STATES.SLEEP

###################################################################################################

    def send_goal(self, goal: Odometry):
        self.path_planning_action_client_state = CLIENT_STATES.IN_PROGRESS

        goal_msg = Planner.Goal()
        goal_msg.goal = goal

        self.path_planning_action_client.wait_for_server()

        self.send_goal_future = self.path_planning_action_client.send_goal_async(goal_msg)

        self.send_goal_future.add_done_callback(self.goal_response_callback)

        return self.path_planning_action_client.send_goal_async(goal_msg)

    def goal_response_callback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.path_planning_action_client_state = CLIENT_STATES.FAIL
            self.get_logger().info('Goal rejected :(')
            return

        self.get_logger().info('Goal accepted :)')

        self.get_result_future = goal_handle.get_result_async()
        self.get_result_future.add_done_callback(self.get_result_callback)

    def get_result_callback(self, future):
        self.path_planning_action_client_state = CLIENT_STATES.SUCCESS
        #result = future.result().result
        #self.get_logger().info('Result: {0}'.format(result.sequence))
        #rclpy.shutdown()

    def image_callback(self, msg):
        try:
            _, self.img = cv2.threshold(self.bridge.imgmsg_to_cv2(msg, desired_encoding='mono8'), 70, 255, cv2.THRESH_BINARY)

        except Exception as e:
            self.get_logger().error(f"Error converting image: {e}")

    def robot_position_callback(self, msg):
        self.robot_position = msg

    def robot_command_callback(self, msg):
        self.state = CONTROLLER_STATES(msg.command)

    def publish_robot_velocity(self, msg=None):
        if msg is None:
            msg = self.robot_velocity
        else:
            self.robot_velocity = msg

        self.robot_velocity_publisher.publish(msg) 

    def publish_robot_servo_angle(self, msg=None):
        if msg is None:
            msg = self.robot_servo_angle
        else:
            self.robot_servo_angle = msg

        self.robot_servo_angle_publisher.publish(msg)

    def remove_rectangle_from_matrix(self, matrix, center, width, height, angle_degrees):
        if matrix.ndim == 2 and matrix.shape[1] == 2: # Assuming matrix is a point cloud
            points_to_check = matrix
        elif matrix.ndim == 2: # Assuming matrix is an image
            rows, cols = matrix.shape
            points_to_check = np.array(np.meshgrid(np.arange(cols), np.arange(rows))).reshape(2, -1).T
        else:
            raise ValueError("Unsupported matrix dimension. Expected 2D image or (N, 2) point cloud.")

        angle_rad = np.radians(-angle_degrees) # Rotate back by negative angle
        cos_a, sin_a = np.cos(angle_rad), np.sin(angle_rad)
        inv_rotation_matrix = np.array([[cos_a, -sin_a],
                                        [sin_a, cos_a]])

        # Translate points relative to rectangle center
        translated_points = points_to_check - np.array(center)

        # Rotate points back to align with unrotated rectangle
        rotated_back_points = (inv_rotation_matrix @ translated_points.T).T

        # Check if points are within unrotated rectangle bounds
        x_in_bounds = (rotated_back_points[:, 0] >= -width / 2) & (rotated_back_points[:, 0] <= width / 2)
        y_in_bounds = (rotated_back_points[:, 1] >= -height / 2) & (rotated_back_points[:, 1] <= height / 2)

        points_in_rectangle_mask = x_in_bounds & y_in_bounds

        if matrix.ndim == 2 and matrix.shape[1] == 2: # Point cloud
            return matrix[~points_in_rectangle_mask]
        else: # Image
            result_matrix = matrix.copy()
            rows, cols = matrix.shape
            # Convert flat mask back to 2D for image indexing
            mask_2d = points_in_rectangle_mask.reshape(rows, cols)
            result_matrix[mask_2d] = 0 # Or any other desired fill value
            return result_matrix

