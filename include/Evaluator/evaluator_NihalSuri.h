#ifndef EVALUATOR_NIHALSURI_H
#define EVALUATOR_NIHALSURI_H

#include <opencv2/core.hpp>       
#include <opencv2/imgproc.hpp>     
#include <opencv2/highgui.hpp>     
#include <opencv2/features2d.hpp>  

#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <cmath>


// Structure to store bounding box information
struct BoundingBox {
    int xmin, ymin, xmax, ymax;
    
    BoundingBox() : xmin(0), ymin(0), xmax(0), ymax(0) {}
    BoundingBox(int x1, int y1, int x2, int y2) : xmin(x1), ymin(y1), xmax(x2), ymax(y2) {}
    
    // Calculate area of the bounding box
    int area() const {
        return (xmax - xmin) * (ymax - ymin);
    }
};

// Function to parse a annotation from a file
std::pair<std::string, BoundingBox> parseLine(const std::string& line);

// Function to calculate IoU between two bounding boxes
float calculateIoU(const BoundingBox& box1, const BoundingBox& box2);

// Calculate mean intersection over union and detection accurracy given the path of the text files
// Inputs:
// resultsPath   -Path of the annotation results
void performanceMetrics(const std::string& resultsPath);







#endif