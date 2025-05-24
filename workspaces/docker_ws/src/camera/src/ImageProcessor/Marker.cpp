#include "ImageProcessor.hpp"
#include <cmath>
#include <iostream>

namespace ImageProcessor {
    
    Marker::Marker() {}
    
    Marker::Marker( int marker_id, 
        cv::Point2f center, 
        cv::Point2f main_corner, 
        float yaw_degree) :    marker_id(marker_id), 
                                center(center), 
                                main_corner(main_corner), 
                                yaw_degree(yaw_degree) {}

    
    Marker Marker::marker_create(int marker_id, std::vector<cv::Point2f> corners) {
        // top-left corner
        cv::Point2f main_corner(corners[0]);
        
        // the mid-point between [0] and [2] corners
        cv::Point2f center((corners[0].x + corners[2].x) / 2, (corners[0].y + corners[2].y) / 2);
        
        // atan of [0] and [1] triangle
        float yaw_degree = std::atan((corners[1].y - corners[0].y) / (corners[1].x - corners[0].x)) * 180 / M_PI;
    
        return (Marker){
            marker_id,
            center, 
            main_corner, 
            yaw_degree

        };
    }
    
};
