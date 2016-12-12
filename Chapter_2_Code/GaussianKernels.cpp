#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {

    Mat gaussian_kernel = getGaussianKernel(7, 1.0, CV_64F);

    int cols = (gaussian_kernel.isContinuous()) ? (gaussian_kernel.rows * gaussian_kernel.cols) : gaussian_kernel.cols;
    int rows = (gaussian_kernel.isContinuous()) ? 1 : gaussian_kernel.rows;

    cout << "Gaussian Kernel...\n";
    for (int row_idx = 0; row_idx < rows; ++row_idx) {
        double* row_ptr = gaussian_kernel.ptr<double>(row_idx);
        for (int col_idx = 0; col_idx < cols; ++col_idx)
            cout << row_ptr[col_idx] << " ";
        cout << "\n";
    }
    
    return 0;
}
