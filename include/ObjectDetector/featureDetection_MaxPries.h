#ifndef FEATUREDETECTION_MAXPRIES_H
#define FEATUREDETECTION_MAXPRIES_H

#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>

#include <string>
#include <vector>


// Detects all keypoints of an image and computes their descriptors.
// The intended use is for the test images.
// Inputs:
// img         - the image to be analyzed
// descriptors - a cv::Mat object containing all descriptors
// keypoints   - a vector containing all keypoints as cv::Keypoint
void computeFeaturesSingleImage(const cv::Mat &img, cv::Mat &descriptors, 
    std::vector<cv::KeyPoint> &keypoints);


// Computes all descriptors inside a mask for a set of images
// Inputs:
// pathList       - a vector of strings containing the paths to the images
// maskList       - a vector of strings containing the paths to the masks, the
//                  keypoints are only detected inside the mask
// descriptorList - the target for the descriptors. All descriptors for each
//                  image are concatenated 
void computeFullDescriptorList(const std::vector<std::string> pathList, 
    const std::vector<std::string> maskList, cv::Mat &descriptorList);

#endif