#ifndef OBJECTDETECTOR_BJORNMAGNUS_H
#define OBJECTDETECTOR_BJORNMAGNUS_H

#include <opencv2/core.hpp>       
#include <opencv2/imgproc.hpp>     
#include <opencv2/highgui.hpp>     
#include <opencv2/features2d.hpp>  


// Fits a box with given size to contain highest amount of features, the box get place moth horizontally and vertically 
// Inputs:
// img          -Image to place the box on (Use only the dimention for grid search)
// Keypoints -Vector of keypoints who you want the box fitted to 
// boxWidht      -Width of the box 
// boxHeight     -Height of the boz
// bestBox      -A rect to where the best box get written to 
void fitBox(const cv::Mat &img, std::vector<cv::KeyPoint> &Keypoints, const int boxWidth, const int boxHeight, cv::Rect &bestBox);

// Find a box centred around the features that can be fitted in to a single box given by the size of the input
// Inputs:
// img           -Image to place the box on (Use only the dimention for grid search)
// Keypoints -Vector of keypoints who you want the box fitted to 
// boxWidht      -Width of the box 
// boxHeight     -Height of the boz
// bestBoxCented -A rect to where the best centred box get written to 
void fitBoxCentred(const cv::Mat &img, std::vector<cv::KeyPoint> &Keypoints, const int boxWidth, const int boxHeight, cv::Rect &bestBoxCentred);

// Dettects all object in the image based on canny and findContours
// Inputs: 
// inputImg      -Image to detect objects 
// detectedBoxes -Vector containing all the Rects from the object detection 
// maxArea       -Maximum area for 
void detectAllObjects(const cv::Mat &inputImg,std::vector<cv::Rect> &detectedBoxes, int maxArea);


// Given a list of boxes and keypoints find the box that contains the most keypoints 
// Inputs:
// Keypoints -Vector of keypoints who you want the box fitted to 
// boxes         -List of boxes to searc through 
// bestBox       -A rect to where the best box get written to 
void findBestBox(std::vector<cv::KeyPoint> &Keypoints,std::vector<cv::Rect> boxes,cv::Rect &bestBox);





#endif