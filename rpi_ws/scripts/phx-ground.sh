#!/bin/bash
colcon build --packages-select robot_interfaces
source install/local_setup.bash

colcon build --packages-select motor_control 
source install/local_setup.bash

python3 src/motor_control/motor_control/motor_control_node.py