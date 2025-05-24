#include "robot_control/robot_control_node.hpp"
#include "robot_control/state_machine.hpp"
#include <iostream>
#include "rclcpp/rclcpp.hpp"

state_machine_t state_machine;

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  
  // state_machine.init();
  state_machine.run();
  std::cout << "Hello, World!\n";
  rclcpp::shutdown();

  return 0;
}