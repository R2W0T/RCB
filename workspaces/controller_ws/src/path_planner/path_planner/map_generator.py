import cv2
import numpy as np

from robot_interfaces.msg import Odometry

class MapGenerator():

    def __init__(self, padding = 20, rubble_size = 10, robot_width = 60, robot_height = 60):
        self.grid_map = None
        self.img = None
        self.padding = padding 
        self.rubble_size = rubble_size 
        self.robot_width = robot_width 
        self.robot_height = robot_height 

    def set_img(self, img, pose: Odometry):
        _, binary_img = cv2.threshold(img, 80, 255, cv2.THRESH_BINARY)
        self.img = self.remove_rectangle_from_matrix(binary_img, (pose.x, pose.y), self.robot_width, self.robot_height, -pose.theta, 255)
        return self.img

    def get_grid_map(self):
        return self.grid_map

    def generate_map(self, pose):
        
        binary_img = self.img 
        
        #invert image
        inverted_binary_img = cv2.bitwise_not(binary_img)
        
        inverted_binary_img_no_robot = inverted_binary_img

        #find contours
        contours, _ = cv2.findContours(inverted_binary_img_no_robot, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        
        img_copy = inverted_binary_img_no_robot.copy()

        for index in range(len(contours)):
            # take contour
            cnt=contours[index]
            # find coordinates
            x,y,w,h = cv2.boundingRect(cnt)
            # if object is rubble
            if w < self.rubble_size and h < self.rubble_size:
                #inflation
                x -= self.rubble_size
                y -= self.rubble_size
                w += 2 * self.rubble_size
                h += 2 * self.rubble_size
                # draw rectangle to original image
                cv2.rectangle(img_copy,(x,y),(x+w,y+h),0,-1)

            # if object is box
            else:
                #inflation
                x -= self.padding
                y -= self.padding
                w += 2 * self.padding
                h += 2 * self.padding
                # draw rectangle to original image
                cv2.rectangle(img_copy,(x,y),(x+w,y+h),255,-1)
        self.grid_map = img_copy
    
    def remove_rectangle_from_matrix(self, matrix, center, width, height, angle_degrees, value):
        if matrix.ndim == 2 and matrix.shape[1] == 2: # Assuming matrix is a point cloud
            points_to_check = matrix
        elif matrix.ndim == 2: # Assuming matrix is an image
            rows, cols = matrix.shape
            points_to_check = np.array(np.meshgrid(np.arange(cols), np.arange(rows))).reshape(2, -1).T
        else:
            raise ValueError("Unsupported matrix dimension. Expected 2D image or (N, 2) point cloud.")

        angle_rad = np.radians(-angle_degrees) # Rotate back by negative angle
        cos_a, sin_a = np.cos(angle_rad), np.sin(angle_rad)
        inv_rotation_matrix = np.array([[cos_a, -sin_a],
                                        [sin_a, cos_a]])

        # Translate points relative to rectangle center
        translated_points = points_to_check - np.array(center)

        # Rotate points back to align with unrotated rectangle
        rotated_back_points = (inv_rotation_matrix @ translated_points.T).T

        # Check if points are within unrotated rectangle bounds
        x_in_bounds = (rotated_back_points[:, 0] >= -width / 2) & (rotated_back_points[:, 0] <= width / 2)
        y_in_bounds = (rotated_back_points[:, 1] >= -height / 2) & (rotated_back_points[:, 1] <= height / 2)

        points_in_rectangle_mask = x_in_bounds & y_in_bounds

        if matrix.ndim == 2 and matrix.shape[1] == 2: # Point cloud
            return matrix[~points_in_rectangle_mask]
        else: # Image
            result_matrix = matrix.copy()
            rows, cols = matrix.shape
            # Convert flat mask back to 2D for image indexing
            mask_2d = points_in_rectangle_mask.reshape(rows, cols)
            result_matrix[mask_2d] = value # Or any other desired fill value
            return result_matrix
