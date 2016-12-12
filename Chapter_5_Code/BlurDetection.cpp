#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

float getMean(Mat input) {
    int num_elements = (input.rows * input.cols);
    float sum = 0.0;
    for (int i = 0; i < input.rows; ++i) {
        for (int j = 0; j < input.cols; ++j)
            sum += input.at<float>(i, j);
    }

    return (sum / num_elements);
}

float getVariance(Mat input) {
    float mean = getMean(input);
    float sum_of_biases = 0.0;
    int num_of_elements = (input.rows * input.cols);

    for (int i = 0; i < input.rows; ++i) {
        for (int j = 0; j < input.cols; ++j) {
            float element_value = input.at<float>(i, j);
            sum_of_biases += ((element_value - mean) * (element_value - mean));
        }
    }

    return (sum_of_biases / num_of_elements);

}

int main() {
    
    Mat input_image_1 = imread("images/blurry1.jpg", IMREAD_GRAYSCALE);
    Mat input_image_2 = imread("images/blurry2.jpg", IMREAD_GRAYSCALE);
    Mat laplacian_output_1, laplacian_output_2;

    Laplacian(input_image_1, laplacian_output_1, CV_32F);
    Laplacian(input_image_2, laplacian_output_2, CV_32F);
    
    float std_dev_1 = getVariance(laplacian_output_1);
    float std_dev_2 = getVariance(laplacian_output_2);
    
    cout << "Bluriness for Image 1 = " << std_dev_1 << "\n";
    cout << "Bluriness for Image 2 = " << std_dev_2 << "\n";

    return 0;
}
