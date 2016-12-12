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

void plotHistogram(Mat histogram) {
    int plotWidth = 1024, plotHeight = 400;
    int binWidth = (plotWidth / histogram.rows);
    Mat histogramPlot(plotHeight, plotWidth, CV_8UC3, Scalar(0, 0, 0));

    normalize(histogram, histogram, 0, plotHeight, NORM_MINMAX);

    for (int i = 1; i < histogram.rows; ++i) {

        rectangle (
                histogramPlot,
                Point( (binWidth * (i-1)), (plotHeight - cvRound(histogram.at<float>(i-1, 0))) ),
                Point(binWidth*i, plotHeight),
                CV_RGB(200, 200, 200),
                CV_FILLED
        );
        
    }
    
    imshow("Histogram", histogramPlot);
    waitKey(0);
}

int main() {

    Mat input_image = imread("images/lena.jpg", IMREAD_GRAYSCALE);
    Mat histogram = computeHistogram(input_image);
    plotHistogram(histogram);
    
    return 0;
}
