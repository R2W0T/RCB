cmake_minimum_required(VERSION 3.31)
project(camera_driver)

####################################################################################################..

include_directories( include )

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(robot_interfaces REQUIRED)                       
find_package(cv_bridge REQUIRED)                       

add_executable(camera_driver_node src/main.cpp 
                            src/camera_driver_node.cpp)

ament_target_dependencies(camera_driver_node cv_bridge rclcpp std_msgs sensor_msgs robot_interfaces )      


install(TARGETS
  camera_driver_node
  DESTINATION lib/${PROJECT_NAME})

###############################################################################################################

###############################################################################################################
find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} ./include)


target_link_libraries( camera_driver_node ${OpenCV_LIBS} )
###############################################################################################################


###############################################################################################################
ament_package()

################################################################################################################
