# CV25 Intermediate Project – Object Detection

## Table of Contents
- [CODE DESIGN AND STYLE GUIDE](#code-design-and-style-guide)
- [OBJECTIVE](#objective)
  - [Inputs](#inputs)
  - [Outputs](#outputs)
  - [Suggested Approach](#suggested-approach)
  - [Dataset](#dataset)
  - [Evaluation Metrics](#evaluation-metrics)
  - [Project Requirements](#project-requirements)
  - [Submission Checklist](#submission-checklist)
- [SOLUTION PIPELINE](#solution-pipeline)

## **CODE DESIGN AND STYLE GUIDE**
*All contributors swear to follow these points with the utmost care:* 
- No usage of GLOBAL VARIABLES!
- Final project musn't have binary files included
- Usage of a single CMakeLists.txt with more *add_executable* commands
- Compile the code, and make sure it runs bug free before pushing
- Include guards to be added in Header file
- A header file musn't contain function definitions, only declerations!
- Never `#include` a .cpp file
- Never add absolute paths in code
- Always check command-line arguments, before processing them, use `std::cerr` for debugging purposes
- Define GUI names as `const` variables
- Don't mix more than one activity in a single function, for example `maxfilter` should only apply the filter, not visualize it as well
- Pass by reference or pointer to be used in functions, for example `const cv::Mat& src`
- For the sake of clarity:
  - No usage of namespaces
  - Only camelCase to be used, fyi [case guide](https://medium.com/nerd-for-tech/programming-case-types-explained-143cad3681e3)
  - When it comes to comments, follow only the [the google c++ style guide](https://google.github.io/styleguide/cppguide.html#Comment_Style) 

##  **OBJECTIVE**
Develop an **object detection system** using **C++ with OpenCV** to identify and localize three known objects:
- Power Drill
- Mustard Bottle
- Sugar Box

The system should detect each object in a scene image and draw a bounding box around it.

---

### Inputs
- RGB scene image
- Synthetic views of each object
- Binary segmentation masks (optional)

---

###  Outputs
- Text file containing bounding box coordinates
- Scene image with bounding boxes overlaid

---

###  Suggested Approach
Use **robust feature matching** as the base method. Other allowed methods:
- Template matching
- Appearance-based detection
- Bag of Words (BoW)

>  **Deep learning methods are not allowed.**

---

### Dataset
[Dataset Download](https://drive.google.com/drive/folders/1heXAbX4WKXf3-z2sl68Qg-cvbcVwosxO?usp=sharing)

Each object has:
- `models/` — 60 synthetic views + segmentation masks
- `test_images/` — Images with scenes for detection
- `labels/` — Ground truth in the format:  <object_id>_<object_name> <xmin> <ymin> <xmax> <ymax>

---

### Evaluation Metrics
- **Mean Intersection over Union (mIoU):**
Average IoU across all object categories
- **Detection Accuracy:**
Number of correct detections (IoU > 0.5 with ground truth)

---

### Project Requirements
- Implemented in **C++ with OpenCV**
- Must compile and run in the official **Virtual Lab**
- Only original code written by group members is allowed

---

### Submission Checklist
- Source code (C++), one author per file
- Report (max 2 pages of text, excluding images/tables), including:
- Approach explanation
- Performance results (metrics + images)
- Team member contributions
- Hours worked per person

---

## **SOLUTION PIPELINE**

1. **Feature Detection on Models/Training Data** (using SIFT, SURF ...)
   - ⇒ List of Feature Vectors

2. **Feature Detection on the whole image** (using the same technique)

3. **For all features in the image**
   - Find the best match in the training data, i.e., the nearest neighbor in feature space
   - Qualify the match by normalized distance:  
     $$d_{i,\text{norm}} = \frac{d_i}{\max(d_i)}$$
   - Perfect match:  
     $$d_{i,\text{norm}} = 0$$  
     Worst match:  
     $$d_{i,\text{norm}} = 1$$
   - Note: This only grades the matches relative to each other. If all matches are "good" in absolute terms, one will still be the worst.

4. **Find the best rectangle**
   - **Sliding window approach**:
     - Slide the window, take all matches within that window and calculate:
       $$\text{Confidence} = \sum (1 - d_{i,\text{norm}})$$
     - Choose the window with the highest confidence score as the "winner" → Box to determine object position
     - Threshold the confidence value (e.g., Confidence > 500 to determine if the object is actually present  
       ⇒ **Values to decide**: Threshold on confidence for deciding if the winner is the object





