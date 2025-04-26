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
    

    int mode = 0;
    int minKeypoints = 7;
    double sigma = 1;
    double cutOffRatio = 0.78;
    bool logImages = true;
    std::string savePath = "../results";
    runDetectionAllImages(allModels, allMasks, allTests, mode, minKeypoints, sigma, cutOffRatio, logImages, savePath);

    /*
    int bestMode = 0;
    int bestMinKeypoints = 9;
    double bestSigma = 1;
    double bestCutOffRatio = 0.73;
    double bestScore = 0;

    //NOTE: THIS WILL RUN THE WHOLE THING 216 TIMES!!
    for (int mode=bestMode; mode<=2; mode++)
    {
        for (int minKeypoints=bestMinKeypoints; minKeypoints<=15; minKeypoints+=2)
        {
            for (double sigma=vestSigma; sigma<=2; sigma+=0.5)
            {
                for (double cutOffRatio=bestCutOffRatio; cutOffRatio<=0.78; cutOffRatio+=0.01)
                {
                    runDetectionAllImages(allModels, allMasks, allTests, mode, minKeypoints, sigma, cutOffRatio, false);
                    currentScore = computeScoreMetric

                    if (currentScore > bestScore)
                    {
                        bestScore = currentScore;
                        bestMode = mode;
                        bestMinKeypoints = minKeypoints;
                        bestSigma = sigma;
                        bestCutOffRatio = cutOffRatio;
                    }
                }
                std::cout << "Current Best Score:     " << bestScore <<std::endl;
                std::cout << "Current Best Mode:      " << bestMode <<std::endl;
                std::cout << "Current Best Keypoints: " << bestMode <<std::endl;
                std::cout << "Current Best Sigma:     " << bestMode <<std::endl;
                std::cout << "Current Best Ratio:     " << bestMode <<std::endl;
            }
        }
    }
    */
    performanceMetrics("../results");

    return 0;
}