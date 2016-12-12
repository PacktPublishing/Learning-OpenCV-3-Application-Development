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

Scalar getPlotColor(int chIdx) {
    switch (chIdx) {
        case 0:
            return Scalar(255, 0, 0);
            break;

        case 1:
            return Scalar(0, 255, 0);
            break;

        case 2:
            return Scalar(0, 0, 255);
            break;
    }
    return Scalar(255, 255, 255);
}

void plotHistogram(Mat histogram, Mat histogramPlot, int chIdx) {
    int plotWidth = histogramPlot.cols;
    int plotHeight = histogramPlot.rows;
    int binWidth = (plotWidth / histogram.rows);
    
    normalize(histogram, histogram, 0, plotHeight, NORM_MINMAX);

    for (int i = 1; i < histogram.rows; ++i) {
        
        Scalar plotColor = getPlotColor(chIdx);
        line (
                histogramPlot,
                Point((binWidth*(i-1)), (plotHeight - cvRound(histogram.at<float>(i-1, 0)))),
                Point(binWidth*i, (plotHeight - cvRound(histogram.at<float>(i, 0)))),
                plotColor, 2, CV_AA, 0
        );

    }
    
}

int main() {

    Mat input_image = imread("images/lena.jpg");
    vector<Mat> channels;
    split(input_image, channels);

    int plotWidth = 1024, plotHeight = 400;
    Mat histogramPlot(plotHeight, plotWidth, CV_8UC3, Scalar(0, 0, 0));
    for (int chIdx = 0; chIdx < channels.size(); ++chIdx) {
        Mat channel = channels[chIdx];
        Mat histogram = computeHistogram(channel);
        plotHistogram(histogram, histogramPlot, chIdx);
    }
    
    imshow("Histogram", histogramPlot);
    waitKey(0);

    
    return 0;
}
