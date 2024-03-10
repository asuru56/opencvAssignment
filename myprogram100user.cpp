#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace std;
using namespace cv;
using namespace std::chrono;

// Cubic interpolation function
double cubicInterpolation(double p[4], double x) {
    return p[1] + 0.5 * x * (p[2] - p[0] + x * (2.0 * p[0] - 5.0 * p[1] + 4.0 * p[2] - p[3] + x * (3.0 * (p[1] - p[2]) + p[3] - p[0])));
}

// Resize image using cubic interpolation
Mat resizeImage(const Mat& image, double scale_factor) {
    // Calculate new dimensions
    int new_height = static_cast<int>(image.rows * scale_factor);
    int new_width = static_cast<int>(image.cols * scale_factor);

    // Create a new empty image with the new dimensions
    Mat resized_image(new_height, new_width, image.type());

    // Perform cubic interpolation
    for (int y = 0; y < new_height; ++y) {
        for (int x = 0; x < new_width; ++x) {
            // Calculate the corresponding position in the original image
            double src_x = x / scale_factor;
            double src_y = y / scale_factor;

            int x1 = static_cast<int>(src_x);
            int y1 = static_cast<int>(src_y);

            // Compute the interpolation for each channel
            for (int c = 0; c < image.channels(); ++c) {
                double p[4];
                for (int i = 0; i < 4; ++i) {
                    int x_idx = std::max(0, std::min(image.cols - 1, x1 - 1 + i));
                    p[i] = image.at<Vec3b>(y1, x_idx)[c];
                }
                double interpolated_value = cubicInterpolation(p, src_x - x1);
                resized_image.at<Vec3b>(y, x)[c] = static_cast<uchar>(interpolated_value);
            }
        }
    }

    return resized_image;
}

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


Mat resizeNearest(const Mat& src, int newWidth, int newHeight) {
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
    Mat input_image = imread("G178_2 -1080.BMP");

    if (input_image.empty()) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    double scale_factor = 0.5; // Specify the scale factor (e.g., 0.5 for halving the size)

    int new_width = input_image.cols / 2; // Half the width
    int new_height = input_image.rows / 2; // Half the height

    // Repeat the resizing operation 1000 times and measure the total time
    auto start_time = high_resolution_clock::now();

    for (int i = 0; i < 1000; ++i) {
        Mat resized_image = resizeImage(input_image, scale_factor);
    }

    auto end_time = high_resolution_clock::now();
    auto duration_ms = duration_cast<milliseconds>(end_time - start_time);

    cout << "Total time for 1000 resizes: BiCubic " << duration_ms.count() << " ms" << endl;

    auto start_time2 = high_resolution_clock::now();

    for (int i = 0; i < 1000; ++i) {
        Mat resized_image = resizeLinear(input_image,new_width, new_height);
    }

    auto end_time2 = high_resolution_clock::now();
    auto duration_ms2 = duration_cast<milliseconds>(end_time2 - start_time2);

    cout << "Total time for 1000 resizes: BiLinear " << duration_ms2.count() << " ms" << endl;

    auto start_time3 = high_resolution_clock::now();

    for (int i = 0; i < 1000; ++i) {
        Mat resized_image = resizeNearest(input_image, new_width,new_height);
    }

    auto end_time3 = high_resolution_clock::now();
    auto duration_ms3 = duration_cast<milliseconds>(end_time3 - start_time3);

    cout << "Total time for 1000 resizes: Nearest Neighbour " << duration_ms3.count() << " ms" << endl;



    return 0;
}
