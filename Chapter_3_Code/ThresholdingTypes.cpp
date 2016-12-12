#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat input_image = imread("images/lena.jpg", IMREAD_GRAYSCALE);
    Mat binary(input_image.size(), input_image.type());
    Mat binary_inv(input_image.size(), input_image.type());
    Mat to_zero(input_image.size(), input_image.type());
    Mat to_zero_inv(input_image.size(), input_image.type());
    Mat trunc(input_image.size(), input_image.type());
    
    threshold(input_image, binary, 120, 255, THRESH_BINARY);
    threshold(input_image, binary_inv, 120, 255, THRESH_BINARY_INV);
    threshold(input_image, to_zero, 120, 255, THRESH_TOZERO);
    threshold(input_image, to_zero_inv, 120, 255, THRESH_TOZERO_INV);
    threshold(input_image, trunc, 120, 255, THRESH_TRUNC);

    imwrite("/home/samyak/OpenCV/Projects/Chapter_3_Code/images/binary.png", binary);
    imwrite("/home/samyak/OpenCV/Projects/Chapter_3_Code/images/binary_inv.png", binary_inv);
    imwrite("/home/samyak/OpenCV/Projects/Chapter_3_Code/images/to_zero.png", to_zero);
    imwrite("/home/samyak/OpenCV/Projects/Chapter_3_Code/images/to_zero_inv.png", to_zero_inv);
    imwrite("/home/samyak/OpenCV/Projects/Chapter_3_Code/images/trunc.png", trunc);
    
    return 0;
}
