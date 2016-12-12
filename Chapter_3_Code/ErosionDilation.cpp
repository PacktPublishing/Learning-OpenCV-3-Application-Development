#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {

    Mat input_image = imread("images/dilationInput.png", CV_LOAD_IMAGE_GRAYSCALE);
    Mat dilated_image(input_image.size(), input_image.type());
    Mat eroded_image(input_image.size(), input_image.type());
    
    Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
    // Mat element = Mat::ones(Size(5, 5), CV_8UC1);
    dilate(input_image, dilated_image, element, Point(-1, -1), 1, BORDER_REPLICATE);
    erode(input_image, eroded_image, element, Point(-1, -1), 1, BORDER_REPLICATE);

    imshow("Input_Image", input_image);
    imshow("Eroded_Image", eroded_image);
    imshow("Dilated_Image", dilated_image);
    waitKey(0);

    return 0;
}
