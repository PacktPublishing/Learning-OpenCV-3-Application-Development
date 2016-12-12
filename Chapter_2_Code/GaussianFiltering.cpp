#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat input_image = imread("images/lena.jpg", IMREAD_GRAYSCALE);
    Mat filtered_image_1, filtered_image_2, filtered_image_3, filtered_image_4;

    GaussianBlur(input_image, filtered_image_1, Size(7, 7), 1.0, 1.0, BORDER_REPLICATE);
    GaussianBlur(input_image, filtered_image_2, Size(7, 7), 2.0, 2.0, BORDER_REPLICATE);
    GaussianBlur(input_image, filtered_image_3, Size(7, 7), 3.0, 3.0, BORDER_REPLICATE);
    GaussianBlur(input_image, filtered_image_4, Size(7, 7), 4.0, 4.0, BORDER_REPLICATE);

    imshow("Filtered Image_1", filtered_image_1);
    imshow("Filtered Image_2", filtered_image_2);
    imshow("Filtered Image_3", filtered_image_3);
    imshow("Filtered Image_4", filtered_image_4);
    waitKey(0);
    return 0;
}
