/*
 * The getStructuringElement() function is used to create masks. It supports 3 types of masks - 
 * 	(1) MORPH_RECT
 * 	(2) MORPH_CROSS
 * 	(3) MORPT_ELLIPSE
 */

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

void printStructuringElement(const Mat& element) {

    for (int i = 0; i < element.rows; ++i) {
	
	const uchar* rowPtr = element.ptr<uchar>(i);
	for (int j = 0; j < element.cols; ++j)
	    cout << (int) rowPtr[j] << " ";
	cout << "\n";
    
    }
}

int main() {

    Mat element = getStructuringElement(MORPH_ELLIPSE, Size(50, 50));
    printStructuringElement(element);

    return 0;
}
