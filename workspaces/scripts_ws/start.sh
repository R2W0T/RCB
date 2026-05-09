#!/bin/bash
source /opt/ros/jazzy/local_setup.bash
source controller_ws/install/local_setup.bash
ros2 topic pub /robot_command robot_interfaces/msg/Command "command: 1" --once & wait