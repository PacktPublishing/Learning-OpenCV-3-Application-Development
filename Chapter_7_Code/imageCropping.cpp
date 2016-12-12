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

float getEuclideanDistance(Point A, Point B) {
    return sqrt( (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y) );
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

Mat rotateFace(Mat original_face, Point left_eye, Point right_eye) {
    
    float angle_line_joining_eyes = getAngleInRad(left_eye, right_eye);
    float rotation_angle = (-1 * angle_line_joining_eyes);
    Mat affine_transformation_matrix = getAffineTransformationMatrix(rotation_angle, left_eye);

    Mat rotated_face;
    warpAffine(original_face, rotated_face, affine_transformation_matrix, original_face.size());

    return rotated_face;
}

Point cropping_size(120, 120);
float offset_ratio = 0.23;
int horizontal_offset = int(floor(offset_ratio * cropping_size.x));
int vertical__offset = int(floor(offset_ratio * cropping_size.y));

/*
 * The code in the main() function operates on a single image at a time.
 * Readers are encouraged to modify the same so that it runs on multiple images.
 * For that, you cn follow the template in markEyeLocations.cpp for reading image paths and
 * corresponding eye locations into appropriate data structures.
 */

int main()
{
    Mat face_image = imread("images/Dataset/Kalpana_Chawla_0005.jpg", IMREAD_GRAYSCALE);
    Point left_eye(102, 115);
    Point right_eye(149, 114);

    float eye_sep_original = getEuclideanDistance(left_eye, right_eye);
    float eye_sep_cropped = cropping_size.x - (2 * horizontal_offset);
    float scale_factor = (eye_sep_original / eye_sep_cropped);

    int crop_anchor_x = left_eye.x - (scale_factor * horizontal_offset);
    int crop_anchor_y = left_eye.y - (scale_factor * vertical__offset);
    int crop_width = int(cropping_size.x * scale_factor);
    int crop_height = int(cropping_size.y * scale_factor);
    
    Rect ROI(crop_anchor_x, crop_anchor_y, crop_width, crop_height);
    Mat rotated_face = rotateFace(face_image, left_eye, right_eye);

    Mat cropped_face = rotated_face(ROI);
    Mat aligned_face;
    resize(cropped_face, aligned_face, cropping_size);
    
    cout << aligned_face.rows << " x" << aligned_face.cols << "\n";
    
    imshow("Aligned_Face", aligned_face); 
    waitKey(0);
    return 0;
}
