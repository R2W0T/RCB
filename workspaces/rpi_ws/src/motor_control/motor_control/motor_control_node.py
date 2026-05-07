import rclpy
from rclpy.node import Node

from std_msgs.msg import String

from robot_interfaces.msg import Velocity, Angle

import serial

import time

import numpy as np

ser = serial.Serial('/dev/ttyACM0', 9600)
endian = 'big'


# mm
wheel_radius = 55 # mm
robot_width = 190 # mm

A = np.array([[wheel_radius/robot_width, wheel_radius/robot_width],[-wheel_radius/robot_width, wheel_radius/robot_width]])
A = np.linalg.inv(A)

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

    # maps angle to pwm values
    def angle_to_pwm_percent(self, angle):
        pulse_width_ms = 1 + (angle / 180.0) * 1
        pwm_percent = (pulse_width_ms / 20.0) * 100
        return pwm_percent

    def servo_angle_callback(self, msg):
        pwm = self.angle_to_pwm_percent(msg.angle)
        # servo_pwm.ChangeDutyCycle(pwm)


    def robot_velocity_callback(self, msg):
        
        velocity = np.array([[msg.linear_velocity], [-msg.angular_velocity]])
        
        # round to percentage
        motor_velocity = np.dot(A, velocity) 
        motor_velocity *= 100 / 375

        if motor_velocity[0, 0] > 100:
            motor_velocity[0,0] = 100
        elif motor_velocity[0, 0] < -100:
            motor_velocity[0, 0] = -100
        
        if motor_velocity[1, 0] > 100:
            motor_velocity[1,0] = 100
        elif motor_velocity[1,0] < -100:
            motor_velocity[1,0] = -100


        right_forward_velocity = 0
        right_reverse_velocity = 0

        left_forward_velocity = 0
        left_reverse_velocity = 0

        if motor_velocity[0, 0] < 0:
            left_reverse_velocity -= motor_velocity[0, 0]
        else:
            left_forward_velocity = motor_velocity[0, 0]


        if motor_velocity[1, 0] < 0:
            right_reverse_velocity -= motor_velocity[1, 0]
        else:
            right_forward_velocity = motor_velocity[1, 0]

        if right_reverse_velocity < 20 and right_reverse_velocity != 0:
            right_reverse_velocity = 20

        if right_forward_velocity < 20 and right_forward_velocity != 0:
            right_forward_velocity = 20

        if left_reverse_velocity < 20 and left_reverse_velocity != 0:
            left_reverse_velocity = 20

        if left_forward_velocity < 20 and left_forward_velocity != 0:
            left_forward_velocity = 20

        vel = bytearray()
        vel.extend(int(right_forward_velocity).to_bytes(1, endian))
        vel.extend(int(right_reverse_velocity).to_bytes(1, endian))
        vel.extend(int(left_forward_velocity).to_bytes(1, endian))
        vel.extend(int(left_reverse_velocity).to_bytes(1, endian))
        ser.write(vel)

        self.get_logger().info(f'Publishing: \n right_forward_velocity: {right_forward_velocity}, right_reverse_velocity: {right_reverse_velocity} left_forward_velocity: {left_forward_velocity}, left_reverse_velocity: {left_reverse_velocity}')
        
        


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
