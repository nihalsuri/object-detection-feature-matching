#include "FeatureMatcher/featureMatching_MaxPries.h"


void matchFromDescriptors(const cv::Mat &dscrTest, const cv::Mat &dscrTrain, 
    std::vector<std::vector<cv::DMatch>> &knnMatches, const int k)
{
    // Create BFMatcher object
    cv::BFMatcher matcher;
    // find the k best matches for each descriptor of the test image
    matcher.knnMatch(dscrTest, dscrTrain, knnMatches, k);
}


void ratioTest(const std::vector<std::vector<cv::DMatch>> &matchesIn,
    std::vector<cv::DMatch> &matchesOut, const double cutOffRatio)
{
    for (const std::vector<cv::DMatch>& match : matchesIn)
    {
        // If the best match is considerably better than the second best, keep it
        // The threshold of 0.75 is given by D. Lowe in his paper (can change this)
        if (match.size() == 2 && match[0].distance < cutOffRatio * match[1].distance)
            matchesOut.push_back(match[0]);
    }
}


void keypointSelection(std::vector<cv::KeyPoint> &goodKeypoints, 
    std::vector<cv::DMatch> goodMatches, const std::vector<cv::KeyPoint> keypoints)
{
    for (cv::DMatch& match : goodMatches)
    {
        // select those keypoints, which have one clear best match
        goodKeypoints.push_back(keypoints[match.queryIdx]);
    }
}