#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat input_image = imread("images/lena.jpg", IMREAD_GRAYSCALE);
    Mat binary_image(input_image.size(), input_image.type());
    
    threshold(input_image, binary_image, 120, 255, THRESH_BINARY);

    imshow("Binary_Image", binary_image);
    waitKey(0);
    return 0;
}
