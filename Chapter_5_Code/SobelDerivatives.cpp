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

    Sobel(input_image, sobel_filtered_horizontal, CV_16S, 1, 0);
    Sobel(input_image, sobel_filtered_vertical, CV_16S, 0, 1);

    convertScaleAbs(sobel_filtered_horizontal, horizontal_der_scaled);
    convertScaleAbs(sobel_filtered_vertical, vertical_der_scaled);

    imshow("Horizontal_Derivative", horizontal_der_scaled);
    imshow("Vertical_Derivative", vertical_der_scaled);
    // imshow("Horizontal_Derivative", sobel_filtered_horizontal);
    // imshow("Vertical_Derivative", sobel_filtered_vertical);
    waitKey(0);

    return 0;
}
