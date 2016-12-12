#include <iostream>
#include <cmath>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    Mat input_image = imread("images/lena.jpg");

    if (argc != 3) {
        cout << "PLease provide non-negative integral values for horizontal and vertical offsets\n"
            << "Sample usage : ./basicImageCropping 50 50\n";
        return -1;
    }
    
    int horizontal_offset = atoi(argv[1]);
    int vertical_offset = atoi(argv[2]);

    if (horizontal_offset < 0 || vertical_offset < 0) {
        cout << "The offsets must bbe non-negative integers!\n";
        return -1;
    }

    Rect roi;
    roi.x = horizontal_offset;
    roi.y = vertical_offset;
    roi.width = (input_image.cols - (2 * horizontal_offset));
    roi.height = (input_image.rows - (2 * vertical_offset));
    
    if ( (roi.width <= 0) || (roi.height <= 0) ) {
        cout << "Please provide reasonable-sized cropping parameters!\n";
        return -1;
    }

    Mat cropped_image =input_image(roi);
    imshow("Cropped_Image", cropped_image);
    waitKey(0);

    return 0;
}
