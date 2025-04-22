#include <iostream>
#include <filesystem>

#include "Utils/inputProcessing_MaxPries.h"


void loadInput(cv::Mat &img, const std::string path, bool grayscale)
{
    if (!grayscale) img = cv::imread(path);
    else img = cv::imread(path, cv::IMREAD_GRAYSCALE);

    // Check image and abort if necessary
    if (img.empty())
    {
        std::cerr << "Error: Could not load image!" << std::endl;
        exit(1);
    }
    
}


std::vector<std::string> fetchFilenames(const std::string sourceDir, const std::string ending)
{
    namespace fs = std::filesystem;

    std::vector<std::string> pathList;

    fs::path rootPath = sourceDir;

    // Loops recursively over every entry in the provided directory
    for (auto dirEntry : fs::recursive_directory_iterator(rootPath))
    {
        // Ignore directories etc.
        if (!dirEntry.is_regular_file()) continue;

        std::string imgPath = dirEntry.path().string();

        // Sort out only those entries that are the relevant training data and
        // store their names in a vector
        if (imgPath.size() >= ending.length() && imgPath.ends_with(ending))
        {
            pathList.push_back(imgPath);
        }
    }
    return pathList;
}