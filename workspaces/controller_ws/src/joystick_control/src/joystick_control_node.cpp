#include "joystick_control/joystick_control_node.hpp"


using std::placeholders::_1;

JoystickControlNode::JoystickControlNode() : Node("joystick_control_node")
{

    ////////////////////////////////////////////////////////////////////////////////////
    joystick_publisher = this->create_publisher<robot_interfaces::msg::Speed>("joystick", 10);

        
}

void JoystickControlNode::publish(int32_t linear_speed, int32_t rotational_speed) {
    auto message = robot_interfaces::msg::Speed();
    message.linear_speed = linear_speed;
    message.rotational_speed = rotational_speed;

    RCLCPP_INFO(this->get_logger(), "Publishing:\n Linear speed: '%d', Rotational speed: '%d'", message.linear_speed, message.rotational_speed);

    joystick_publisher->publish(message);
}
