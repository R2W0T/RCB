import math
from enum import Enum

from robot_interfaces.msg import Odometry, Velocity 

#TODO: state enum
class MotionControllerState(Enum):
    SLEEP = 0
    GO_TO_GOAL = 1
    AT_GOAL = 2
    ARRIVED = 3

class PurePursuitMotionController:
    def __init__(self, look_ahead_distance, path=None):
        self.ld = look_ahead_distance
        self.path = path
        self.velocity = Velocity(linear_velocity = 0, angular_velocity = 0)
        self.last_goal_point = None

        self.kl = 0.5
        self.ka = 2
        self.state = MotionControllerState.SLEEP


    def set_path(self, path):
        self.path = path

        self.state = MotionControllerState.GO_TO_GOAL

        self.last_goal_point = path[0]

    def get_state(self):
        return self.state == MotionControllerState.ARRIVED

    def get_velocity(self):
        return self.velocity

    #point[0, 1, 2] = {x, y, theta}
    def calc_dist(self, point1: list, point2: list):
        return int(math.floor(math.sqrt((point1[0] - point2[0]) ** 2 + (point1[1] - point2[1]) ** 2)))

    #current_pose[0, 1, 2] = {x, y, theta}
    def set_velocity(self, current_pose: list):

        # getting intersection points
        goal_point = None

        if (self.last_goal_point[0] == self.path[-1][0] and self.last_goal_point[1] == self.path[-1][1]) or self.calc_dist(current_pose, self.path[-1]) < self.ld:
            goal_point = self.path[-1]
        else:
            for point in self.path:
                if self.calc_dist(current_pose, point) == self.ld:
                    # getting the last point
                    goal_point = point
        
        _theta = 0

        # determine goal point
        if goal_point is None:
            goal_point = self.last_goal_point
        else:
            self.last_goal_point = goal_point

        if abs(current_pose[0] - self.path[-1][0]) <= 10 and abs(current_pose[1] - self.path[-1][1]) <= 10:
            self.state = MotionControllerState.AT_GOAL

        d_theta = self.path[-1][2] - current_pose[2]

        # making goal in range ]-180, 180]
        d_theta = (     d_theta - 360 if d_theta > 180 
                   else d_theta + 360 if d_theta <= -180 
                   else d_theta)
        
        if self.state == MotionControllerState.AT_GOAL and abs(d_theta) < 10:
            self.state = MotionControllerState.ARRIVED

        match self.state:
            case MotionControllerState.GO_TO_GOAL:
                self.velocity.linear_velocity = self.kl * self.calc_dist(current_pose, goal_point)
                self.velocity.linear_velocity = int(min(max(self.velocity.linear_velocity, -300), 300) * 100 / 300)
            
                # calculationg angular velocity
                _theta = math.atan2(current_pose[1] - goal_point[1], goal_point[0] - current_pose[0]) * 180 / math.pi
                _theta = _theta if _theta > 0 else 360 + _theta 
        
                # (+ 180) for making the axis same
                d_theta = _theta - current_pose[2]

                # making goal in range ]-180, 180]
                d_theta = (      d_theta - 360 if d_theta > 180 
                            else d_theta + 360 if d_theta <= -180 
                            else d_theta)

                if abs(d_theta) > 90:
                    self.velocity.linear_velocity = 0

                self.velocity.angular_velocity = -self.ka * d_theta
                self.velocity.angular_velocity = int(min(max(self.velocity.angular_velocity, -180), 180) * 100 / 180)

            case MotionControllerState.AT_GOAL:
                self.velocity.linear_velocity = 0

                d_theta = self.path[-1][2] - current_pose[2]

                # making goal in range ]-180, 180]
                d_theta = (      d_theta - 360 if d_theta > 180 
                            else d_theta + 360 if d_theta <= -180 
                            else d_theta)

                self.velocity.angular_velocity = -self.ka * d_theta
                self.velocity.angular_velocity = int(min(max(self.velocity.angular_velocity, -180), 180) * 100 / 180)

            case MotionControllerState.ARRIVED:
                self.velocity.angular_velocity = 0
                self.velocity.linear_velocity = 0
        

'''
class MotionController():
    def __init__(self):
        self.velocity = Velocity(linear_velocity=0, angular_velocity=0)
        self.goal = Odometry(x=0, y=0, theta=0)
        self.kl = 0.4
        self.ka = 3
        self.arrived_at_goal = False
        self.facing_goal = False
        self.state = False

    def get_velocity(self):
        return self.velocity

    def set_goal(self, goal: Odometry):
        self.state = False
        self.arrived_at_goal = False
        self.facing_goal = False
        self.goal = goal

    # arrived at goal
    def get_state(self):
        return self.state

    def set_velocity(self, pose: Odometry):

        d_x = self.goal.x - pose.x
        d_y = self.goal.y - pose.y

        d_theta = self.goal.theta - pose.theta
        d_theta = (     d_theta - 360 if d_theta > 180 
                   else d_theta + 360 if d_theta <= -180 
                   else d_theta)

        to_goal_theta = math.atan2(-d_y, d_x) * 180 / math.pi
        to_goal_theta = to_goal_theta if to_goal_theta > 0 else 360 + to_goal_theta 
        
        # (+ 180) for making the axis same
        d_to_goal_theta = to_goal_theta - pose.theta
        # making goal in range ]-180, 180]
        d_to_goal_theta = (     d_to_goal_theta - 360 if d_to_goal_theta > 180 
                            else d_to_goal_theta + 360 if d_to_goal_theta < -180 
                            else d_to_goal_theta)


        print(f"d_x: {d_x}, d_y: {d_y}, d_theta: {d_theta}, to_goal_theta: {to_goal_theta}, d_to_goal_theta: {d_to_goal_theta}")
        if abs(d_to_goal_theta) >= 10 and not self.arrived_at_goal and not self.facing_goal and not self.state:
            self.velocity.linear_velocity = 0
            self.velocity.angular_velocity = -self.ka * d_to_goal_theta
            self.velocity.angular_velocity = int(min(max(self.velocity.angular_velocity, -180), 180) * 100 / 180)

        elif abs(d_to_goal_theta) < 10 and not self.facing_goal:
            self.facing_goal = True

        elif (abs(d_x) >= 10 or abs(d_y) >= 10) and not self.arrived_at_goal and self.facing_goal and not self.state:
            #self.velocity.angular_velocity = 0

            self.velocity.angular_velocity = -self.ka * d_to_goal_theta
            self.velocity.angular_velocity = int(min(max(self.velocity.angular_velocity, -360), 360) * 100 / 360)

            self.velocity.linear_velocity = self.kl * math.sqrt(math.pow(d_x, 2) + math.pow(d_y, 2))
            self.velocity.linear_velocity = int((min(self.velocity.linear_velocity, 400)) * 100 / 400)

        elif (abs(d_x) < 10 or abs(d_y) < 10) and not self.arrived_at_goal and self.facing_goal and not self.state:
            self.arrived_at_goal = True
            self.velocity.angular_velocity = 0
            self.velocity.linear_velocity = 0

        elif abs(d_theta) >= 10 and self.arrived_at_goal and self.facing_goal and not self.state:
            self.velocity.linear_velocity = 0
            self.velocity.angular_velocity = -self.ka * d_theta
            self.velocity.angular_velocity = int(min(max(self.velocity.angular_velocity, -180), 180) * 100 / 180)

        else:
            self.state = True
            self.arrived_at_goal = True
            self.velocity.linear_velocity = 0
            self.velocity.angular_velocity = 0

'''
