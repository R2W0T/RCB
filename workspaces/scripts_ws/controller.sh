#!/bin/bash
source /opt/ros/jazzy/local_setup.bash
cd controller_ws
colcon build --packages-select robot_interfaces
source install/local_setup.bash
colcon build
source install/local_setup.bash
python3 ../controller_ws/src/path_planner/path_planner/main.py & \
python3 ../controller_ws/src/robot_control/robot_control/main.py & wait
cd ..