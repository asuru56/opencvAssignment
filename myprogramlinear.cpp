#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

using namespace std
using namespace cv;

Mat resizeLinear(const Mat& src, int newWidth, int newHeight) {
    Mat dst(newHeight, newWidth, src.type());

    double scaleX = static_cast<double>(src.cols) / newWidth;
    double scaleY = static_cast<double>(src.rows) / newHeight;

    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            double srcX = x * scaleX;
            double srcY = y * scaleY;

            int x1 = static_cast<int>(srcX);
            int y1 = static_cast<int>(srcY);
            int x2 = std::min(x1 + 1, src.cols - 1);
            int y2 = std::min(y1 + 1, src.rows - 1);

            double tx = srcX - x1;
            double ty = srcY - y1;

            // Linear interpolation in each channel
            Vec3b value1 = src.at<Vec3b>(y1, x1) * (1 - tx) + src.at<Vec3b>(y1, x2) * tx;
            Vec3b value2 = src.at<Vec3b>(y2, x1) * (1 - tx) + src.at<Vec3b>(y2, x2) * tx;
            Vec3b result = value1 * (1 - ty) + value2 * ty;

            dst.at<Vec3b>(y, x) = result;
        }
    }

    return dst;
}

 
int main() {
    // Load the input image
    Mat input_image = imread("input.jpg");

    // Check if the image was loaded successfully
    if (input_image.empty()) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    // Specify the desired new dimensions for the image
    int new_width = input_image.cols / 2; // Half the width
    int new_height = input_image.rows / 2; // Half the height

    // Repeat the resizing operation 1000 times and measure the total time
    auto start_time = high_resolution_clock::now();

    for (int i = 0; i < 1000; ++i) {
        Mat resized_image = resizeLinear(input_image, new_width, new_height);
    }

    auto end_time = high_resolution_clock::now();
    auto duration_ms = duration_cast<milliseconds>(end_time - start_time);

    cout << "Total time for 1000 resizes: " << duration_ms.count() << " ms" << endl;

    return 0;
}
