#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{

    Mat input_image = imread("images/lena.jpg");
    Mat hsv_image;
    cvtColor(input_image, hsv_image, CV_BGR2HSV);

    int hBins = 30, sBins = 32;
    int histSize[] = { hBins, sBins };

    float hRange[] = { 0, 180 };
    float sRange[] = { 0, 256 };
    const float* ranges[] = { hRange, sRange };

    int channels[] = { 0, 1 };

    Mat histogram;
    calcHist(&hsv_image, 1, channels, Mat(), histogram, 2, histSize, ranges, true, false);

    double maxVal=0;
    minMaxLoc(histogram, 0, &maxVal, 0, 0);

    int scale = 10;
    Mat histImg = Mat::zeros((sBins * scale), (hBins * scale), CV_8UC3);
    for (int h = 0; h < hBins; h++) {
        for (int s = 0; s < sBins; s++) {
            float binVal = histogram.at<float>(h, s);
            int intensity = cvRound(binVal * 255 / maxVal);
            rectangle(
                    histImg,
                    Point(h * scale, s * scale),
                    Point((h+1)*scale - 1, (s+1)*scale - 1),
                    Scalar::all(intensity),
                    CV_FILLED
            );
        }
    }

    imshow( "H-S Histogram", histImg );
    waitKey(0);
    return 0;
}

