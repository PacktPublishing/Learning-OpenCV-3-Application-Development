#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

Mat getNegativeLUT() {
    vector<uchar> lut_array(256, 0);
    for (int i = 0; i < 256; ++i)
            lut_array[i] = (uchar)(255 - i);

    Mat LUT(1, 256, CV_8U);
    for (int j = 0; j < 256; ++j)
            LUT.at<uchar>(0, j) = lut_array[j];
    return LUT;
}

int main() {
    Mat input_image = imread("images/lena.jpg", IMREAD_GRAYSCALE);
    Mat output_image;
    Mat lookup_table = getNegativeLUT();

    LUT(input_image, lookup_table, output_image);

    imshow("Input Image", input_image);
    imshow("Output Image", output_image);
    waitKey(0);

    return 0;
}


