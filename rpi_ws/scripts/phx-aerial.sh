#!/bin/bash
colcon build --packages-select robot_interfaces
source install/local_setup.bash

colcon build --packages-select image_processor
source install/local_setup.bash

ros2 run image_processor image_processor_node