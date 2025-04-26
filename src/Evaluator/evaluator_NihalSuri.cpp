#include "Evaluator/evaluator_NihalSuri.h"
#include "Utils/inputProcessing_MaxPries.h"


std::pair<std::string, BoundingBox> parseLine(const std::string& line) {
    std::istringstream iss(line);
    std::string object_id, x_str, y_str, w_str, h_str;
    
    // Parse based on your ground truth format
    // Note: Adjust this based on your actual ground truth format
    iss >> object_id >> x_str >> y_str >> w_str >> h_str;
    
    // Convert to xmin, ymin, xmax, ymax format if needed
    int xmin = std::stoi(x_str);
    int ymin = std::stoi(y_str);
    int xmax = xmin + std::stoi(w_str);
    int ymax = ymin + std::stoi(h_str);
    
    return {object_id, BoundingBox(xmin, ymin, xmax, ymax)};
}


float calculateIoU(const BoundingBox& box1, const BoundingBox& box2) {
    // Calculate coordinates of intersection
    int xmin_intersect = std::max(box1.xmin, box2.xmin);
    int ymin_intersect = std::max(box1.ymin, box2.ymin);
    int xmax_intersect = std::min(box1.xmax, box2.xmax);
    int ymax_intersect = std::min(box1.ymax, box2.ymax);
    
    // Check if there is an intersection
    if (xmax_intersect <= xmin_intersect || ymax_intersect <= ymin_intersect) {
        return 0.0f; // No intersection
    }
    
    // Calculate area of intersection
    int intersection_area = (xmax_intersect - xmin_intersect) * (ymax_intersect - ymin_intersect);
    
    // Calculate area of union
    int union_area = box1.area() + box2.area() - intersection_area;
    
    // Calculate IoU
    return static_cast<float>(intersection_area) / union_area;
}


