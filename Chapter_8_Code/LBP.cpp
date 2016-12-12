#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;


void LBP(const Mat& src, Mat& dst) {
	
    dst = Mat::zeros(src.rows-2, src.cols-2, CV_8UC1);
	for(int i = 1; i < (src.rows - 1); i++) {
		for(int j = 1; j < (src.cols-1); j++) {
			uchar center = src.at<uchar>(i,j);
			unsigned char code = 0;
			code |= (src.at<uchar>(i-1,j-1) > center) << 7;
			code |= (src.at<uchar>(i-1,j) > center) << 6;
			code |= (src.at<uchar>(i-1,j+1) > center) << 5;
			code |= (src.at<uchar>(i,j+1) > center) << 4;
			code |= (src.at<uchar>(i+1,j+1) > center) << 3;
			code |= (src.at<uchar>(i+1,j) > center) << 2;
			code |= (src.at<uchar>(i+1,j-1) > center) << 1;
			code |= (src.at<uchar>(i,j-1) > center) << 0;
			dst.at<unsigned char>(i-1,j-1) = code;
		}
	}
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        cout << "Please provide image path as command-line parameter.\n"
            << "Sample usage : ./LBP images/lena.jpg\n";
        return -1;
    }

    Mat input = imread(argv[1], IMREAD_GRAYSCALE);
    Mat lbp_image;
    LBP(input, lbp_image);

    imshow("lbp", lbp_image);
    waitKey(0);

    return 0;
}
