#pragma once

#include "ImageProcessor.hpp"

namespace ImageProcessor {

    class ArucoMarkerProcessor {
        private:
            cv::aruco::Dictionary dict;
            std::vector<Marker> markers;
            
        public:

            ArucoMarkerProcessor(int dict_num);
        
            void marker_generate(int marker_id, int size, std::string path_to_containing_folder);
            void markers_detect(cv::Mat &img);
            
            std::vector<Marker>& markers_get();

            Marker marker_get(int marker_id);
    };


};
