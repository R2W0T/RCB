import cv2

import rclpy

from path_planning_node import PathPlanningActionServer

def main(args=None):
    rclpy.init(args=args)

    path_planning_action_server = PathPlanningActionServer()

    rclpy.spin(path_planning_action_server)

    path_planning_action_server.destroy_node()

    rclpy.shutdown()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    main()
