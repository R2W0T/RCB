import rclpy
from rclpy.node import Node

from std_msgs.msg import String

from robot_interfaces import Speed

import RPi.GPIO as GPIO
import time

import numpy as np

right_motor_r_pin = 26
right_motor_l_pin = 19
left_motor_r_pin = 13
left_motor_l_pin = 6

frequency = 1000
# mm
A = np.array([[40/2, 40/2],[-40/300, 40/300]])
A = np.linalg.inv(A)

GPIO.setwarnings(False)		
GPIO.setmode(GPIO.BCM)
	
r_r_pwm = GPIO.PWM(right_motor_r_pin, 1000)
r_r_pwm.start(0)

r_l_pwm = GPIO.PWM(right_motor_l_pin, 1000)
r_l_pwm.start(0)

l_r_pwm = GPIO.PWM(left_motor_r_pin, 1000)
l_r_pwm.start(0)

l_l_pwm = GPIO.PWM(left_motor_l_pin, 1000)
l_l_pwm.start(0)

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
        speed = np.array([msg.linear_speed, msg.angular_speed])
        motor_speed = np.dot(A, speed)

        r_r = 0
        r_l = 0

        l_r = 0
        l_l = 0

        if motor_speed[0] < 0:
            l_l -= motor_speed[0]
        else:
            l_r = motor_speed[0]


        if motor_speed[1] < 0:
            r_l -= motor_speed[1]
        else:
            r_r = motor_speed[1]

        r_l_pwm.ChangeDutyCycle(r_l)
        r_r_pwm.ChangeDutyCycle(r_r)
        l_l_pwm.ChangeDutyCycle(l_l)
        l_r_pwm.ChangeDutyCycle(l_r)
        


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