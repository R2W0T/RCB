import rclpy
from robot_control_node import RobotControlNode


def main(args=None):
    rclpy.init(args=args)

    action_client = RobotControlNode()
    action_client.run()

#    future = action_client.send_goal(10)

#    rclpy.spin(action_client)#_until_future_complete(action_client, future)

#    RobotControlNode.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
