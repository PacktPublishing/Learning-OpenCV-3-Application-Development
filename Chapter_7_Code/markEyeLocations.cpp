#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Point getCoordinates(const string& str) {
    stringstream ss(str);
    string item;
    vector<int> coordinates;
    while(getline(ss, item, ' '))
        coordinates.push_back( atoi(item.c_str()) );

    Point coordinatePt(coordinates[0], coordinates[1]);
    return coordinatePt;
}

vector<string> imagePaths;
vector<Point> leftEyeCoordinates;
vector<Point> rightEyeCoordinates;

void readInput(char* filePath) {
    
    ifstream fin;
    fin.open(filePath);
    
    string line;
    int counter = 0;
    
    while(getline(fin, line)) {
        
        counter = (counter + 1) % 3;
        if (counter == 1)
            imagePaths.push_back(line);
        else if (counter == 2) {
            Point leftEyeLoc = getCoordinates(line);
            leftEyeCoordinates.push_back(leftEyeLoc);
        }
        else {
            Point rightEyeLoc = getCoordinates(line);
            rightEyeCoordinates.push_back(rightEyeLoc);
        }
    }

    fin.close();
}

void showMarkedFaces() {
    
    for (int i = 0; i < imagePaths.size(); ++i) {
        string imagePath = imagePaths[i];
        Mat image = imread(imagePath);

        Point leftEye = leftEyeCoordinates[i];
        Point rightEye = rightEyeCoordinates[i];

        circle(image, leftEye, 5, Scalar(255, 0, 0), -1);
        circle(image, rightEye, 5, Scalar(255, 0, 0), -1);

        imshow("Eyes", image);
        waitKey(0);
    }

}

int main()
{
    readInput("eyeLocations.txt");

    CV_Assert(imagePaths.size() == leftEyeCoordinates.size());
    CV_Assert(leftEyeCoordinates.size() == rightEyeCoordinates.size());

    showMarkedFaces();

    return 0;
}
