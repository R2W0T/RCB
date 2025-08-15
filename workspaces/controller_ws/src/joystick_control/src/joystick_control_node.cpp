#include "joystick_control/joystick_control_node.hpp"


using std::placeholders::_1;

JoystickControlNode::JoystickControlNode() : Node("joystick_control_node")
{

    ////////////////////////////////////////////////////////////////////////////////////
    joystick_publisher = this->create_publisher<robot_interfaces::msg::Velocity>("joystick", 10);

        
}

void JoystickControlNode::publish(int32_t linear_velocity, int32_t angular_velocity) {
    auto message = robot_interfaces::msg::Velocity();
    message.linear_velocity = linear_velocity;
    message.angular_velocity = angular_velocity;

    RCLCPP_INFO(  this->get_logger(), 
	  	  "Publishing:\n Linear velocity: '%d', Angular velocity: '%d'", 
		  message.linear_velocity, 
		  message.angular_velocity
		);

    joystick_publisher->publish(message);
}
