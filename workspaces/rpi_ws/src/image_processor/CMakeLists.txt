cmake_minimum_required(VERSION 3.28)
project(image_processor)

####################################################################################################..

include_directories( include )

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(robot_interfaces REQUIRED)                       

add_executable(image_processor_node src/main.cpp 
                            src/image_processor_node.cpp)

ament_target_dependencies(image_processor_node rclcpp sensor_msgs cv_bridge std_msgs robot_interfaces )      


install(TARGETS
  image_processor_node
  DESTINATION lib/${PROJECT_NAME})

###############################################################################################################

###############################################################################################################
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} ./include)


# target_link_libraries( image_processor_node ${OpenCV_LIBS})
###############################################################################################################

find_package( PkgConfig REQUIRED )
pkg_check_modules( GST REQUIRED gstreamer-1.0 gstreamer-video-1.0 gstreamer-app-1.0 )

target_include_directories( image_processor_node PRIVATE ${OpenCV_INCLUDE_DIRS} ${GST_INCLUDE_DIRS})

# target_link_libraries( image_processor_node ${OpenCV_LIBS} ${GST_LIBRARIES})

find_package( PkgConfig REQUIRED )
pkg_check_modules( LIBCAMERA REQUIRED libcamera )

target_include_directories( image_processor_node PRIVATE ${LIBCAMERA_INCLUDE_DIRS})

# target_link_libraries( image_processor_node PRIVATE  ${LIBCAMERA_LIBRARIES})

target_link_libraries( image_processor_node ${OpenCV_LIBS} ${LIBCAMERA_LIBRARIES} ${GST_LIBRARIES})

###############################################################################################################
ament_package()

################################################################################################################
