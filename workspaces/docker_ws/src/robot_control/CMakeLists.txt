cmake_minimum_required(VERSION 3.8)
project(robot_control)

###############################################################################################################
#...

include_directories( include )

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(robot_interfaces REQUIRED)                         # CHANGE

add_executable(robot_control_node src/main.cpp 
                                  src/state_machine.cpp
                                  src/robot_control_node.cpp)
ament_target_dependencies(robot_control_node rclcpp std_msgs robot_interfaces)         # CHANGE

# add_executable(listener src/subscriber_member_function.cpp)
# ament_target_dependencies(listener rclcpp robot_interfaces)     # CHANGE

install(TARGETS
  robot_control_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
###############################################################################################################

###############################################################################################################

################################################################################################################