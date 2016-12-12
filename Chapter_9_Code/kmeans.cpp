#include <iostream>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat_<float> data(10, 2);
    data <<  0, 0,
                     0.5, 0,
                     0.5, 0.25,
                     1, 1.25,
                     1, 1.5,
                     1, 1,
                     0.5, 1.5,
                     0.25, 1,
                     2, 1.5,
                     2, 2.5;

    int K = 2;
    Mat labels, centers;
    TermCriteria criteria(TermCriteria::EPS+TermCriteria::MAX_ITER, 10, 0.0001);

    kmeans(data, K, labels, criteria, 1, KMEANS_RANDOM_CENTERS, centers);
    cout << labels << "\n";
    cout << centers << "\n";
    
    return 0;
}
