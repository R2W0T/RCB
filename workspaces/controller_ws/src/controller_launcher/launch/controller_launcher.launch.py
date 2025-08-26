from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='robot_control',
            executable='main.py',
#            name='robot_control_node',
            output='screen',
            # parameters=[{'param_name': 'param_value'}] # Optional parameters
        ),
        Node(
            package='path_planner',
            executable='main.py',
#            name='path_planning_node',
            output='screen',
            # parameters=[{'param_name': 'param_value'}] # Optional parameters
        )
    ])
