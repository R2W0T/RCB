import os

from ament_index_python.packages import get_package_share_directory

import launch
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    return launch.LaunchDescription([

        Node(
            package="tf2_ros",
            executable="static_transform_publisher",
            name="static_transform_publisher",
            arguments=["0.0", "0.0", "0.0", "0.0", "0.0", "0.0", "odom", "base_link", ]

        ),

        Node(
            package="image_processor",
            executable="image_processor_node",
            name="image_processor_node"
        ),

        Node(
            package="image_post_processor",
            executable="image_post_processor_node",
            name="image_post_processor_node"
        ),
    ])
    



#
##        IncludeLaunchDescription(
##            PathJoinSubstitution([
 #               FindPackageShare('launch_all'), 'launch', 'no_controller.launch.py']
 #           ),
 #           launch_arguments={'target_frame': 'map'}.items(),
#        ),
