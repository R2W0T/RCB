#!/bin/bash
source /opt/ros/jazzy/local_setup.bash
cd controller_ws
colcon build --packages-select robot_interfaces
source install/local_setup.bash
colcon build
source install/local_setup.bash
ros2 run joystick joystick_node & \
python3 src/motor_control/motor_control/motor_control_node.py & wait
cd ..