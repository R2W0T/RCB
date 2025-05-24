cmake_minimum_required(VERSION 3.8)
project(camera)

####################################################################################################..

include_directories( include )

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(robot_interfaces REQUIRED)                       

add_executable(camera_node src/main.cpp 
                            src/camera_node.cpp)
ament_target_dependencies(camera_node rclcpp std_msgs robot_interfaces )      


install(TARGETS
  camera_node
  DESTINATION lib/${PROJECT_NAME})

###############################################################################################################

###############################################################################################################
find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} ./include)

add_library( img_proc STATIC ./src/ImageProcessor/ImageTransformationProcessor.cpp 
                        ./src/ImageProcessor/Marker.cpp 
                        ./src/ImageProcessor/ArucoMarkerProcessor.cpp
                        ./src/ImageProcessor/ImageProcessor.cpp )


target_link_libraries( camera_node ${OpenCV_LIBS} )
target_link_libraries( img_proc ${OpenCV_LIBS} )
target_link_libraries( camera_node img_proc )
###############################################################################################################


###############################################################################################################
ament_package()

################################################################################################################