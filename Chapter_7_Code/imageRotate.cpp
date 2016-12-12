#include <iostream>
#include <cmath>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

#define PI 3.14159265

float getAngleInRad(Point A, Point B) {
    float A_x = A.x;
    float A_y = A.y;
    float B_x = B.x;
    float B_y = B.y;

    float slope = ((B_y - A_y) / (B_x - A_x));
    return (-1 * atan(slope));
}

Mat getAffineTransformationMatrix(float rotation_angle, Point center_rotation) {
    
    float cos_rotation_angle = cos(rotation_angle);
    float sin_rotation_angle = sin(rotation_angle);

    float A = cos_rotation_angle;
    float B = sin_rotation_angle;
    float C = center_rotation.x - (center_rotation.x*A) - (center_rotation.y*B);
    float D = -1 * sin_rotation_angle;
    float E = cos_rotation_angle;
    float F = center_rotation.y - (center_rotation.x*D) - (center_rotation.y*E);

    Mat affine_transformation_matrix = Mat(2, 3, CV_32FC1);
    affine_transformation_matrix.at<float>(0, 0) = A;
    affine_transformation_matrix.at<float>(0, 1) = B;
    affine_transformation_matrix.at<float>(0, 2) = C;
    affine_transformation_matrix.at<float>(1, 0) = D;
    affine_transformation_matrix.at<float>(1, 1) = E;
    affine_transformation_matrix.at<float>(1, 2) = F;

    return affine_transformation_matrix;

}

void rotateFace(Mat original_face, Point left_eye, Point right_eye) {
    
    float angle_line_joining_eyes = getAngleInRad(left_eye, right_eye);
    float rotation_angle = (-1 * angle_line_joining_eyes);
    Mat affine_transformation_matrix = getAffineTransformationMatrix(rotation_angle, left_eye);

    Mat rotated_face;
    warpAffine(original_face, rotated_face, affine_transformation_matrix, original_face.size());

    imshow("Original_Image", original_face);
    imshow("Rotated_Image", rotated_face);
    waitKey(0);
}

/*
 * The code in the main() function operates on a single image at a time.
 * Readers are encouraged to modify the same so that it runs on multiple images.
 * For that, you cn follow the template in markEyeLocations.cpp for reading image paths and
 * corresponding eye locations into appropriate data structures.
*/

int main()
{
    Mat face_image = imread("images/Dataset/Tom_Cruise_0006.jpg", IMREAD_GRAYSCALE);
    rotateFace(face_image, Point(105, 107), Point(149, 115));
    return 0;
}
