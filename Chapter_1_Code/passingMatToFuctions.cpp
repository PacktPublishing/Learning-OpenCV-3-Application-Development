#include <iostream> 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void processImage(Mat input_image) {
    int channels = input_image.channels();
    int numRows = input_image.rows;
    int numCols = input_image.cols * channels;

    for (int i = 0; i < numRows; ++i) {
        uchar* image_row = input_image.ptr<uchar>(i);
        for (int j = 0; j < numCols; ++j)
            image_row[j] = 0;
        }
}

int main() {
    Mat image = imread("images/lena.jpg");
    Mat image_clone = image.clone();
    processImage(image);
                
    imshow("image", image);
    imshow("image_clone", image_clone);
    waitKey(0);

    return 0;
}


