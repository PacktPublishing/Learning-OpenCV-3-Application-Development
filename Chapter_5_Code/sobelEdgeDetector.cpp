#include <iostream>
#include <cstdlib>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

Mat getGradientMagnitude(Mat xGrad, Mat yGrad) {
    
    CV_Assert((xGrad.rows == yGrad.rows) && (xGrad.cols == yGrad.cols));

    
    Mat gradient_magnitude(xGrad.rows, xGrad.cols, CV_16S);
    for (int i = 0; i < xGrad.rows; ++i) {
        for (int j = 0; j < xGrad.cols; ++j)
            gradient_magnitude.at<short>(i, j) = abs(xGrad.at<short>(i, j)) + abs(yGrad.at<short>(i, j));
    }
    return gradient_magnitude;
}

Mat thresholdGradientMagnitude(Mat gradient_magnitude, int threshold) {
    
    Mat edges = Mat::zeros(gradient_magnitude.rows, gradient_magnitude.cols, CV_8U);
    for(int i = 0; i < gradient_magnitude.rows; ++i) {
        for (int j = 0; j < gradient_magnitude.cols; ++j) {
            if (gradient_magnitude.at<short>(i, j) >= threshold)
                edges.at<uchar>(i, j) = 255;
        }
    }

    return edges;
}

int main()
{
    Mat input_image = imread("images/lena.jpg", IMREAD_GRAYSCALE);
    Mat x_gradient, y_gradient;

    Sobel(input_image, x_gradient, CV_16S, 1, 0);
    Sobel(input_image, y_gradient, CV_16S, 0, 1);


    Mat gradient_magnitude = getGradientMagnitude(x_gradient, y_gradient);
    Mat edges_output = thresholdGradientMagnitude(gradient_magnitude, 100);

    imshow("Edges", edges_output);
    waitKey(0);
    return 0;
}
