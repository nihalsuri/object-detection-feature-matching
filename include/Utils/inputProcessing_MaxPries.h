#ifndef INPUTPROCESSING_MAXPRIES_H
#define INPUTPROCESSING_MAXPRIES_H

#include <opencv2/highgui.hpp>
#include <string>
#include <vector>

// Loads an image into a cv::Mat object from a provided path
//
// Inputs:
// img       - the target cv::Mat object
// path      - the path where the image is stored
// grayscale - wheather the image should be loaded as a grayscale image
void loadInput(cv::Mat &img, const std::string path, bool grayscale=false);


// Generates a vector containing all file-paths with a specified ending
// in a given directory and its subsirectories
// Inputs:
// sourceDir - the directory to be searced
// ending    - the specified ending of the filenames (includes extentions)
//
// Output:
// pathList - a vector containing strings of all specified file-paths
std::vector<std::string> fetchFilenames(const std::string sourceDir, const std::string ending);

#endif