import rclpy
from rclpy.node import Node

from geometry_msgs.msg import Twist 

from robot_interfaces.msg import Velocity

class MotionToSimNode(Node):

    def __init__(self):

        super().__init__('motion_to_sim')
        self.publisher_ = self.create_publisher(Twist, 'cmd_vel', 10)

        self.subscription = self.create_subscription(
            Velocity,
            'robot_velocity',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning

    def listener_callback(self, msg):
        if msg.linear_velocity < 15 and msg.linear_velocity != 0 and msg.linear_velocity > 0:
            msg.linear_velocity = 15

        if msg.linear_velocity > -15 and msg.linear_velocity != 0 and msg.linear_velocity < 0:
            msg.linear_velocity = -15

        if msg.angular_velocity < 15 and msg.angular_velocity != 0 and msg.angular_velocity > 0:
            msg.angular_velocity = 15

        if msg.angular_velocity > -15 and msg.angular_velocity != 0 and msg.angular_velocity < 0:
            msg.angular_velocity = -15

        twist_msg = Twist()
        twist_msg.linear.x = float(msg.linear_velocity) / 25 
        twist_msg.angular.z = -float(msg.angular_velocity) / 25
        
        self.publisher_.publish(twist_msg)


def main(args=None):

    rclpy.init(args=args)

    motion_to_sim_node = MotionToSimNode()

    rclpy.spin(motion_to_sim_node)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    motion_to_sim_node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
    

