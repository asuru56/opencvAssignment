#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

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

int main() {
    Mat input_image = imread("input.jpg");

    if (input_image.empty()) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    double scale_factor = 0.5; // Specify the scale factor (e.g., 0.5 for halving the size)

    Mat resized_image = resizeImage(input_image, scale_factor);

    imshow("Original Image", input_image);
    imshow("Resized Image", resized_image);
    waitKey(0);

    return 0;
}
