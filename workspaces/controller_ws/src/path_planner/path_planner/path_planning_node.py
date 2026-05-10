import math
import numpy as np
import time

import cv2

from rclpy.qos import QoSProfile, HistoryPolicy, ReliabilityPolicy, DurabilityPolicy

import rclpy
from rclpy.action import ActionServer
from rclpy.node import Node

from cv_bridge import CvBridge

from sensor_msgs.msg import CompressedImage 


from robot_interfaces.action import Planner
from robot_interfaces.msg import Command, Odometry, Velocity 


from path_planner import  AStar, Pose
from map_generator import MapGenerator
from motion_controller import PurePursuitMotionController

from rclpy.callback_groups import ReentrantCallbackGroup

import threading

class PathPlanningActionServer(Node):
    def __init__(self):
        super().__init__('path_planning_action_server')

        self.frames = {}
        self.frame_lock = threading.Lock()

        self.reentrant_group = ReentrantCallbackGroup()

        self.action_server = ActionServer(
            self, 
            Planner, 
            'path_planning_action', 
            self.execute_callback,
            callback_group=self.reentrant_group
        )

        self.pose_subscription = self.create_subscription(
            Odometry,
            'robot_position',
            self.pose_callback,
            10,
            callback_group=self.reentrant_group
        )
        self.pose_subscription  # prevent unused variable warning

        self.pose = Odometry()

        video_qos_profile = QoSProfile(
                history=HistoryPolicy.KEEP_LAST, 
                reliability=ReliabilityPolicy.BEST_EFFORT, 
                durability=DurabilityPolicy.VOLATILE, 
                depth=1
        )

        self.image_subscription = self.create_subscription(
            CompressedImage,
            'compressed_processed_image',
            self.image_callback,
            video_qos_profile,
            callback_group=self.reentrant_group
        )
        self.image_subscription  # prevent unused variable warning

        self.br = CvBridge()
    

        self.velocity_publisher = self.create_publisher(
            Velocity,
            'robot_velocity',
            10,
        )
        self.velocity_publisher  # prevent unused variable warning

        self.image_command_publisher = self.create_publisher(
            Command,
            'image_command',
            10,
        )
        self.image_command_publisher  # prevent unused variable warning

        self.map_generator = MapGenerator(padding=30, rubble_size=20, robot_width = 60, robot_height = 60)

    def pose_callback(self, msg):
        self.pose = msg

    def image_callback(self, msg):
        try:
            img = self.br.compressed_imgmsg_to_cv2(msg)
            map = self.map_generator.set_img(img, self.pose)
            with self.frame_lock:
                self.frames['Image'] = img
                self.frames['Generated Map'] = map
            
        except Exception as e:
            self.get_logger().error(f"Error converting image: {e}")

    def publish_image_command(self, msg):
        self.image_command_publisher.publish(msg)

    def publish_velocity(self, msg):
        self.velocity_publisher.publish(msg) 

    def execute_callback(self, goal_handle):

        self.publish_image_command(Command(command=1))
        time.sleep(5)
        self.publish_image_command(Command(command=0))

        goal = goal_handle.request.goal

        self.get_logger().info(f'Executing goal {goal} ...')
        self.get_logger().info(f'Pose: {self.pose.x}, {self.pose.y} ...')
        
        self.get_logger().info('Generating map...')
        self.map_generator.generate_map(Odometry(x=self.pose.x, y=self.pose.y, theta=self.pose.theta))
        self.get_logger().info('Map generated...')
        grid = self.map_generator.get_grid_map()
        emg = cv2.cvtColor(grid, cv2.COLOR_GRAY2BGR)
        cv2.line(emg, (int(goal.x), int(goal.y)), (int(goal.x+2), int(goal.y+2)), (0, 0, 255), 2)

        self.get_logger().info('Path planning...')

        with self.frame_lock:
            self.frames['Generatted Grid'] = grid 
            self.frames['Pose and Goal Points'] = emg 

        a_star = AStar(grid, Pose(self.pose.x, self.pose.y), Pose(goal.x, goal.y, goal.theta))

        path_a_star = a_star.a_star()

        if not path_a_star:
            self.get_logger().info('A* failed...')
        else:
            self.get_logger().info('A* succeded...')

        img = cv2.cvtColor(grid, cv2.COLOR_GRAY2BGR)

        for node in path_a_star:
            if node.parent is not None:
                cv2.line(img, (int(node.pose.x), int(node.pose.y)), (int(node.parent.pose.x), int(node.parent.pose.y)), (0, 0, 255), 2)
        img[int(self.pose.y), int(self.pose.x)] = (0, 0, 255)
        img[int(goal.y), int(goal.x)] = (0, 0, 255)

        with self.frame_lock:
            self.frames['Generatted Path'] = img 

        self.get_logger().info('Path planned...')

        self.get_logger().info('Navigating to goal...')

        self.publish_velocity(Velocity(linear_velocity=0, angular_velocity=0))


        controller = PurePursuitMotionController(40)

        path = []
        for point in path_a_star:
            path.append([point.pose.x, point.pose.y, point.pose.theta])
        
        path[-1][2] = goal.theta
        controller.set_path(path)

        while not controller.get_state():
            controller.set_velocity([self.pose.x, self.pose.y, self.pose.theta])

            velocity = controller.get_velocity()
            self.get_logger().info(f'{velocity.linear_velocity}, {velocity.angular_velocity}')
            self.get_logger().info(f'{controller.state}')
            self.publish_velocity(velocity)
         
            time.sleep(0.05)

        self.get_logger().info('Arrived at goal...')

        cv2.destroyAllWindows()

        goal_handle.succeed()
             
        succeed = Planner.Result()

        return succeed
    

def draw_line(mat, start, end, value):
    d_y = end.pose.y - start.pose.y
    d_x = end.pose.x - start.pose.x
    if d_x == 0:
        for i in range(int(d_y)):
            mat[int(start.pose.y+i), int(start.pose.x)] = value
        return
    m = d_y / d_x
    c = start.pose.y - (m * start.pose.x)


    for i in range(int(d_x)):
        x = i + start.pose.x
        y = m * x + c
        
        mat[int(y), int(x)] = value

    for i in range(int(d_y)):
        y = i + start.pose.y
        x = (y - c) / m
        
        mat[int(y), int(x)] = value