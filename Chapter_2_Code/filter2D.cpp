#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

const int KERNEL_SIZE = 7;

int main() {
    Mat input_image = imread("images/lena.jpg", IMREAD_GRAYSCALE);
    Mat filtered_image;
    Mat kernel = Mat::ones(KERNEL_SIZE, KERNEL_SIZE, CV_32F) / (float)(KERNEL_SIZE * KERNEL_SIZE);

    filter2D(input_image, filtered_image, -1, kernel, Point(-1, 1), 0, BORDER_REPLICATE);
    
    imshow("Filtered Image", filtered_image);
    waitKey(0);

    return 0;
}
