import cv2

import rclpy

from path_planning_node import PathPlanningActionServer

from rclpy.executors import MultiThreadedExecutor

def main(args=None):
    rclpy.init(args=args)

    path_planning_action_server = PathPlanningActionServer()


    executor = MultiThreadedExecutor(num_threads=10)

    rclpy.spin(path_planning_action_server, executor=executor)

    path_planning_action_server.destroy_node()

    rclpy.shutdown()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    main()
