#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat input_image = imread("images/lena.jpg", IMREAD_GRAYSCALE);
    Mat sobel_filtered_horizontal, sobel_filtered_vertical;
    Mat horizontal_der_scaled, vertical_der_scaled;

    Scharr(input_image, sobel_filtered_horizontal, -1, 1, 0);
    Scharr(input_image, sobel_filtered_vertical, -1, 0, 1);

    imshow("Horizontal_Derivative", sobel_filtered_horizontal);
    imshow("Vertical_Derivative", sobel_filtered_vertical);
    waitKey(0);

    return 0;
}
