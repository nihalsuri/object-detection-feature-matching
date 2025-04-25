#ifndef OBJECTDETECTORALL_MAXPRIES_H
#define OBJECTDETECTORALL_MAXPRIES_H

#include <string>
#include <vector>

// Tries to detect all provided objects in every provided image. Detected
// objects are encapsuled in a rectangular box. The positions and sizes of the
// resulting boxes are logged to a text file.
// Input:
// allModels   - a list containing lists with paths to all object model images
// allMasks    - a list containing lists with paths to all object model masks.
// allTests    - a list with paths to all test images.
// mode        - choice variable for different methods of placing the box
// sigma       - variance for gaussian blur to be applied to the test  images 
//               before feature detection
// cutOffRatio - the cut off ratio for the ratio test by D. Lowe
// logImages   - optional, if true, the detected keypoints that passed the
//               ratio test and the found boxes are drawn on the test images
//               and they are saved in the filesystem

void runDetectionAllImages(const std::vector<std::vector<std::string>> &allModels, 
    const std::vector<std::vector<std::string>> &allMasks, 
    const std::vector<std::string> &allTests, 
    int mode, int minKeypoints, double sigma, double cutOffRatio, bool logImages=false);

#endif