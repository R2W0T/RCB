import rclpy
from rclpy.node import Node

from std_msgs.msg import String

from robot_interfaces.msg import Velocity, Angle

import RPi.GPIO as GPIO
import time

import numpy as np

servo_pin = 14

left_motor_forward_pin = 4
left_motor_reverse_pin = 17
right_motor_forward_pin = 25
right_motor_reverse_pin = 23

frequency = 1000
# mm
wheel_radius = 40 # mm
robot_width = 300 # mm

A = np.array([[wheel_radius/robot_width, wheel_radius/robot_width],[-wheel_radius/robot_width, wheel_radius/robot_width]])
A = np.linalg.inv(A)

GPIO.setwarnings(False)		
GPIO.setmode(GPIO.BCM)

GPIO.setup(servo_pin,GPIO.OUT)
servo_pwm = GPIO.PWM(servo_pin, 50)
servo_pwm.start(0)

GPIO.setup(right_motor_forward_pin,GPIO.OUT)
right_forward_pwm = GPIO.PWM(right_motor_forward_pin, frequency)
right_forward_pwm.start(0)

GPIO.setup(right_motor_reverse_pin,GPIO.OUT)
right_reverse_pwm = GPIO.PWM(right_motor_reverse_pin, frequency)
right_reverse_pwm.start(0)

GPIO.setup(left_motor_forward_pin,GPIO.OUT)
left_forward_pwm = GPIO.PWM(left_motor_forward_pin, frequency)
left_forward_pwm.start(0)

GPIO.setup(left_motor_reverse_pin,GPIO.OUT)
left_reverse_pwm = GPIO.PWM(left_motor_reverse_pin, frequency)
left_reverse_pwm.start(0)

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
        servo_pwm.ChangeDutyCycle(pwm)


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

        if right_reverse_velocity < 35 and right_reverse_velocity != 0:
            right_reverse_velocity = 35

        if right_forward_velocity < 35 and right_forward_velocity != 0:
            right_forward_velocity = 35

        if left_reverse_velocity < 35 and left_reverse_velocity != 0:
            left_reverse_velocity = 35

        if left_forward_velocity < 35 and left_forward_velocity != 0:
            left_forward_velocity = 35

        right_reverse_pwm.ChangeDutyCycle(right_reverse_velocity)

        right_forward_pwm.ChangeDutyCycle(right_forward_velocity)

        left_reverse_pwm.ChangeDutyCycle(left_reverse_velocity)

        left_forward_pwm.ChangeDutyCycle(left_forward_velocity)
        
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
