#include <iostream>
#include <vector>
#include <fstream>
#include <cstdio>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>


using namespace std;
using namespace cv;
using namespace cv::ml;

const int NUM_TRAINING_EXAMPLES = 80;
const int NUM_FEATURES = 531;
const int NUM_TEST_EXAMPLES = 20;

int main(int argc, char** argv){
	if(argc !=3)   {
		cout << "USAGE: ./svm [TRAINING] [TEST]\n";
		return -1;   
	}   
	const char* training_file = argv[1];
	const char* test_file = argv[2];
	
	ifstream fin_train, fin_test;
	fin_train.open(training_file);
	fin_test.open(test_file);

	Mat training_data(NUM_TRAINING_EXAMPLES, NUM_FEATURES, CV_32FC1);
	Mat class_labels(NUM_TRAINING_EXAMPLES, 1, CV_32FC1);

	Mat test_data(NUM_TEST_EXAMPLES, NUM_FEATURES, CV_32FC1);
	Mat prediction_results(NUM_TEST_EXAMPLES, 1, CV_32FC1);
	
	for(int i = 0; i < NUM_TRAINING_EXAMPLES; ++i) {
		for(int j = 0; j < (NUM_FEATURES+1);++j) {
			vector<float> example((NUM_FEATURES+1), 0.0f);
			fin_train >> example[j];
			
			if(j < NUM_FEATURES)
				training_data.at<float>(i, j) = example[j];
			else
				class_labels.at<float>(i, 0) = example[j];
		}   
	}

	vector<float> correct_results(NUM_TEST_EXAMPLES, 0.0f);
	for(int i = 0; i < NUM_TEST_EXAMPLES; ++i) {
		for(int j = 0; j < (NUM_FEATURES+1);++j) {
			if(j < NUM_FEATURES)
				fin_test >> test_data.at<float>(i, j);
		else
			fin_test >> correct_results[i];
		}
	}

	Ptr<SVM> svm = SVM::create();
	svm->setType(SVM::C_SVC);
	svm->setKernel(SVM::RBF);
	svm->setC(2);
	svm->setGamma(0.0000305176);
	svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 10000, 1e-6));

	svm->train(training_data, ROW_SAMPLE, class_labels);
	svm->predict(test_data, prediction_results);
	
	for(int i = 0; i < NUM_TEST_EXAMPLES; ++i) {
		float prediction = prediction_results.at<float>(i, 0);
		cout << prediction << " " << correct_results[i] << "\n";
	}

	return 0;
}
