#!/bin/bash
source /opt/ros/jazzy/local_setup.bash
cd sim_ws
colcon build --packages-select robot_interfaces
source install/local_setup.bash
colcon build
source install/local_setup.bash
ros2 launch robot_sim robot_sim.launch.py & wait
cd ..