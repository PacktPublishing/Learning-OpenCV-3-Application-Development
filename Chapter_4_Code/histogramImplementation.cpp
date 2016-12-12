#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat computeHistogram(Mat input_image) {
    Mat histogram = Mat::zeros(256, 1, CV_32S);

    for (int i = 0; i < input_image.rows; ++i) {
        for (int j = 0; j < input_image.cols; ++j) {
            
            int binIdx = (int) input_image.at<uchar>(i, j);
            histogram.at<int>(binIdx, 0) += 1;
        
        }
    }

    return histogram;
}


int main()
{
    Mat input_image = imread("images/lena.jpg", IMREAD_GRAYSCALE);
    int totalPixelCount = (input_image.rows * input_image.cols);

    Mat histogram = computeHistogram(input_image);

    cout << "Histogram...\n";
    int sum = 0;
    for (int i = 0; i < histogram.rows; ++i) {
        sum += histogram.at<int>(i, 0);
        cout << i << " : " << histogram.at<int>(i, 0) << "\n";
    }
    cout << "Sum of all frequency counts = " << sum << "\n";
    cout << "rows * cols = " << totalPixelCount << "\n";


    return 0;
}
