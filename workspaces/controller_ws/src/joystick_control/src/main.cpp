#include <thread>
#include <chrono>

#include "joystick_control/joystick_control_node.hpp"
#include "joystick_control/joystick.hpp"

#include "rclcpp/rclcpp.hpp"

int main(int argc, char* argv[]) {
 
    rclcpp::init(argc, argv);
  
    // init
    const char* deviceRoute = "/dev/input/js0";
    int js = open(deviceRoute, O_RDONLY);
    if(js == -1) {
        perror("Could not open joystick");
    }

    struct js_event event;
    struct axis_state axes[3] = {0};
    size_t axis;

    auto node = std::make_shared<JoystickControlNode>();

    while (read_event(js, &event) == 0)
    {
        switch (event.type)
        {
            case JS_EVENT_AXIS:
                axis = get_axis_state(&event, axes);
                if (axis < 3){
                    int32_t x = axes[0].x;
                    // reverse value
                    int32_t y = axes[2].x;

                    int32_t z = axes[1].x;

                    int32_t a = axes[5].x;


                    node->publish(y, x);   
                    node->publish_angle(z, a);   
                }

                break;
            default:
                /* Ignore init events. */
                break;
        }
        
        fflush(stdout);

	    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    close(js);

  
    rclcpp::shutdown();
     
}
