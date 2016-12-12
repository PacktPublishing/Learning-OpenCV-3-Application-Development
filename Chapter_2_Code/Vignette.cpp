#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat input_image = imread("images/lena.jpg", IMREAD_GRAYSCALE);
    
    Mat kernel_X = getGaussianKernel(input_image.cols, 50);
    Mat kernel_Y = getGaussianKernel(input_image.rows, 50);
    Mat kernel_X_transpose;
    transpose(kernel_X, kernel_X_transpose);
    Mat kernel = kernel_Y * kernel_X_transpose;
    
    Mat mask, processed_image;
    normalize(kernel, mask, 0, 1, NORM_MINMAX);
    input_image.convertTo(processed_image, CV_64F);
    multiply(mask, processed_image, processed_image);
    convertScaleAbs(processed_image, processed_image);

    imshow("Vignette", processed_image);
    waitKey(0);

    return 0;
}
