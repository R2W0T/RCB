import rclpy
from rclpy.node import Node

from std_msgs.msg import String

from robot_interfaces.msg import Speed

import RPi.GPIO as GPIO
import time

import numpy as np

right_motor_forward_pin = 26
right_motor_reverse_pin = 19
left_motor_forward_pin = 13
left_motor_reverse_pin = 6

frequency = 1000
# mm
wheel_radius = 40 # mm
robot_width = 300 # mm

A = np.array([[wheel_radius/robot_width, wheel_radius/robot_width],[-wheel_radius/robot_width, wheel_radius/robot_width]])
A = np.linalg.inv(A)

GPIO.setwarnings(False)		
GPIO.setmode(GPIO.BCM)

GPIO.setup(right_motor_forward_pin,GPIO.OUT)
right_forward_pwm = GPIO.PWM(right_motor_forward_pin, 1000)
right_forward_pwm.start(0)

GPIO.setup(right_motor_reverse_pin,GPIO.OUT)
right_reverse_pwm = GPIO.PWM(right_motor_reverse_pin, 1000)
right_reverse_pwm.start(0)

GPIO.setup(left_motor_forward_pin,GPIO.OUT)
left_forward_pwm = GPIO.PWM(left_motor_forward_pin, 1000)
left_forward_pwm.start(0)

GPIO.setup(left_motor_reverse_pin,GPIO.OUT)
left_reverse_pwm = GPIO.PWM(left_motor_reverse_pin, 1000)
left_reverse_pwm.start(0)

class MotorControlNode(Node):

    def __init__(self):
        super().__init__('motor_control_node')
        self.subscription = self.create_subscription(
            Speed,
            'robot_speed',
            self.robot_speed_callback,
            10)
        self.subscription  # prevent unused variable warning

    def robot_speed_callback(self, msg):
        
        speed = np.array([[msg.linear_speed], [-msg.rotational_speed]])
        
        # round to percentage
        motor_speed = np.dot(A, speed) 
        motor_speed *= 100 / 375

        if motor_speed[0, 0] > 100:
            motor_speed[0,0] = 100
        elif motor_speed[0, 0] < -100:
            motor_speed[0, 0] = -100
        
        if motor_speed[1, 0] > 100:
            motor_speed[1,0] = 100
        elif motor_speed[1,0] < -100:
            motor_speed[1,0] = -100


        right_forward_speed = 0
        right_reverse_speed = 0

        left_forward_speed = 0
        left_reverse_speed = 0

        if motor_speed[0, 0] < 0:
            left_reverse_speed -= motor_speed[0, 0]
        else:
            left_forward_speed = motor_speed[0, 0]


        if motor_speed[1, 0] < 0:
            right_reverse_speed -= motor_speed[1, 0]
        else:
            right_forward_speed = motor_speed[1, 0]

        right_reverse_pwm.ChangeDutyCycle(right_reverse_speed)
        right_forward_pwm.ChangeDutyCycle(right_forward_speed)
        left_reverse_pwm.ChangeDutyCycle(left_reverse_speed)
        left_forward_pwm.ChangeDutyCycle(left_forward_speed)
        
        self.get_logger().info(f'Publishing: \n right_forward_speed: {right_forward_speed}, right_reverse_speed: {right_reverse_speed} left_forward_speed: {left_forward_speed}, left_reverse_speed: {left_reverse_speed}')
        
        


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
