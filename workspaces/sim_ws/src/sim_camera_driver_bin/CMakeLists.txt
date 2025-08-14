cmake_minimum_required(VERSION 3.28)
project(sim_camera_driver_bin)

####################################################################################################..

include_directories( include )

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(robot_interfaces REQUIRED)                       
find_package(cv_bridge REQUIRED)                       

add_executable(sim_camera_driver_bin_node src/main.cpp 
                            src/camera_driver_bin_node.cpp)

ament_target_dependencies(sim_camera_driver_bin_node cv_bridge rclcpp std_msgs sensor_msgs robot_interfaces )      


install(TARGETS
  sim_camera_driver_bin_node
  DESTINATION lib/${PROJECT_NAME})

###############################################################################################################

###############################################################################################################
find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} ./include)


target_link_libraries( sim_camera_driver_bin_node ${OpenCV_LIBS} )
###############################################################################################################


###############################################################################################################
ament_package()

################################################################################################################
