#pragma once

#include <inttypes.h>
#include "robot_control/robot_control_node.hpp"

enum STATES {
    SLEEP = 0,
    GO_TO_GOAL = 1,
    JOYSTICK = 2
};

class state_machine_t {
  public:
    state_machine_t();

    ~state_machine_t();

    // this should be after rclcpp::init()
    void init();

    void change_state(uint8_t state);
    
    void run();

    void sleep();
    void go_to_goal();
    void joystick();

    float g_odometry[3] = {0.0, 0.0, 0.0}; 
    float r_odometry[3] = {0.0, 0.0, 0.0};
    int32_t speed[2] = {0, 0};

  private:
    uint8_t state = SLEEP;
    
    std::shared_ptr<RobotControlNode> node;



};