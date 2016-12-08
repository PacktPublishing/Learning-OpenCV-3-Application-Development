#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;


int main() {
    Mat image = imread("images/lena.jpg", IMREAD_COLOR);
    imshow("Output", image);
    waitKey(0); 

    return 0;
}

