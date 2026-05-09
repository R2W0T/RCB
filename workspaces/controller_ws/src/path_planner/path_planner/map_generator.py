import cv2
import numpy as np

from robot_interfaces.msg import Odometry

class MapGenerator():

    def __init__(self):
        self.grid_map = None
        self.img = None

    def set_img(self, img, pose: Odometry):
        _, binary_img = cv2.threshold(img, 80, 255, cv2.THRESH_BINARY)
        self.img = self.remove_rectangle_from_matrix(binary_img, (pose.x, pose.y), 220, 230, -pose.theta, 255)

    def get_grid_map(self):
        return self.grid_map

    def generate_map(self, pose):
        
        binary_img = self.img 
        grid_rows = binary_img.shape[0]
        grid_cols = binary_img.shape[1]
        
        # Initialize occupancy grid

        #invert image
        inverted_binary_img = cv2.bitwise_not(binary_img)
        
        inverted_binary_img_no_robot = self.remove_rectangle_from_matrix(inverted_binary_img, (pose.x, pose.y), 220, 230, -pose.theta, 0)

        #find contours
        contours, _ = cv2.findContours(inverted_binary_img_no_robot, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        
        img_copy = inverted_binary_img_no_robot.copy()
        padding = 30
        # loop through contours
        for index in range(len(contours)):
            # take contour
            cnt=contours[index]
            # find coordinates
            x,y,w,h = cv2.boundingRect(cnt)
            # if object is rubble
            if w < 30 and h < 30:
                continue
            else:
                #inflation
                x -= padding
                y -= padding
                w += 2 * padding
                h += 2 * padding
                # draw rectangle to original image
                cv2.rectangle(img_copy,(x,y),(x+w,y+h),255,-1)

        for index in range(len(contours)):
            # take contour
            cnt=contours[index]
            # find coordinates
            x,y,w,h = cv2.boundingRect(cnt)
            # if object is rubble
            if w < 40 and h < 40:
                #inflation
                x -= 10
                y -= 10
                w += 2 * 10
                h += 2 * 10
                # draw rectangle to original image
                cv2.rectangle(img_copy,(x,y),(x+w,y+h),0,-1)

        border_type = cv2.BORDER_CONSTANT
        border_color = [0, 0, 0] # Black in BGR

        # Apply the border
        self.grid_map = self.remove_rectangle_from_matrix(img_copy, (pose.x, pose.y), 220, 230, -pose.theta, 0)


    
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
