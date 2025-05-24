#include "ImageProcessor.hpp"

namespace ImageProcessor {

    ImageProcessor::ImageProcessor( int dict, 
                    cv::Mat &img,
                    std::array<int, 4> &markers_cw_ids,
                    cv::Size size,
                    int robot_marker_id
                ) : aruco_proc(dict), img(img), markers_cw_ids(markers_cw_ids),size(size) {
        
        // do image transformation
        dst_points = {cv::Point2f(0, 0), cv::Point2f(size.width, 0), cv::Point2f(0, size.height), cv::Point2f(size.width, size.height)};
        
        cv::Mat mat = (cv::Mat_<double>(3, 3) << 1.38061023e+03, 0.00000000e+00, 9.71110427e+02,
                                                    0.00000000e+00, 1.37834276e+03, 5.08515340e+02, 
                                                    0.00000000e+00, 0.00000000e+00, 1.00000000e+00);
                                            

        cv::Mat distortion_coeff = (cv::Mat_<double>(1, 5) << 0.1172886, -0.3268505, -0.00110654, 0.00121132, 0.27603067);
        
        camera_matrix = mat.clone();
        distortion_coefficient = distortion_coeff.clone();
    }
    
                // this method will update the image and perform perspective transformation on it 
    // for further processing and calculate robot position relative to the transformed image
    void ImageProcessor::image_update(cv::Mat &img) {

        std::array<cv::Point2f, 4> src_corners;
        
        // this->img = img.clone();
        cv::undistort(img, this->img, camera_matrix, distortion_coefficient);
        
        aruco_proc.markers_detect(img);
        
        ImageTransformationProcessor::get_corner_markers(src_corners, markers_cw_ids, aruco_proc.markers_get());

        ImageTransformationProcessor::perspective_transform(this->img, this->img, src_corners, dst_points, size);

        aruco_proc.markers_detect(this->img);

        robot = aruco_proc.marker_get(robot.marker_id);
        
    }
    void ImageProcessor::image_print() {
        cv::imshow("img proc", img);
        // cv::waitKey(-1);
        // cv::destroyAllWindows();

    }

    Marker& ImageProcessor::robot_get() {
        return robot;
    }
    
    cv::Mat& ImageProcessor::img_get() {
        return img;
    }

    bool ImageProcessor::get_is_transformed() {
        return is_transformed;
    }
    bool ImageProcessor::get_is_robot_detected() {
        return is_robot_detected;
    }

}
