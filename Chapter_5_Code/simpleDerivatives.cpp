#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat getXDerivativeKernel() {
    Mat xDerivativeKernel = Mat::zeros(3, 3, CV_32F);
    
    xDerivativeKernel.at<float>(0, 0) = -1.0;
    xDerivativeKernel.at<float>(1, 0) = -1.0;
    xDerivativeKernel.at<float>(2, 0) = -1.0;

    xDerivativeKernel.at<float>(0, 2) = 1.0;
    xDerivativeKernel.at<float>(1, 2) = 1.0;
    xDerivativeKernel.at<float>(2, 2) = 1.0;

    return (xDerivativeKernel / 3);
}

Mat getYDerivativeKernel() {
    Mat yDerivativeKernel = Mat::zeros(3, 3, CV_32F);
    
    yDerivativeKernel.at<float>(0, 0) = -1.0;
    yDerivativeKernel.at<float>(0, 1) = -1.0;
    yDerivativeKernel.at<float>(0, 2) = -1.0;

    yDerivativeKernel.at<float>(2, 0) = 1.0;
    yDerivativeKernel.at<float>(2, 1) = 1.0;
    yDerivativeKernel.at<float>(2, 2) = 1.0;

    return (yDerivativeKernel / 3);
}

int main()
{
    Mat input_image = imread("images/lena.jpg", IMREAD_GRAYSCALE);
    Mat derivative_X, derivative_Y;
    Mat scaled_derivative_X, scaled_derivative_Y;
    
    Mat xDerivativeKernel = getXDerivativeKernel();
    Mat yDerivativeKernel = getYDerivativeKernel();

    filter2D(input_image, derivative_X, CV_16S, xDerivativeKernel);
    filter2D(input_image, derivative_Y, CV_16S, yDerivativeKernel);

    convertScaleAbs(derivative_X, scaled_derivative_X);
    convertScaleAbs(derivative_Y, scaled_derivative_Y);
    
    imshow("Input-Image", input_image);
    imshow("X-Derivative", scaled_derivative_X);
    imshow("Y-Derivative", scaled_derivative_Y);
    waitKey(0);
    return 0;
}

/*
 *  
    for (int i = 0; i < xDerivativeKernel.rows; ++i) {
        for (int j = 0; j < xDerivativeKernel.cols; ++j)
             cout << xDerivativeKernel.at<float>(i, j) << "\t";
        cout << "\n";
    }
 */

