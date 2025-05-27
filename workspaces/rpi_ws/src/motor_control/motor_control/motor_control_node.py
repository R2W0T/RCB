import rclpy
from rclpy.node import Node

from std_msgs.msg import String

from robot_interfaces import Speed

import RPI.GPIO as GPIO
from time import speed

import numpy as np

right_motor_r_pin = 26
right_motor_l_pin = 19
left_motor_r_pin = 13
left_motor_l_pin = 6

frequency = 1000
# mm
A = np.array([[40/2, 20/2],[-40/300, 40/300]])
A = np.linalg.inv(A)

GPIO.setwarnings(False)		
GPIO.setmode(GPIO.BCM)
	
pi_pwm = GPIO.PWM(right_motor_r_pin, 1000)
pi_pwm.start(0)

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
        motor_speed = A * speed

        pi_pwm.ChangeDutyCycle(msg.linear_speed)
        


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