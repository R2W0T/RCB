import math
import numpy as np

import cv2

from rclpy.qos import QoSProfile, HistoryPolicy, ReliabilityPolicy, DurabilityPolicy

import rclpy
from rclpy.action import ActionServer
from rclpy.node import Node

from cv_bridge import CvBridge

from sensor_msgs.msg import Image 


from robot_interfaces.action import Planner
from robot_interfaces.msg import Odometry
from robot_interfaces.msg import Speed 


from path_planner import PathPlanner, RRT, RRTStar, AStar, Pose
from map_generator import MapGenerator
from motion_controller import MotionController

class PathPlanningActionServer(Node):
    def __init__(self):
        super().__init__('path_planning_action_server')

        self.action_server = ActionServer(self, Planner, 'path_planning_action', self.execute_callback)

        self.pose_subscription = self.create_subscription(
            Odometry,
            'robot_position',
            self.pose_callback,
            10)
        self.pose_subscription  # prevent unused variable warning

        self.pose = Odometry()

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

        self.br = CvBridge()
    

        self.speed_publisher = self.create_publisher(
            Speed,
            'robot_speed',
            10)
        self.speed_publisher  # prevent unused variable warning

        self.map_generator = MapGenerator()
        self.path_planner = PathPlanner()
        self.motion_controller = MotionController()

    def pose_callback(self, msg):
        self.pose = msg

    def image_callback(self, msg):
        try:
            self.map_generator.set_img(self.br.imgmsg_to_cv2(msg, desired_encoding='mono8'))

            
        except Exception as e:
            self.get_logger().error(f"Error converting image: {e}")

    def publish_speed(self, msg):
        self.speed_publisher.publish(msg) 

    def execute_callback(self, goal_handle):
        #cv2.destroyAllWindows()

        goal = goal_handle.request.goal


        self.get_logger().info(f'Executing goal {goal} ...')
        self.get_logger().info(f'Pose: {self.pose.x}, {self.pose.y} ...')
        
        self.get_logger().info('Generating map...')
        self.map_generator.generate_map(Odometry(x=self.pose.x, y=self.pose.y, theta=self.pose.theta))
        self.get_logger().info('Map generated...')
        grid = self.map_generator.get_grid_map()

        #done in one step
        #self.get_logger().info('Inflating map...')
        #self.get_logger().info('Map inflated...')
        
        self.get_logger().info('Path planning...')
        #TODO

        rrt = RRT(grid, Pose(self.pose.x, self.pose.y), Pose(goal.x, goal.y), max_step=20)
        rrt_star = RRTStar(grid, Pose(self.pose.x, self.pose.y), Pose(goal.x, goal.y), max_step=20)
        a_star = AStar(grid, Pose(self.pose.x, self.pose.y), Pose(goal.x, goal.y))

        path = rrt.rrt()
        path_star = rrt_star.rrt_star()
        path_a_star = a_star.a_star()

        if not path:
            self.get_logger().info('RRT failed...')
        else:
            #if path[0].pose == Pose(x=self.pose.x, y=self.pose.y) and path[-1].pose == Pose(x=goal.x, y=goal.y):
            self.get_logger().info('RRT succeded...')

        if not path_star:
            self.get_logger().info('RRT* failed...')
        else:
            #if path_star[0].pose == Pose(x=self.pose.x, y=self.pose.y) and path_star[-1].pose == Pose(x=goal.x, y=goal.y):
            self.get_logger().info('RRT* succeded...')

        if not path_a_star:
            self.get_logger().info('A* failed...')
        else:
            #if path[0].pose == Pose(x=self.pose.x, y=self.pose.y) and path[-1].pose == Pose(x=goal.x, y=goal.y):
            self.get_logger().info('A* succeded...')

        img = cv2.cvtColor(grid, cv2.COLOR_GRAY2BGR)
        for node in path:
            if node.parent is not None:
                cv2.line(img, (int(node.pose.x), int(node.pose.y)), (int(node.parent.pose.x), int(node.parent.pose.y)), (255, 0, 0), 2)
                

        for node in path_star:
            if node.parent is not None:
                cv2.line(img, (int(node.pose.x), int(node.pose.y)), (int(node.parent.pose.x), int(node.parent.pose.y)), (0, 255, 0), 2)

        for node in path_a_star:
            if node.parent is not None:
                cv2.line(img, (int(node.pose.x), int(node.pose.y)), (int(node.parent.pose.x), int(node.parent.pose.y)), (0, 0, 255), 2)
        img[int(self.pose.y), int(self.pose.x)] = (0, 0, 255)
        img[int(goal.y), int(goal.x)] = (0, 0, 255)


        cv2.imshow("img", img)
        cv2.waitKey(6)
        self.get_logger().info('Path planned...')

        self.get_logger().info('Navigating to goal...')

        self.publish_speed(Speed(linear_speed=0, rotational_speed=0))

        goal_handle.succeed()
             
        for point in path_a_star:
            if point is None:
                break
            #point.print() 
            self.motion_controller.set_goal(Odometry(x=point.pose.x, y=point.pose.y, theta=point.pose.theta))

       
            while not self.motion_controller.get_state():
                # TODO after planner is done better goal setter

                self.motion_controller.set_speed(self.pose)

                self.publish_speed(self.motion_controller.get_speed())
         
                rclpy.spin_once(self, timeout_sec=0.1)
        
        '''
        self.motion_controller.set_goal(Odometry(x=goal.x, y=goal.y, theta=goal.theta))
        while not self.motion_controller.get_state():
            # TODO after planner is done better goal setter

            self.motion_controller.set_speed(self.pose)

            self.publish_speed(self.motion_controller.get_speed())
         
            rclpy.spin_once(self, timeout_sec=0.1)
        
        self.get_logger().info('Arrived at goal...')
        '''     
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


"""                
        for point in path:
            if point is None:
                break
            point.print() 
            self.motion_controller.set_goal(Odometry(x=point.pose.x, y=point.pose.y, theta=point.pose.theta))

        
            while not self.motion_controller.get_state():
                # TODO after planner is done better goal setter

                self.motion_controller.set_speed(self.pose)

                self.publish_speed(self.motion_controller.get_speed())
            
                rclpy.spin_once(self, timeout_sec=0.1)

"""     
