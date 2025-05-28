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
                    int32_t y = axes[0].y;


                    node->publish(y, x);   
                }

                break;
            default:
                /* Ignore init events. */
                break;
        }
        
        fflush(stdout);
    }

    close(js);

  
    rclcpp::shutdown();
     
}