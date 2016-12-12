#include <iostream>
#include <cstdio>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

vector<int> convertToBinary(int x) {
    vector<int> result(8, 0);
    
    int idx = 0;
    while(x != 0) {
        result[idx] = x % 2;
        ++idx;
        x /= 2;
    }

    reverse(result.begin(), result.end());
    return result;
}

int countTransitions(vector<int> x) {
    int result = 0;
    for(int i = 0; i < 8; ++i)
        result += (x[i] != x[(i+1) % 8]);
    return result;
}

Mat uniformPatternHistogram(const Mat& src, int numPatterns) {
    Mat hist;
    hist = Mat::zeros(1, (numPatterns+1), CV_32SC1);

    for (int i = 0; i < numPatterns; ++i) {
        if (countTransitions(convertToBinary(i)) > 2)
            hist.at<int>(0, i) = -1;
    }

    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            int bin = src.at<uchar>(i, j);
            if (hist.at<int>(0, bin) == -1)
                hist.at<int>(0, numPatterns) += 1;
            else
                hist.at<int>(0, bin) += 1;
        }
    }
    return hist;
}

void uniformPatternSpatialHistogram(const Mat& src, Mat& hist, int numPatterns,
        int gridX, int gridY, int overlap) {
    
    int width = src.cols;
    int height = src.rows;
    vector<Mat> histograms;

    Size window = Size(static_cast<int>(floor(src.cols/gridX)),
            static_cast<int>(floor(src.rows/gridY)));

    for (int x = 0; x <= (width - window.width); x+= (window.width - overlap)) {
        for (int y = 0; y <= (height - window.height); y+= (window.height - overlap)) {
            Mat cell = Mat(src, Rect(x, y, window.width, window.height));
            histograms.push_back(uniformPatternHistogram(cell, numPatterns));
        }
    }
    
    hist.create(1, histograms.size()*(numPatterns+1), CV_32SC1);
    for (int histIdx = 0; histIdx < histograms.size(); ++histIdx) {
        for (int valIdx = 0; valIdx < (numPatterns+1); ++valIdx) {
            int y = (histIdx * (numPatterns+1)) + valIdx;
            hist.at<int>(0, y) = histograms[histIdx].at<int>(valIdx);
        }
    }
}

vector<int> getFeatureVector(Mat spatial_hist) {
    vector<int> feature_vector;
    for(int j = 0; j < spatial_hist.cols; ++j) {
        if(spatial_hist.at<int>(0, j) != -1)
            feature_vector.push_back(spatial_hist.at<int>(0, j));
    }
    return feature_vector;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        cout << "Please provide the name of the image file as command-line agument.\n"
            << "Sample usage : ./uniformPatternHistogram images/lena.jpg\n";
        return -1;
    }

    Mat input_image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    Mat spatial_histogram;
    uniformPatternSpatialHistogram(input_image, spatial_histogram, 256, 3, 3, 0);

    vector<int> feature_vector = getFeatureVector(spatial_histogram);
    for (int i = 0; i < feature_vector.size(); ++i)
        cout << feature_vector[i] << " ";
    cout << "\n";


    return 0;
}
