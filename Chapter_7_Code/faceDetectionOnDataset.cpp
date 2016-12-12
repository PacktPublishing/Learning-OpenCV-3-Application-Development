#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

String face_cascade_file = "data/haarcascade_frontalface_alt.xml";

int main(int argc, char** argv)
{
    CascadeClassifier face_cascade;
    face_cascade.load(face_cascade_file);

    if (argc != 2) {
        cout << "Please enter the name of the file as a command-line argument.\n"
            << "Sample usage : ./faceDetectionOnDataset images/Dataset/fileNames.txt\n";
        return -1;
    }

    char* file_name = argv[1];
    ifstream fin(file_name);

    for(string image_path; getline(fin, image_path);) {    
        Mat input_image = imread(image_path);
        vector<Rect> faces;
        face_cascade.detectMultiScale(
            input_image, faces, 
		    1.1, 
		    2, 
		    0|CASCADE_SCALE_IMAGE, 
		    Size(30, 30)
        );
    
        for (int i = 0; i < faces.size(); ++i) {
            Rect detected_face = faces[i];
            rectangle(input_image, detected_face, Scalar(255, 0, 0), 2);
        }
        
        imshow("Detetced_Face", input_image);
        waitKey(0);
    }

    return 0;
}


