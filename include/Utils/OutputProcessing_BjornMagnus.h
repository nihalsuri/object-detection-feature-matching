#ifndef OutputProcessing_BjornMagnus_H
#define OutputProcessing_BjornMagnus_H

#include <opencv2/core.hpp>       
#include <opencv2/imgproc.hpp>     
#include <opencv2/highgui.hpp>     
#include <opencv2/features2d.hpp>  

#include <string>
#include <vector>
#include <filesystem>

// Open the image with given size and name 
// Inputs:
// img      -Image to be open
// Resize   -Resize the image given the ratio
// name     -Name of the window to be open  
void openImage(cv::Mat &img,float Resize, std::string name);


//Save image given origianl path, path where it will be saved and name 
// Inputs:
// img          -Image to be saved
// imagePath    -Path to original iamge
// savePath     -Path to be saved in 
// addedname    -String that get added to the original name when saved 
void saveImage(cv::Mat &img, std::string imagePath,std::string savePath,std::string addedname);




#endif