void performanceMetrics(const std::string& resultsPath){
    // Provide mIoU for each object category 
    // Provide avergae mIoU
    
    // Collect all annotation file-paths
    std::vector<std::string> groundTruthPaths; 
    // Sugar box
    std::vector<std::string> pathListSugarLabels = fetchFilepaths("../data/004_sugar_box/labels", "box.txt");
    // Mustard bottle
    std::vector<std::string> pathListMustardLabels = fetchFilepaths("../data/006_mustard_bottle/labels", "box.txt");
    // Power drill
    std::vector<std::string> pathListPowerDrillLabels = fetchFilepaths("../data/035_power_drill/labels", "box.txt");
    // Concatenate all ground truth labels 
    groundTruthPaths.reserve(pathListSugarLabels.size() + pathListMustardLabels.size() + pathListPowerDrillLabels.size());
    groundTruthPaths.insert(groundTruthPaths.end(), pathListSugarLabels.begin(), pathListSugarLabels.end());
    groundTruthPaths.insert(groundTruthPaths.end(), pathListMustardLabels.begin(), pathListMustardLabels.end());
    groundTruthPaths.insert(groundTruthPaths.end(), pathListPowerDrillLabels.begin(), pathListPowerDrillLabels.end());


    // Complete results 
    std::vector<std::string> resultPaths = fetchFilepaths(resultsPath + "/coordinates", "color_output.txt");
    std::vector<std::string> temp(resultPaths.begin(), resultPaths.begin() + 10);
    resultPaths.insert(resultPaths.end(), temp.begin(), temp.end());
    resultPaths.erase(resultPaths.begin(), resultPaths.begin() + 10); 

    // // for debugging 
    // std::cout << "GT" << std::endl;
    // // Output the concatenated result
    // for (const auto& word : groundTruthPaths) {
    //     std::cout << word << std::endl;
    // }
    // std::cout << "Result" << std::endl;
    // for (const auto& word : resultPaths) {
    //     std::cout << word << std::endl;
    // }

    // Maps to store IoU sums and counts for each object category
    std::map<std::string, float> iouSums = {
        {"004_sugar_box", 0.0f},
        {"006_mustard_bottle", 0.0f},
        {"035_power_drill", 0.0f}
    };
    
    std::map<std::string, int> iouCounts = {
        {"004_sugar_box", 0},
        {"006_mustard_bottle", 0},
        {"035_power_drill", 0}
    };

    // Maps for detection accuracy calculation
    std::map<std::string, int> truePositives = {
        {"004_sugar_box", 0},
        {"006_mustard_bottle", 0},
        {"035_power_drill", 0}
    };
    
    std::map<std::string, int> totalInstances = {
        {"004_sugar_box", 0},
        {"006_mustard_bottle", 0},
        {"035_power_drill", 0}
    }; 

    // Process each pair of files
    for (size_t i = 0; i < groundTruthPaths.size(); ++i) {
        std::string gtPath = groundTruthPaths[i];
        std::string resultPath = resultPaths[i];
        
        // Read ground truth file
        std::ifstream gtFile(gtPath);
        if (!gtFile.is_open()) {
            std::cerr << "Could not open ground truth file: " << gtPath << std::endl;
            continue;
        }
        
        // Parse ground truth bounding boxes
        std::map<std::string, BoundingBox> gtBoxes;
        std::string line;
        while (std::getline(gtFile, line)) {
            if (!line.empty()) {
                auto [objectId, box] = parseLine(line);
                gtBoxes[objectId] = box;
            }
        }
        gtFile.close();
        
        // Read result file
        std::ifstream resultFile(resultPath);
        if (!resultFile.is_open()) {
            std::cerr << "Could not open result file: " << resultPath << std::endl;
            continue;
        }
        
        // Parse result bounding boxes
        std::map<std::string, BoundingBox> resultBoxes;
        while (std::getline(resultFile, line)) {
            if (!line.empty()) {
                auto [objectName, box] = parseLine(line);
                resultBoxes[objectName] = box;
            }
        }
        resultFile.close();
        
        // Calculate IoU for each object category present in both files
        for (const auto& [objectType, _] : iouSums) {
            // Check if object exists in ground truth 
            if(gtBoxes.count(objectType) > 0){
                totalInstances[objectType]++;

                // Check if the object is recognized in results 
                if(resultBoxes.count(objectType) > 0){
                    float iou = calculateIoU(gtBoxes[objectType], resultBoxes[objectType]); 
                    // Update sums and counts
                    iouSums[objectType] += iou; 
                    iouCounts[objectType]++;

                    // Check if detection is accurate (according to task)
                    if(iou > 0.5f){
                        truePositives[objectType]++;
                    }
                }
            }
        }
    }

    // Calculate mean IoU for each object category
    float totalMeanIoU = 0.0f;
    int validCategories = 0;
    
    std::cout << "\nMean IoU per category:" << std::endl;
    for (const auto& [objectType, sum] : iouSums) {
        if (iouCounts[objectType] > 0) {
            float meanIoU = sum / iouCounts[objectType];
            std::cout << objectType << ": " << meanIoU << std::endl;
            totalMeanIoU += meanIoU;
            validCategories++;
        } else {
            std::cout << objectType << ": No valid detections" << std::endl;
        }
    }
    
    // Calculate overall mean IoU across all categories
    if (validCategories > 0) {
        std::cout << "\nOverall Mean IoU: " << totalMeanIoU / validCategories << std::endl;
    } else {
        std::cout << "\nNo valid detections found in any category." << std::endl;
    }

    // Calculate and display detection accuracy for each object category
    std::cout << "\nDetection Accuracy (IoU > 0.5) per category:" << std::endl;
    int totalTP = 0;
    int totalInstancesAll = 0;
    
    for (const auto& [objectType, tp] : truePositives) {
        int instances = totalInstances[objectType];
        totalTP += tp;
        totalInstancesAll += instances;
        
        if (instances > 0) {
            float accuracy = static_cast<float>(tp) / instances;
            std::cout << objectType << ": " << accuracy << " (" << tp << "/" << instances << ")" << std::endl;
        } else {
            std::cout << objectType << ": No instances found" << std::endl;
        }
    }
    
    // Calculate overall detection accuracy
    if (totalInstancesAll > 0) {
        float overallAccuracy = static_cast<float>(totalTP) / totalInstancesAll;
        std::cout << "\nOverall Detection Accuracy: " << overallAccuracy 
                  << " (" << totalTP << "/" << totalInstancesAll << ")" << std::endl;
    } else {
        std::cout << "\nNo instances found across all categories." << std::endl;
    }


    
}