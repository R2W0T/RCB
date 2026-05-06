import rclpy
from rclpy.executors import SingleThreadedExecutor
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, DurabilityPolicy, HistoryPolicy

from std_msgs.msg import String
from sensor_msgs.msg import CompressedImage, Image

from robot_interfaces.msg import Commnad, Odometry

import time

import numpy as np
from enum import Enum

from cv_bridge import CvBridge
import cv2
import math

from picamera2 import Picamera2

class state(Enum):
    SLEEP = 0
    PUBLISH = 1
    PUBLISH_MAIN = 2

class ImageProcessorNode(Node):

    def __init__(self):
        super().__init__('image_processor_node')
        self.command_subscription = self.create_subscription(
            Command,
            'image_command',
            self.command_callback,
            10)
        self.command_subscription  # prevent unused variable warning

        self.robot_position_publisher = self.create_publisher(
            Odometry,
            'robot_position',
            10)
        self.robot_position_publisher  # prevent unused variable warning
        video_qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            durability=DurabilityPolicy.VOLATILE,
            history=HistoryPolicy.KEEP_LAST,
            depth=1
        )
        self.compressed_image_publisher = self.create_publisher(
            CompressedImage,
            'compressed_processed_image',
            self.servo_angle_callback,
            video_qos_profile)
        self.compressed_image_publisher  # prevent unused variable warning

        self.command = state.SLEEP.value
        self.bridge = CvBridge()

    def command_callback(self, command):
        self.command = command

    def publish_compressed_processed_image(img):
        cv_image = self.bridge.cv2_to_imgmsg(image, "mono8")

        compressd_img = self.bridge.cv2_to_compressed_imgmsg(cv_image, dst_format='jpeg')

        self.compressed_image_publisher.publish(compressd_img)

    def publish_position(x, y, theta):
        odom = Odometry(x=x, y=y, theta=theta)
        self.get_logger().info(f"Publishing:\n x: {odom.x}, y: {odom.y}, theta: {odom.theta}")
        self.robot_position_publisher.publish(odom)

    def process_image(img):
        gray_img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

        # gray_img = cv2.threshold(gray_img, 70, 1, cv2.THRESH_BINARY);

        if self.state == state.PUBLISH_MAIN.value:
            self.publish_compressed_processed_image(gray_img)
            self.get_logger().info("Publishing: 4")

        markers_cw_ids = [0, 1, 2, 3]
        width = 640
        height = 480
        src_pts = [[0, 0], [0, 0], [0, 0], [0, 0]]
        dst_pts = [[0, 0], [width, 0], [0, height], [width, height]]
        robot_marker_id = 4
        dictionary = cv2.aruco.getPredefinedDictionary(cv2.aruco.DICT_APRILTAG_25h9)
        parameters =  cv2.aruco.DetectorParameters()

        detector = cv2.aruco.ArucoDetector(dictionary, parameters)
        corners, ids, rejected = detector.detectMarkers(gray_img)

        # # 4. Draw results
        # if ids is not None:
        #     cv2.aruco.drawDetectedMarkers(img, corners, ids)

        self.get_logger().info(f"Publishing: 1, {ids.size()}")
        if(ids.size() < 5):
            return; 


        self.get_logger().info("Publishing: 2")
        for i in range(ids):
            for j in range(4):
                if ids[i] == markers_cw_ids[j]:
                    src_pts[j] = corners[i][0]
        
        p_matrix = cv2.getPerspectiveTransform(src_pts, dst_pts)

        dst = cv2.warpPerspective(gray_img, p_matrix, cv2.Size(width, height))

        corners, ids, rejected = detector.detectMarkers(dst)
                
        for i in range(ids.size()):
            if ids[i] == robot_marker_id:
                theta = math.atan2((corners[i][0].y - corners[i][1].y), (corners[i][1].x - corners[i][0].x))
                theta *=  180 / math.PI
                theta = theta if theta >= 0 else 360 + theta
                self.publish_position(((corners[i][0].x + corners[i][2].x) / 2), 
                                ((corners[i][0].y + corners[i][2].y) / 2),
                                theta)
                break

        if self.state == state.PUBLISH.value:
            self.publish_compressed_processed_image(dst)
            self.get_logger().info("Publishing: 3")

def main(args=None):

    cam = Picamera2()
    config = cam.create_video_configuration(main={"format": 'RGB888', "size": (640, 480)})
    cam.configure(config)
    cam.start()

    rclpy.init(args=args)

    image_processor_node = ImageProcessorNode()
    executor = SingleThreadedExecutor()
    executor.add_node(image_processor_node)
    executor.spin_once(timeout_sec=0.1)

    try:
        while rclpy.ok():
            executor.spin_once(timeout_sec=0.1)
            frame = cam.capture_array()
            img = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)
            rclpy.spin_once(image_processor_node)

            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

            image_processor_node.process_image(img)
    except KeyboardInterrupt:
        pass
    finally:
        cam.stop()
        image_processor_node.destroy_node()
        rclpy.shutdown()




if __name__ == '__main__':
    main()
