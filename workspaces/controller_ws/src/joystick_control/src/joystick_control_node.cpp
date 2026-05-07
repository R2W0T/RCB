#include "joystick_control/joystick_control_node.hpp"


using std::placeholders::_1;

JoystickControlNode::JoystickControlNode() : Node("joystick_control_node")
{

    ////////////////////////////////////////////////////////////////////////////////////
    joystick_publisher = this->create_publisher<robot_interfaces::msg::Velocity>("robot_velocity", 10);
    servo_publisher = this->create_publisher<robot_interfaces::msg::Angle>("servo_angle", 10);

        
}

void JoystickControlNode::publish(int32_t linear_velocity, int32_t angular_velocity) {
    auto message = robot_interfaces::msg::Velocity();
    message.linear_velocity = -linear_velocity * 100 / 32767;
    message.angular_velocity = angular_velocity * 100 / 32767;

    RCLCPP_INFO(  this->get_logger(), 
	  	  "Publishing:\n Linear velocity: '%d', Angular velocity: '%d'", 
		  message.linear_velocity, 
		  message.angular_velocity
		);

    joystick_publisher->publish(message);
}

void JoystickControlNode::publish_angle(int32_t fangle, int32_t sangle) {
    auto message = robot_interfaces::msg::Angle();
    message.fangle = -((32767 + fangle) * 100 / 32767) + 50;
    message.sangle = -((32767 + sangle) * 100 / 32767) + 50;

    RCLCPP_INFO(  this->get_logger(), 
      "Publishing:\n First Angle: '%f', Secong Angle: '%f'", 
      message.fangle,
      message.sangle
		);

    servo_publisher->publish(message);
}
