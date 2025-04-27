#include <iostream>
#include <string>
#include <vector>

#include "Utils/inputProcessing_MaxPries.h"
#include "ObjectDetector/objectDetectorAll_MaxPries.h"
#include "Evaluator/evaluator_NihalSuri.h"


int main(int argc, char** argv)
{
    
    std::vector<std::vector<std::string>> allModels, allMasks;
    std::vector<std::string> allTests;
    loadTrainTestData(allModels, allMasks, allTests);

    
    // Best parameters SIFT
    int mode = 2;
    int minKeypoints = 10;       // up to 10 to balance score and flase positives
    double sigma = 0.8;
    double cutOffRatio = 0.80;   // 0.80 to balance score and flase positives (best score at 0.83)
    int boxHeight = 225;
    int boxWidth = 150;

    bool logImages = true;
    std::string savePath = "../results";
    runDetectionAllImages(allModels, allMasks, allTests, mode, minKeypoints, sigma, cutOffRatio, boxHeight, boxWidth, logImages, savePath, 0);
    performanceMetrics(savePath);
    
    
    /*
    // Fixed size centerd box, fixed keypoints to 10. Only vary sigma and ratio
    int mode = 2;
    int boxWidth = 150;
    int boxHeight = 225;
    std::string savePath = "../results";
    int startKeypoints = 10, stopKeypoints = 10;

    double startSigma = 0.5, stopSigma = 1.5;
    double startRatio = 0.70, stopRatio = 0.85;

    std::cout << "SURF:";
    evaluateBestParameters(mode, savePath, startKeypoints, stopKeypoints, startSigma, stopSigma, 
                           startRatio, stopRatio, boxHeight, boxHeight, boxWidth, 1);
    std::cout << "\n\nORB:";
    evaluateBestParameters(mode, savePath, startKeypoints, stopKeypoints, startSigma, stopSigma, 
                           startRatio, stopRatio, boxHeight, boxHeight, boxWidth, 2);
    std::cout << "\n\nAKAZE:";
    evaluateBestParameters(mode, savePath, startKeypoints, stopKeypoints, startSigma, stopSigma, 
                           startRatio, stopRatio, boxHeight, boxHeight, boxWidth, 3);
    */

    return 0;
}