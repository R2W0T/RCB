cmake_minimum_required(VERSION 3.28)
project(sim_image_processor)

####################################################################################################..

include_directories( include )

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(robot_interfaces REQUIRED)                       

add_executable(sim_image_processor_node src/main.cpp 
                            src/image_processor_node.cpp)

ament_target_dependencies(sim_image_processor_node rclcpp sensor_msgs cv_bridge std_msgs robot_interfaces )      


install(TARGETS
  sim_image_processor_node
  DESTINATION lib/${PROJECT_NAME})

###############################################################################################################

###############################################################################################################
find_package( OpenCV REQUIRED )
#4.6.0
include_directories( ${OpenCV_INCLUDE_DIRS} ./include)


target_link_libraries( sim_image_processor_node ${OpenCV_LIBS} )
###############################################################################################################


###############################################################################################################
ament_package()

################################################################################################################
