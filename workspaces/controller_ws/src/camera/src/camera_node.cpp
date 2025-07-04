#include "camera/camera_node.hpp"


using std::placeholders::_1;

CameraNode::CameraNode() : Node("camera_control_node")
{

    ////////////////////////////////////////////////////////////////////////////////////
    robot_position_publisher = this->create_publisher<robot_interfaces::msg::Odometry>("robot_position", 10);

        
}

void CameraNode::publish(float x, float y, float theta) {
    auto message = robot_interfaces::msg::Odometry();
    message.x = x;
    message.y = y;
    message.theta = theta;

    RCLCPP_INFO(this->get_logger(), "Publishing:\n x: '%f', y: '%f', theta: '%f'", message.x, message.y, message.theta);

    robot_position_publisher->publish(message);
}
