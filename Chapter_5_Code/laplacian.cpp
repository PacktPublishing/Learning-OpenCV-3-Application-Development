#include <iostream>
#include <cstdlib>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat input_image = imread("images/lena.jpg", IMREAD_GRAYSCALE);
    Mat output, scaled_output;

    Laplacian(input_image, output, CV_16S, 3);
    convertScaleAbs(output, scaled_output);

    imshow("Laplacian", scaled_output);
    waitKey(0);
    return 0;
}
