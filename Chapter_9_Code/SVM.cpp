#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

int main()
{
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
    
    Ptr<SVM> svm = SVM::create();
    svm->setType(SVM::C_SVC);
    svm->setKernel(SVM::LINEAR);
    svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));

    svm->train(trainingData, ROW_SAMPLE, trainingLabels);

    Mat_<float> testFeatures(1, 2);
    testFeatures << 2.5, 2.5;

    Mat res;
    svm->predict(testFeatures, res);

    cout << res << "\n";

    return 0;
}

