#include "ImageProcessor.hpp"
#include <cmath>
#include <iostream>

namespace ImageProcessor {
        
    void ImageTransformationProcessor::perspective_transform(cv::Mat &img, 
                                                            cv::Mat &dst, 
                                                            std::array<cv::Point2f, 4> &src_corners, 
                                                            std::array<cv::Point2f, 4> &dst_corners, 
                                                            cv::Size size
                                                        ) {

        cv::Mat perspective_matrix = cv::getPerspectiveTransform(src_corners, dst_corners);
        cv::warpPerspective(img, dst, perspective_matrix, size);
    }
    
            // ClockWise starting from top left 
    void ImageTransformationProcessor::get_corner_markers(std::array<cv::Point2f, 4> &src_corners, std::array<int, 4> &corner_cw_ids, std::vector<Marker> &markers) {
        
        for(auto marker : markers) {
            if(marker.marker_id == corner_cw_ids[0]) {
                src_corners[0] = marker.main_corner;
            } else if(marker.marker_id == corner_cw_ids[1]) {
                src_corners[1] = marker.main_corner;

            } else if(marker.marker_id == corner_cw_ids[2]) {
                src_corners[3] = marker.main_corner;
                
            } else if(marker.marker_id == corner_cw_ids[3]) {
                src_corners[2] = marker.main_corner;
                
            }
         
        }
    }
    
};
