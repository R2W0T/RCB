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

        path = self.get_path()
        return path


    def get_path(self):
        path = []
        
        stack = []
        node = self.get_node_from_closed_list(self.goal)
        node.pose.theta = self.goal.theta
        while node is not None:
            stack.append(node)
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