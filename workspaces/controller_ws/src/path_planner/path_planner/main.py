import cv2

import rclpy

from path_planning_node import PathPlanningActionServer

from rclpy.executors import MultiThreadedExecutor

import threading

def main(args=None):
    rclpy.init(args=args)

    path_planning_action_server = PathPlanningActionServer()


    executor = MultiThreadedExecutor(num_threads=10)
    executor.add_node(path_planning_action_server)

    spin_thread = threading.Thread(target=executor.spin, daemon=True)
    spin_thread.start()


    try:
        while rclpy.ok():
            # Main thread handles the GUI
            with path_planning_action_server.frame_lock:
                for name, frame in path_planning_action_server.frames.items():
                    cv2.imshow(name, frame)
                cv2.waitKey(1)
    finally:
        path_planning_action_server.destroy_node()
        rclpy.shutdown()
        cv2.destroyAllWindows()

if __name__ == '__main__':
    main()
