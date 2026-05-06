import random
import math
import numpy as np


class Pose():
    def __init__(self, x, y, theta=0):
        self.x = x
        self.y = y
        self.theta = theta

    def print(self):
        print(f"Pose: x: {self.x}, y: {self.y}, theta: {self.theta}")

class AStarNode:
    def __init__(self, pose, parent, dist_from_start, dist_from_end):
        self.parent = parent
        self.dist_from_start = dist_from_start
        self.dist_from_end = dist_from_end
        self.cost = self.dist_from_start + self.dist_from_end
        self.pose = pose

class AStar:

    def __init__(self, grid, pose, goal):

        self.grid = grid
        self.pose = pose
        self.goal = goal

        self.open_list = [] 

        self.closed_list = []

        start_node = AStarNode(pose, None, self.calc_cost(self.pose, pose), self.calc_cost(self.goal, pose))

        self.open_list.append(start_node)

    def a_star(self):
        while True:
            current = self.get_lowest_cost_node()
            self.closed_list.append(current)
            self.open_list.remove(current)
            current.pose.print()

            if current.pose.x == self.goal.x and current.pose.y == self.goal.y:
                break
            
            neighbors = self.get_neighbors(current)

            for neighbor in neighbors:
                
                is_in_closed, node = self.check_if_node_in_closed(neighbor)
                if is_in_closed:
                    continue

                is_in_open, node = self.check_if_node_in_open(neighbor)
                if is_in_open:
                    if neighbor.cost < node.cost:
                        self.open_list.remove(node)
                        self.open_list.append(neighbor)
                else:
                    self.open_list.append(neighbor)
                #neighbor.pose.print()

        path = self.get_path()
        return path


    def get_path(self):
        path = []
        #node = self.get_node_from_closed_list(self.goal)
        #while node is not None:
        #    path.insert(0, node)
        #    node = node.parent
        
        stack = []
        node = self.get_node_from_closed_list(self.goal)
        node.pose.theta = self.goal.theta
        while node is not None:
            stack.append(node)
            '''
            if node.parent is not None:
                theta = math.atan2(node.parent.pose.y - node.pose.y, node.pose.x - node.parent.pose.x) * 180 / math.pi
                theta = theta + 360 if theta < 0 else theta
                node.parent.pose.theta = theta
            '''
            node = node.parent


        while stack:
            path.append(stack.pop())

        return path


    def get_node_from_closed_list(self, pose):
        for node in self.closed_list:
            if node.pose.x == pose.x and node.pose.y == pose.y:
                return node
        return False


    def check_if_node_in_closed(self, node):
        for closed_node in self.closed_list:
            if node.pose.x == closed_node.pose.x and node.pose.y == closed_node.pose.y:
                return True, closed_node
            
        return False, node

    def check_if_node_in_open(self, node):
        for open_node in self.open_list:
            if node.pose.x == open_node.pose.x and node.pose.y == open_node.pose.y:
                return True, open_node

        return False, node

    def get_lowest_cost_node(self):
        current = self.open_list[0]
        for node in self.open_list:
            if node.cost < current.cost:
                current = node

        return current

    def get_neighbors(self, node):
        neighbors = []
        for i in range(int(node.pose.x) - 1, int(node.pose.x) + 2):
            if i >= self.grid.shape[1] or i < 0:
                continue
            for j in range(int(node.pose.y) - 1, int(node.pose.y) + 2):
                # check if node not occupied
                if j >= self.grid.shape[0] or j < 0:
                    continue

                if self.grid[j, i] != 255:
                    pose = Pose(i, j)
                    neighbor = AStarNode(pose, node, self.calc_cost(self.pose, pose), self.calc_cost(self.goal, pose))
                    neighbors.append(neighbor)
        return neighbors

    def calc_cost(self, pose1, pose2):
        return int(math.sqrt((pose2.x - pose1.x)**2 + (pose2.y - pose1.y)**2) * 10)

