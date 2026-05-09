import rclpy
from rclpy.node import Node

from std_msgs.msg import String

from robot_interfaces.msg import Velocity, Angle

import serial

import time
import math 

import numpy as np

ser = serial.Serial('/dev/ttyUSB0', 115200)
# ser = serial.Serial('/dev/ttyACM0', 115200)
endian = 'big'

# mm
wheel_radius = 55 # mm
robot_width = 190 # mm

class MotorControlNode(Node):

    def __init__(self):
        super().__init__('motor_control_node')
        self.subscription = self.create_subscription(
            Velocity,
            'robot_velocity',
            self.robot_velocity_callback,
            10)
        self.subscription  # prevent unused variable warning

        self.servo_subscription = self.create_subscription(
            Angle,
            'servo_angle',
            self.servo_angle_callback,
            10)
        self.servo_subscription  # prevent unused variable warning

    def servo_angle_callback(self, msg):
        pass


    def robot_velocity_callback(self, msg):
        
        motor_velocity = np.array([
            msg.linear_velocity - ((msg.angular_velocity * (math.pi / 180) * (100 / 165)) * robot_width / 2), 
            msg.linear_velocity + ((msg.angular_velocity * (math.pi / 180) * (100 / 165)) * robot_width / 2)
        ])

        self.get_logger().info(f'Publishing 0: \n right_motor_velocity: {int(motor_velocity[1])}, left_motor_velocity: {int(motor_velocity[0])}')

        motor_velocity *= 4 * 100 / 375

        if motor_velocity[0] > 100:
            motor_velocity[0] = 100
        elif motor_velocity[0] < -100:
            motor_velocity[0] = -100
        
        if motor_velocity[1] > 100:
            motor_velocity[1] = 100
        elif motor_velocity[1] < -100:
            motor_velocity[1] = -100


        if motor_velocity[1] < 20 and motor_velocity[1] > 0 and motor_velocity[1] != 0:
            motor_velocity[1] = 20

        elif motor_velocity[1] > -20 and motor_velocity[1] < 0 and motor_velocity[1] != 0:
            motor_velocity[1] = -20

        if motor_velocity[0] < 20 and motor_velocity[0] > 0 and motor_velocity[0] != 0:
            motor_velocity[0] = 20

        elif motor_velocity[0] > -20 and motor_velocity[0] < 0 and motor_velocity[0] != 0:
            motor_velocity[0] = -20

        vel = bytearray()
        vel.extend(int(0).to_bytes(1, endian, signed=False))
        vel.extend(int(motor_velocity[0]).to_bytes(1, endian, signed=True))
        vel.extend(int(motor_velocity[1]).to_bytes(1, endian, signed=True))
        ser.write(vel)

        self.get_logger().info(f'Publishing: \n right_motor_velocity: {int(motor_velocity[1])}, left_motor_velocity: {int(motor_velocity[0])}')
        
def main(args=None):
    rclpy.init(args=args)

    motor_control_node = MotorControlNode()

    rclpy.spin(motor_control_node)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    motor_control_node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
