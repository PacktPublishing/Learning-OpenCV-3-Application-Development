#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>

using namespace std;
using namespace cv;

int main()
{
    Ptr<ml::KNearest> knn(ml::KNearest::create());
    Mat_<float> trainingData(10, 2);
    trainingData <<  0, 0,
                     0.5, 0,
                     0.5, 0.25,
                     1, 1.25,
                     1, 1.5,
                     1, 1,
                     0.5, 1.5,
                     0.25, 1,
                     2, 1.5,
                     2, 2.5;

    Mat_<int> trainingLabels(1, 10);
    trainingLabels << 0, 0, 0, 1, 1, 1, 0, 1, 1, 1;

    knn->train(trainingData, ml::ROW_SAMPLE, trainingLabels);

    Mat_<float> testFeatures(1, 2);
    testFeatures << 2.5, 2.5;

    int K = 4;
    Mat response, dist;
    knn->findNearest(testFeatures, K, noArray(), response, dist);
    cout << response << "\n";
    cout << dist  << "\n";

    return 0;
}
