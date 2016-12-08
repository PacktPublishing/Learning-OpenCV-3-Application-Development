#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat color_image = imread("images/lena.jpg", IMREAD_UNCHANGED);
    vector<Mat> channels;
    split(color_image, channels);

    imshow("Blue", channels[0]);
    imshow("Green", channels[1]);
    imshow("Red", channels[2]);
    waitKey(0);

    return 0;
}
