#include "Utils/OutputProcessing_BjornMagnus.h"

void openImage(cv::Mat &img,float Resize = 1, std::string name = "Window"){
    cv::resize(img, img, cv::Size(), Resize, Resize);  //Resize the image to given format 
    cv::namedWindow(name, cv::WINDOW_AUTOSIZE);        //Gives the name to the window being opened 
    cv::imshow(name, img);                             //Open the given image with given name 
    cv::waitKey(0);                                    //allows window to render the image and wait for a key to be pressed
}

void saveImage(cv::Mat &img, std::string imagePath,std::string savePath, std::string addedname="_output.jpg"){
    std::filesystem::path origPathFs(imagePath);
    //Get the name of the original image from its path 
    std::string filename = origPathFs.stem().string();   
    //Set the path and name for the file to be saved      
    std::string newFilename = savePath + filename + addedname;
    //Save image with given path and name
    cv::imwrite(newFilename, img); 
}