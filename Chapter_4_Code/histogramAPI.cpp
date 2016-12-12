#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat computeHistogram(Mat input_image) {
    
    Mat histogram;
    int channels[] = { 0 };
    int histSize[] = { 256 };
    float range[] = { 0, 256 };
    const float* ranges[] = { range };
    
    calcHist(&input_image, 1, channels, Mat(), histogram, 1, histSize, ranges);

    return histogram;

}

int main()
{
    Mat input_image = imread("images/lena.jpg", IMREAD_GRAYSCALE);
    Mat histogram = computeHistogram(input_image);
    
    cout << "Histogram...\n";
    for (int i = 0; i < histogram.rows; ++i)
        cout << i << " : " << histogram.at<float>(i, 0) << "\n";

    return 0;
}
