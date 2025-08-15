#include "robot_control/robot_control_node.hpp"

#include "robot_control/state_machine.hpp"


extern state_machine_t state_machine;

using std::placeholders::_1;

RobotControlNode::RobotControlNode() : Node("robot_control_node")
{
    position_subscription = this->create_subscription<robot_interfaces::msg::Odometry>(
    "robot_position", 10, std::bind(&RobotControlNode::position_topic_callback, this, _1));


    command_subscription = this->create_subscription<robot_interfaces::msg::Command>(
        "robot_command", 10, std::bind(&RobotControlNode::command_topic_callback, this, _1));


        
    joystick_subscription = this->create_subscription<robot_interfaces::msg::Velocity>(
        "joystick", 10, std::bind(&RobotControlNode::joystick_topic_callback, this, _1));


    ////////////////////////////////////////////////////////////////////////////////////
    velocity_publisher = this->create_publisher<robot_interfaces::msg::Velocity>("robot_velocity", 10);

        
}

void RobotControlNode::publish(int32_t linear_velocity, int32_t angular_velocity) {
    auto message = robot_interfaces::msg::Velocity();
    message.linear_velocity = linear_velocity;
    message.angular_velocity = angular_velocity;

    RCLCPP_INFO(this->get_logger(), "Publishing:\n Linear velocity: '%d', Rotational velocity: '%d'", message.linear_velocity, message.angular_velocity);

    velocity_publisher->publish(message);
}

void RobotControlNode::position_topic_callback(const robot_interfaces::msg::Odometry::SharedPtr msg) const {
    
    state_machine.r_odometry[0] = msg->x;
    state_machine.r_odometry[1] = msg->y;
    state_machine.r_odometry[2] = msg->theta;
    
}

void RobotControlNode::command_topic_callback(const robot_interfaces::msg::Command::SharedPtr msg) const {
    
    state_machine.change_state(msg->command);

    state_machine.g_odometry[0] = msg->odometry.x;
    state_machine.g_odometry[1] = msg->odometry.y;
    state_machine.g_odometry[2] = msg->odometry.theta;

}

void RobotControlNode::joystick_topic_callback(const robot_interfaces::msg::Velocity::SharedPtr msg) const {

    state_machine.velocity[0] = msg->linear_velocity;
    state_machine.velocity[1] = msg->angular_velocity;

}
