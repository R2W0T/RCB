import math

from robot_interfaces.msg import Speed
from robot_interfaces.msg import Odometry 

#TODO: state enum

class MotionController():
    def __init__(self):
        self.speed = Speed(rotational_speed=0, linear_spped=0)
        self.goal = Odometry(x=0, y=0, theta=0)
        self.kl = 0.6
        self.ka = 0.1
        self.arrived_at_goal = False
        self.state = False

    def get_speed(self):
        return self.speed

    def set_goal(self, goal: Odometry):
        self.state = False
        self.goal = goal

    # arrived at goal
    def get_state(self):
        return self.state

    def set_speed(self, pose: Odometry):
        pass
'''
        d_x = self.goal.x - pose.x
        d_y = self.goal.y - pose.y

        d_theta = self.goal.theta - pose.theta
        d_theta = (d_theta - 360 if d_theta > 360 else d_theta + 360 if d_theta < 0 else d_theta)
 

        to_goal_theta = math.atan2(d_y, d_x) * 180 / math.pi
        to_goal_theta = to_goal_theta if to_goal_theta > 0 else 360 + to_goal_theta 

        d_to_goal_theta = to_goal_theta - pose.theta
        # making goal in range [0, 360]
        d_to_goal_theta = (d_to_goal_theta - 360 if d_to_goal_theta > 360 else d_to_goal_theta + 360 if d_to_goal_theta < 0 else d_to_goal_theta)

        if abs(d_to_goal_theta) >= 10 and not self.arrived_at_goal and not self.state:

#            print("to goal theta")
            self.speed.linear_speed = 0
            self.speed.rotational_speed = self.ka * d_to_goal_theta
            self.speed.rotational_speed = int((self.speed.rotational_speed if self.speed.rotational_speed in range(-360, 360) else 360 if self.speed.rotational_speed > 360 else -360) * 100 / 360)

        elif abs(d_x) >= 10 or abs(d_y) >= 10 and not self.arrived_at_goal and not self.state:
#            print("linear")
            self.speed.rotational_speed = 0
            self.speed.linear_speed = self.kl * math.sqrt(math.pow(d_x, 2) + math.pow(d_y, 2))
            self.speed.linear_speed = int((self.speed.linear_speed if self.speed.linear_speed < 1000 else 1000) * 100 / 1000)

        elif abs(d_x) <= 10 and abs(d_y) <= 10 and not self.arrived_at_goal and not self.state:
#            print("at goal")
            self.arrived_at_goal = True

        elif abs(d_theta) > 5 and self.arrived_at_goal and not self.state:
#            print("at goal theta")
            self.speed.linear_speed = 0
            self.speed.rotational_speed = self.ka * d_theta
            self.speed.rotational_speed = int((self.speed.rotational_speed if self.speed.rotational_speed in range(-360, 360) else 360 if self.speed.rotational_speed > 360 else -360) * 100 / 360)
        
        else:
#            print("done")
            self.speed = Speed(rotational_speed=0, linear_spped=0)
            self.arrived_at_goal = False
            self.state = True
        
        
'''
