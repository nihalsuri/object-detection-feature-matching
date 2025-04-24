#include <opencv2/imgproc.hpp>

#include "Utils/inputProcessing_MaxPries.h"
#include "ObjectDetector/featureDetection_MaxPries.h"



void computeFeaturesSingleImage(const cv::Mat &img, cv::Mat &descriptors, 
    std::vector<cv::KeyPoint> &keypoints, const double sigma)
{
    // Create a cv::SIFT object, which is like a pointer
    cv::Ptr<cv::SIFT> sift = cv::SIFT::create();
    // cv::noArray() stands for an empty mask, 

    // Blurr the image before detection
    if (sigma > 0)
    {
        cv::Size g_size(0,0);
        cv::GaussianBlur(img, img, g_size, sigma, 0);
    }
    

    sift->detectAndCompute(img, cv::noArray(), keypoints, descriptors);
}


void computeFullDescriptorList(const std::vector<std::string> pathList, 
    const std::vector<std::string> maskList,
    cv::Mat &descriptorList)
{
    // Create a cv::SIFT object, which is like a pointer
    cv::Ptr<cv::SIFT> sift = cv::SIFT::create();

    for (int i=0; i<pathList.size(); i++)
    {
        cv::Mat trainImg;
        cv::Mat trainMask;
        loadInput(trainImg, pathList[i]);
        loadInput(trainMask, maskList[i], true);
        

        std::vector<cv::KeyPoint> keypoints;
        cv::Mat descriptors;

        // Detect keypoints within the mask and computes their descriptors
        sift->detectAndCompute(trainImg, trainMask, keypoints, descriptors);

        // Concattenate the descriptors of each training image
        if (!descriptors.empty())
        {
            descriptorList.push_back(descriptors);
        }
    }
}