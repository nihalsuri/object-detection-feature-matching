#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

#include "Utils/inputProcessing_MaxPries.h"
#include "Utils/OutputProcessing_BjornMagnus.h"
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
    cv::Mat testImage;
    cv::Mat descriptorsTest;
    std::vector<cv::KeyPoint> keypointsTest;
    std::string imagePath = pathListSugarTest[3];
    loadInput(testImage, imagePath);
    computeFeaturesSingleImage(testImage, descriptorsTest, keypointsTest);
    

    //Match the features of the image to those of the model
    std::vector<std::vector<cv::DMatch>> matches;
    matchFromDescriptors(descriptorsTest, descriptorList, matches);

    
    //Filter only good matches, using the ratio test
    std::vector<cv::DMatch> goodMatches;
    ratioTest(matches, goodMatches);


    //Select all keypoints of the test image corresponding to good matches
    std::vector<cv::KeyPoint> goodKeypoints;
    keypointSelection(goodKeypoints, goodMatches, keypointsTest);


    //Find position of rectangl that fit most keypoints 
    cv::Rect bestBox;
    fitBox(testImage,goodKeypoints,300,150,bestBox);
    //Find position of rectangl that fit most keypoints and centre the rectangle around the keypoints 
    cv::Rect bestBoxCentred;
    fitBoxCentred(testImage,goodKeypoints,300,150,bestBoxCentred);
    //Find all the object based on canny edge detection 
    std::vector<cv::Rect> boxes;
    detectAllObjects(testImage,boxes, 100000);
    //Find the rectangle that fits the most keypoints 
    cv::Rect bestBox2;
    findBestBox(goodKeypoints,boxes, bestBox2);



    //Draw the good keypoints
    cv::Mat outImage;
    cv::Scalar color( 0, 0, 255 );
    cv::drawKeypoints(testImage, goodKeypoints, outImage, color);

    //Draw the Boxes 
    cv::rectangle(outImage, bestBox, cv::Scalar(0, 0, 255),2);
    cv::rectangle(outImage, bestBox2, cv::Scalar(0, 255, 0),2);
    cv::rectangle(outImage, bestBoxCentred, cv::Scalar(255, 0, 0),2);

    //Open image
    openImage(outImage,1,"Test");

    //Save image with original name + _output.jpg saved to given path 
    saveImage(outImage,imagePath,"../data/Output/","_output.jpg");

    return 0;
}