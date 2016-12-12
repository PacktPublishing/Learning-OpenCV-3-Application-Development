#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat input_image = imread("images/lena.jpg");
    cvtColor(input_image, input_image, CV_BGR2GRAY);

    Mat gaussian_noise = input_image.clone();
    randn(gaussian_noise, 0, 50);
    input_image += gaussian_noise;

    Mat edges;
    Canny(input_image, edges, 100, 300, 3, false);

    imshow("Noisy_Input", input_image);
    imshow("Noisy_Edge_Detection", edges);
    waitKey(0);
    return 0;
}

