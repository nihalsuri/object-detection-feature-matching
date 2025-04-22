#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

#include "Utils/inputProcessing_MaxPries.h"
#include "ObjectDetector/featureDetection_MaxPries.h"
#include "FeatureMatcher/featureMatching_MaxPries.h"






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
    loadInput(testImage, pathListSugarTest[1]);
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


    //Draw the good keypoints
    cv::Mat outImage;
    cv::Scalar color( 0, 0, 255 );
    cv::drawKeypoints(testImage, goodKeypoints, outImage, color);
    namedWindow("TEST", cv::WINDOW_AUTOSIZE);
    cv::imshow("TEST", outImage);
    cv::waitKey(0);
    

    return 0;
}