'''
class PathPlanner():
    def path_planning(self, goal):
        pass

class TreeNode():
    def __init__(self, x, y, theta=0):
        self.parent = None
        self.pose = Pose(x, y, theta)
        self.cost = 0
        self.nearest = 0

    def print(self):

        print("Node: ")
        self.pose.print()

        print("parent: ")
        if self.parent is not None:
            self.parent.pose.print()  
        else:
            print("None")

class RRT():
    def __init__(self, grid, pose, goal, max_iter=500, max_step=20):

        self.grid = grid
        self.pose = TreeNode(pose.x, pose.y)
        self.goal = TreeNode(goal.x, goal.y)
        self.max_iter = min(max_iter, 1000)
        self.max_step = max_step
        self.nodes = [self.pose]
        self.set_nodes = set()
        self.path = []
    
    def rrt(self):

        node = None

        for i in range(self.max_iter):

            node = self.add_node()

            if node is None or not node:
                continue

            if self.is_goal(node):
                break

        self.get_path()
        return self.path

    # checks if node is near goal
    def is_goal(self, node):
        if self.calc_distance(node, self.goal) <= 20:
            if not self.is_collided(node, self.goal):
                self.goal.parent = node
                return True
        return False

    def get_path(self):
#TODO
        stack = []
        node = self.goal
        node.pose.theta = 0
        while node is not None:
            stack.append(node)
            if node.parent is not None:
                theta = math.atan2(node.pose.y - node.parent.pose.y, node.pose.x - node.parent.pose.x) 
                theta = theta + 180 if theta < 0 else theta
                node.parent.pose.theta = theta
            node = node.parent


        while stack:
            self.path.append(stack.pop())

    def gen_rand_node(self):
        return TreeNode(random.randint(0, self.grid.shape[1] - 1), random.randint(0, self.grid.shape[0] - 1))
    
    def add_node(self):

        node = self.gen_rand_node()
        
        parent = self.find_nearest(node)

        vect = self.get_unit_vect(node, parent)
        
        # make node in max step
        node = TreeNode(math.floor(parent.pose.x + vect[0] * self.max_step), math.floor(parent.pose.y + vect[1] * self.max_step))
        if node in self.set_nodes:
            return None

        self.set_nodes.add(node)
        
        # check if node is out of pounds
        if node.pose.x > self.grid.shape[1] - 1:
            node.pose.x = self.grid.shape[1] - 1

        if node.pose.x < 0:
            node.pose.x = 0

        if node.pose.y > self.grid.shape[0] - 1:
            node.pose.y = self.grid.shape[0] - 1
        
        if node.pose.y < 0:
            node.pose.y = 0
        
        # check for collisions
        if self.is_collided(node, parent):
            return False
         
        node.parent = parent
        node.nearest = self.calc_distance(node, node.parent)
        node.cost = node.parent.cost + node.nearest

        self.nodes.append(node)
        return node

    def is_collided(self, node, parent):
        vect = self.get_unit_vect(node, parent)

        for i in range(self.max_step):
            if math.floor(parent.pose.x + i * vect[0]) > self.grid.shape[1] - 1 or math.floor(parent.pose.y + i * vect[1]) > self.grid.shape[0] - 1:
                return False
            if self.grid[math.floor(parent.pose.y + i * vect[1]), math.floor(parent.pose.x + i * vect[0])] == 255:
                return True
        return False

    def calc_distance(self, node, other):
        return np.linalg.norm([ (node.pose.x - other.pose.x), (node.pose.y - other.pose.y) ])

    def get_unit_vect(self, node, other):

        magnitude = self.calc_distance(node, other)
        vect = np.array([ (node.pose.x - other.pose.x), (node.pose.y - other.pose.y) ])
        if magnitude == 0:
            return vect

        return vect / magnitude

    def find_nearest(self, node):
        #if self.nodes is None:
        #    return None

        l = 100**3
        nearest = None
        for n in self.nodes:
            s = self.calc_distance(node, n)
            if s < l:
                l = s
                nearest = n

        return nearest

    

class RRTStar():
    def __init__(self, grid, pose, goal, max_iter=500, max_step=20):

        self.grid = grid
        self.pose = TreeNode(pose.x, pose.y)
        self.goal = TreeNode(goal.x, goal.y)
        self.max_iter = min(max_iter, 1000)
        self.max_step = max_step
        self.nodes = [self.pose]
        self.set_nodes = set()
        self.path = []
    
    def rrt_star(self):

        node = None

        for i in range(self.max_iter):

            node = self.add_node()

            if node is None or not node:
                continue

            if self.is_goal(node):
                break

        self.get_path()
        return self.path

    # checks if node is near goal
    def is_goal(self, node):
        if self.calc_distance(node, self.goal) <= 20:
            if not self.is_collided(node, self.goal):
                self.goal.parent = node
                return True
        return False

    def get_path(self):
#TODO
        stack = []
        node = self.goal
        node.pose.theta = 0
        while node is not None:
            stack.append(node)
            if node.parent is not None:
                theta = math.atan2(node.pose.y - node.parent.pose.y, node.pose.x - node.parent.pose.x) 
                theta = theta + 180 if theta < 0 else theta
                node.parent.pose.theta = theta
            node = node.parent


        while stack:
            self.path.append(stack.pop())



    def gen_rand_node(self):
        return TreeNode(random.randint(0, self.grid.shape[1] - 1), random.randint(0, self.grid.shape[0] - 1))
    
    def add_node(self):

        node = self.gen_rand_node()
        
        parent = self.find_nearest(node)

        vect = self.get_unit_vect(node, parent)
        
        # make node in max step
        node = TreeNode(math.floor(parent.pose.x + vect[0] * self.max_step), math.floor(parent.pose.y + vect[1] * self.max_step))

        if node in self.set_nodes:
            return None

        self.set_nodes.add(node)
        
        # check if node is out of pounds
        if node.pose.x > self.grid.shape[1] - 1:
            node.pose.x = self.grid.shape[1] - 1

        if node.pose.x < 0:
            node.pose.x = 0

        if node.pose.y > self.grid.shape[0] - 1:
            node.pose.y = self.grid.shape[0] - 1
        
        if node.pose.y < 0:
            node.pose.y = 0
        
        # check for collisions
        if self.is_collided(node, parent):
            return False
         
        node.parent = parent
        node.nearest = self.calc_distance(node, node.parent)
        node.cost = node.parent.cost + node.nearest

        self.rewire(node)

        self.nodes.append(node)
        return node

    def get_neighbors(self, node):
        neighbors = [neighbor for neighbor in self.nodes if self.calc_distance(node, neighbor) <= self.max_step]
        return neighbors

    def rewire(self, node):
        neighbors = self.get_neighbors(node)
        for neighbor in neighbors:
            new_nearest = self.calc_distance(node, neighbor)
            new_cost = node.cost + new_nearest
            if neighbor.cost < new_cost or self.is_collided(node, neighbor):
                continue

            neighbor.parent = node
            neighbor.cost = new_cost
            neighbor.nearest = new_nearest

    def is_collided(self, node, parent):
        vect = self.get_unit_vect(node, parent)

        for i in range(self.max_step):
            if math.floor(parent.pose.x + i * vect[0]) > self.grid.shape[1] - 1 or math.floor(parent.pose.y + i * vect[1]) > self.grid.shape[0] - 1:
                return False
            if self.grid[math.floor(parent.pose.y + i * vect[1]), math.floor(parent.pose.x + i * vect[0])] == 255:
                return True
        return False

    def calc_distance(self, node, other):
        return np.linalg.norm([ (node.pose.x - other.pose.x), (node.pose.y - other.pose.y) ])

    def get_unit_vect(self, node, other):

        magnitude = self.calc_distance(node, other)
        vect = np.array([ (node.pose.x - other.pose.x), (node.pose.y - other.pose.y) ])
        if magnitude == 0:
            return vect

        return vect / magnitude

    def find_nearest(self, node):
        #if self.nodes is None:
        #    return None

        l = 100**3
        nearest = None
        for n in self.nodes:
            s = self.calc_distance(node, n)
            if s < l:
                l = s
                nearest = n

        return nearest
'''
