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
        self.robot_servo_angle = Angle(amgle=0)
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
            eliability=ReliabilityPolicy.BEST_EFFORT, 
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
            Commane,
            'robot_command',
            self.robot_command_callback,
            10
        )
        self.robot_position_subscription
###################################################################################################

###################################################################################################
    def run(self):
        while True:
            rclpy.spin_once(self, timeout=0.1)
###################################################################################################

    def send_goal(self, pose: Odometry):
        self.path_planning_action_client_state = CLIENT_STATES.IN_PROGRESS

        goal_msg = Planner.Goal()
        goal_msg.goal = pose

        self.path_planning_action_client.wait_for_server()

        self.send_goal_future = self._path_planning_action_client.send_goal_async(goal_msg)

        self.send_goal_future.add_done_callback(self.goal_response_callback)

        #return self.path_planning_action_client.send_goal_async(goal_msg)

    def goal_response_callback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self._path_planning_action_client_state = CLIENT_STATES.FAIL
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
            self.img = self.bridge.imgmsg_to_cv2(msg, desired_encoding='mono8')

        except Exception as e:
            self.get_logger().error(f"Error converting image: {e}")

    def robot_position_callback(self, msg):
        self.robot_position = msg

    def robot_command_callback(self, msg):
        self.state = msg.command

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
