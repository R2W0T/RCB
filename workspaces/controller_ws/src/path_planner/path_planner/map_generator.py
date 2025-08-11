import cv2
import numpy as np

from robot_interfaces.msg import Odometry

class MapGenerator():

    def __init__(self):
        self.grid_map = None
        self.img = None

    def set_img(self, img):
        self.img = img

    def get_grid_map(self):
        return self.grid_map

    def generate_map(self, pose):

        gray_img = cv2.cvtColor(self.img, cv2.COLOR_BGR2GRAY)  

        _, binary_img = cv2.threshold(gray_img, 127, 255, cv2.THRESH_BINARY)
        grid_rows = binary_img.shape[0]
        grid_cols = binary_img.shape[1]
        
        # Initialize occupancy grid
        cv2.imshow("binary image", binary_img)

        #invert image
        inverted_binary_img = cv2.bitwise_not(binary_img)
        cv2.imshow("inverted binary image", inverted_binary_img)
        
        inverted_binary_img_no_robot = self.remove_rectangle_from_matrix(inverted_binary_img, (pose.x, pose.y), 450, 300, pose.theta)
        cv2.imshow("inverted binary image no robot", inverted_binary_img_no_robot)

        #find contours
        contours, _ = cv2.findContours(inverted_binary_img_no_robot, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        
        img_copy = inverted_binary_img_no_robot.copy()
        padding = 100
        # loop through contours
        for index in range(len(contours)):
            # take contour
            cnt=contours[index]
            # find coordinates
            x,y,w,h = cv2.boundingRect(cnt)
            x -= padding
            y -= padding
            w += 2 * padding
            h += 2 * padding
            # draw rectangle to original image
            cv2.rectangle(img_copy,(x,y),(x+w,y+h),255,2)
        
        cv2.imshow("image with contours", img_copy)
        # Define border type and color (e.g., BORDER_CONSTANT with black color)
        border_type = cv2.BORDER_CONSTANT
        border_color = [0, 0, 0] # Black in BGR

        # Apply the border
        self.grid_map = img_copy.copy()#cv2.copyMakeBorder(img_copy, padding, padding, padding, padding, border_type, value=255)

        cv2.line(self.grid_map, (padding, 0), (padding, self.grid_map.shape[0]), 255, 2)
        cv2.line(self.grid_map, (self.grid_map.shape[1] - padding, 0), (self.grid_map.shape[1] - padding, self.grid_map.shape[0]), 255, 2)
        cv2.line(self.grid_map, (0, padding), (self.grid_map.shape[1], padding), 255, 2)
        cv2.line(self.grid_map, (0, self.grid_map.shape[0] - padding), (self.grid_map.shape[1], self.grid_map.shape[0] - padding), 255, 2)
        cv2.imshow("grid", self.grid_map)
    
        cv2.waitKey(2)

    
    def remove_rectangle_from_matrix(self, matrix, center, width, height, angle_degrees):
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
            result_matrix[mask_2d] = 0 # Or any other desired fill value
            return result_matrix

""" # Populate the occupancy grid
        for r in range(grid_rows):
            for c in range(grid_cols):
                # Check if the cell region contains occupied pixels (e.g., any dark pixel)
                if binary_image[r, c] == 255:
                    self.grid_map[r, c] = 255
                else:
                    self.grid_map[r, c] = 0

        # remove robot from map_grid  
        #self.grid_map = self.remove_rectangle_from_matrix(self.grid_map, [400, 400], 200, 200, pose.theta)   
"""
