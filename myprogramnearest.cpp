#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

Mat resizeNearestNeighbor(const Mat& src, int newWidth, int newHeight) {
    Mat dst(newHeight, newWidth, src.type());

    double scaleX = static_cast<double>(src.cols) / newWidth;
    double scaleY = static_cast<double>(src.rows) / newHeight;

    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            int srcX = static_cast<int>(x * scaleX);
            int srcY = static_cast<int>(y * scaleY);

            // Nearest-neighbor interpolation
            dst.at<Vec3b>(y, x) = src.at<Vec3b>(srcY, srcX);
        }
    }

    return dst;
}

int main() {
    // Read an image from file
    Mat src = imread("/home/athul/Documents/OpenCV/G178_2 -1080.BMP");

    // Define the desired output size
    int newWidth = src.cols / 2;
    int newHeight = src.rows / 2;

    // Resize the image using nearest-neighbor interpolation
    Mat dst = resizeNearestNeighbor(src, newWidth, newHeight);

    // Display the original and resized images
    imshow("Original", src);
    imshow("Resized (Nearest Neighbor)", dst);

    // Wait for a key press to exit
    waitKey(0);

    return 0;
}
