#include "robot_control/state_machine.hpp"

#include <iostream>
#include <memory>

#include <rclcpp/rclcpp.hpp>

#include <iostream>
#include <chrono>
#include <thread>

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

        std::this_thread::sleep_for(std::chrono::milliseconds(10));    
        
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

    // var fot checking if robot arrived at the goal to change state and fix orientation
    static bool arrived_at_goal = false;
    
    const int linear_kp = 2;
    const int angular_kp = 6;
    // compute motor speeds
    float d_x = g_odometry[0] - r_odometry[0];
    float d_y = g_odometry[1] - r_odometry[1];

    // check the distance to goal
    if(sqrt(pow(d_x, 2) + pow(d_y, 2)) >= 15 && !arrived_at_goal) {

        speed[0] = (uint32_t)(linear_kp * (sqrt(pow(d_x, 2) + pow(d_y, 2))) + 0.5);
        speed[1] =  (uint32_t)(angular_kp * ((atan2(d_y, d_x) * 180 / M_PI) - r_odometry[2]) + 0.5);

    } else {
        speed[0] = 0;
        arrived_at_goal = true;
    }

    if(arrived_at_goal && abs(g_odometry[2] - r_odometry[2]) > 5) { 
        speed[1] = (uint32_t)(angular_kp * (g_odometry[2] - r_odometry[2]));
    } else if( arrived_at_goal && abs(g_odometry[2] - r_odometry[2]) <= 5) {
        speed[1] = 0;
        arrived_at_goal = false;
        this->change_state(SLEEP);
    }
    // limit linear speed to 1000 and turn it to percentage
    // limit angular speed to 360 and turn it to percentage
    node->publish(  ((speed[0] > 1000 ? 1000 : speed[0] < -1000 ? -1000 : speed[0]) * 100 / 1000), 
                    (speed[1] > 360 ? 360 : speed[1] < -360 ? -360 : speed[1]) * 100 / 360);

}

void state_machine_t::joystick() {

    // from input to percentage
    // speed[0] = (int32_t)(speed[0] * 100 / 32767);
    // speed[1] = (int32_t)(speed[1] * 100 / 32767);
    
    node->publish((speed[0] * 100 / 32767), (speed[1] * 100 / 32767));

}

