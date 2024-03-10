#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main() {
    // Read an image from file
    Mat src = imread("/home/athul/Documents/OpenCV/G178_2 -1080.BMP");

    int newWidth = src.cols / 2;
    int newHeight = src.rows / 2;
    Size newSize(newWidth, newHeight);

    // Resize the image using cv::resize function with different interpolation methods
    Mat dst_linear, dst_nearest, dst_cubic;

    resize(src, dst_linear, newSize, 0, 0, INTER_LINEAR); // Bilinear interpolation
    resize(src, dst_nearest, newSize, 0, 0, INTER_NEAREST); // Nearest-neighbor interpolation
    resize(src, dst_cubic, newSize, 0, 0, INTER_CUBIC); // Bicubic interpolation

    // Display the original and resized images
    imshow("Original", src);
    imshow("Resized (Linear)", dst_linear);
    imshow("Resized (Nearest Neighbor)", dst_nearest);
    imshow("Resized (Bicubic)", dst_cubic);

    // Wait for a key press to exit
    waitKey(0);

    return 0;
}
