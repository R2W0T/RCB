#include "ImageProcessor.hpp"
#include <cmath>
#include <iostream>

namespace ImageProcessor {

    ArucoMarkerProcessor::ArucoMarkerProcessor(int dictNum) {
        // dict init
        dict = cv::aruco::getPredefinedDictionary(dictNum);

    }

    // containing foler ending with '/'
    void ArucoMarkerProcessor::marker_generate(int marker_id, int size, std::string path_to_containing_folder) {

        cv::Mat marker_image;

        cv::aruco::generateImageMarker(dict, marker_id, size, marker_image, 1);

        cv::imwrite(path_to_containing_folder + "marker" + std::to_string(marker_id) + ".png", marker_image);
    }

    void ArucoMarkerProcessor::markers_detect(cv::Mat &img) {

        cv::aruco::DetectorParameters detector_params = cv::aruco::DetectorParameters();
        cv::aruco::ArucoDetector detector(dict, detector_params);
        
        std::vector<std::vector<cv::Point2f>> corners;
        std::vector<int> markers_ids;

        detector.detectMarkers(img, corners, markers_ids);
    
        for(unsigned int i = 0; i < markers_ids.size(); i++) {
            markers.push_back(Marker::marker_create(markers_ids[i], corners[i]));
        }

        #ifdef PRINT_DETECTED_MARKERS
            cv::aruco::drawDetectedMarkers(img, corners, markers_ids);
        #endif
    }

                
    std::vector<Marker>& ArucoMarkerProcessor::markers_get() {
        return markers;
    }


    Marker ArucoMarkerProcessor::marker_get(int marker_id) {
        
        for(auto marker : markers) {
            if (marker.marker_id == marker_id) {
                return marker;
            }
        }

        return Marker();
    }

        
};
