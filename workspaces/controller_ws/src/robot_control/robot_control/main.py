import rclpy
from robot_control_node import RobotControlNode


def main(args=None):
    rclpy.init(args=args)

    action_client = RobotControlNode()
    action_client.run()

    action_client.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
