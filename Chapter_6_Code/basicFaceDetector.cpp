#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

String face_cascade_file = "data/haarcascade_frontalface_alt.xml";

int main(int argc, char** argv)
{

    if (argc != 2) {
        cout << "Please provide the name of the input file as a command-line argument.\n"
            << "Sample usage : ./basicFaceDetector images/Emma_Watson.jpg\n";
        return 1;
    }

    char* file_name = argv[1];
    Mat input_image = imread(file_name);

    CascadeClassifier face_cascade;
    face_cascade.load(face_cascade_file);
    
    vector<Rect> faces;
    face_cascade.detectMultiScale(input_image, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30));
    

    cout << faces.size() << " faces detected...\n";
    for (int i = 0; i < faces.size(); ++i) {
        Rect detected_face = faces[i];
        rectangle(input_image, detected_face, Scalar(255, 0, 0), 2);
    }

    imshow("Faces", input_image);
    waitKey(0);
    return 0;
}
