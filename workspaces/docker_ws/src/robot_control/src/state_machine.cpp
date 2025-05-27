#include "robot_control/state_machine.hpp"

#include <iostream>
#include <memory>

#include <rclcpp/rclcpp.hpp>

state_machine_t::state_machine_t() {
    // node = std::make_shared<RobotControlNode>();
}

state_machine_t::~state_machine_t() {}

// this should be after rclcpp::init()
void state_machine_t::init() {

    // this should be after rclcpp::init()
    node = std::make_shared<RobotControlNode>();

}


void state_machine_t::change_state(uint8_t state) {
    this->state = state; 
}

void state_machine_t::run() {
    
    
    while (1) {
        
        rclcpp::spin_some(node);

        switch(state) {
            case SLEEP:
                sleep();
                break;
            
            case GO_TO_GOAL:
                go_to_goal();
                break;
            
            case JOYSTICK:
                joystick();
                break;

            default:
                break;
        }
    }
    
}

void state_machine_t::sleep() {
    node->publish(0, 0);
}

void state_machine_t::go_to_goal() {

    // compute motor speeds
    float d_x = g_odometry[0] - r_odometry[0];
    float d_y = g_odometry[1] - r_odometry[1];
    

    if((d_x * d_x) + (d_y * d_y) >= 0.05) {

        speed[0] = (uint32_t)(1 * (sqrt(pow(d_x, 2) + pow(d_y, 2))) + 0.5);
        speed[1] =  (uint32_t)(0.3 * (atan2(d_y, d_x) - r_odometry[2]) + 0.5);

    } else {
        speed[0] = 0;
        speed[1] = (uint32_t)(0.3 * (g_odometry[2] - r_odometry[2]));
    }

    node->publish(speed[0], speed[1]);

}

void state_machine_t::joystick() {
    node->publish(speed[0], speed[1]);
}

