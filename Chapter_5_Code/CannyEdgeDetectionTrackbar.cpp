#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

Mat input_image, edges;
char* window_name = "Edge-Detection";
int lowThreshold;

void CannyThreshold(int, void*) {
    Canny(input_image, edges, lowThreshold, (lowThreshold * 3), 3);
    imshow(window_name, edges);
}

int main()
{
    input_image = imread("images/cannyInput.jpg");
    cvtColor(input_image, input_image, CV_BGR2GRAY);

    edges.create(input_image.size(), input_image.type());

    namedWindow(window_name, CV_WINDOW_NORMAL);
    createTrackbar("Min-Threshold:", window_name, &lowThreshold, 100, CannyThreshold);
    CannyThreshold(0, 0);

    waitKey(0);
    return 0;
}
