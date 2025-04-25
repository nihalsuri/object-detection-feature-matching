#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

#include "Utils/inputProcessing_MaxPries.h"
#include "Utils/OutputProcessing_BjornMagnus.h"
#include "Utils/outputProcessing_NihalSuri.h"
#include "ObjectDetector/featureDetection_MaxPries.h"
#include "FeatureMatcher/featureMatching_MaxPries.h"
#include "ObjectDetector/ObjectDetector_BjornMagnus.h"


 
int main(int argc, char** argv)
{
    //Collect all filenames from a given directory
    std::vector<std::string> pathListSugarModels = fetchFilenames("../data/004_sugar_box/models", "color.png");
    std::vector<std::string> pathListSugarMask = fetchFilenames("../data/004_sugar_box/models", "mask.png");
    std::vector<std::string> pathListSugarTest = fetchFilenames("../data/004_sugar_box/test_images", "color.jpg");


    //Compute the list of all descriptors for the model "sugar_box"
    cv::Mat descriptorList;
    computeFullDescriptorList(pathListSugarModels, pathListSugarModels, descriptorList);

    

    //Load one test image and compute its keypoints
    cv::Rect objectDeteced,objectDeteced1,objectDeteced2;
    std::string imagePath = pathListSugarTest[8];
    std::vector<cv::KeyPoint> goodKeypoints;
    double sigma = 1;
    double cutOffRatio = 0.77;

    //Find position of rectangle that fit most keypoints
    runDetection(imagePath, descriptorList, 0, 12 , objectDeteced, goodKeypoints, sigma, cutOffRatio);
    //Find position of rectangl that fit most keypoints and centre the rectangle around the keypoints 
    runDetection(imagePath, descriptorList, 1, 12 , objectDeteced1, goodKeypoints, sigma, cutOffRatio);
    //Find all the object based on canny edge detection and find the object containing the most keypoints
    runDetection(imagePath, descriptorList, 2, 12 , objectDeteced2, goodKeypoints, sigma, cutOffRatio);
    
    //Draw the good keypoints
    cv::Mat testImage;
    loadInput(testImage, imagePath);
    cv::Mat outImage;
    cv::Scalar color( 0, 0, 255 );
    cv::drawKeypoints(testImage, goodKeypoints, outImage, color);

    //Draw the Boxes 
    cv::rectangle(outImage, objectDeteced, cv::Scalar(0, 0, 255),2);
    cv::rectangle(outImage, objectDeteced1, cv::Scalar(0, 255, 0),2);
    cv::rectangle(outImage,objectDeteced2, cv::Scalar(255, 0, 0),2);

    //Open image
    openImage(outImage,1,"Test");

    //Save image with original name + _output.jpg saved to given path 
    saveImage(outImage,imagePath,"../results/images/","_output.jpg");

    // write to files for each bounding box method, choose one of them in the end
    std::vector<cv::Rect>mode0;
    mode0.push_back(objectDeteced); 
    writeCoordinates(mode0, imagePath, "../results/coordinates/mode0/", "_output"); 

    std::vector<cv::Rect>mode1;
    mode1.push_back(objectDeteced1); 
    writeCoordinates(mode1, imagePath, "../results/coordinates/mode1/", "_output");

    std::vector<cv::Rect>mode2;
    mode2.push_back(objectDeteced2); 
    writeCoordinates(mode2, imagePath, "../results/coordinates/mode2/", "_output");

    return 0;
}