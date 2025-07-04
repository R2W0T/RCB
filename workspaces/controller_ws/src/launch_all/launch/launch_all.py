import launch
from launch_ros.actions import Node

def generate_launch_description():
    return launch.LaunchDescription([
        Node(
            package="robot_control",
            executable="robot_control_node",
            name="robot_control_node"
        ),

        Node(
            package="joystick_control",
            executable="joystick_control_node",
            name="joystick_control_node"
        ),

        Node(
            package="camera",
            executable="camera_node",
            name="camera_node"
        ),
    ])
