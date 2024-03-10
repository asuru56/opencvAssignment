#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

using namespace cv;
using namespace std;

int main() {
    // Read an image from file
    Mat src = imread("input.jpg");

    // Check if the image was loaded successfully
    if (src.empty()) {
        cerr << "Error: Unable to load image file" << endl;
        return 1;
    }

    int newWidth = src.cols / 2;
    int newHeight = src.rows / 2;
    Size newSize(newWidth, newHeight);

    // Timing measurements for Inter_Linear
    auto start_linear = chrono::steady_clock::now();
    for (int i = 0; i < 1000; ++i) {
        Mat dst_linear;
        resize(src, dst_linear, newSize, 0, 0, INTER_LINEAR); // Bilinear interpolation
    }
    auto end_linear = chrono::steady_clock::now();
    
    //Output in ms
    auto duration_linear = chrono::duration_cast<chrono::milliseconds>(end_linear - start_linear);
    cout << "Time taken for 1000 iterations using INTER_LINEAR: " << duration_linear.count() << " ms" << endl;
    
    //Timing for Inter_Nearest
    auto start_nearest = chrono::steady_clock::now();
    for (int i = 0; i < 1000; ++i) {
        Mat dst_nearest;
        resize(src, dst_nearest, newSize, 0, 0, INTER_NEAREST); // Nearest-neighbor interpolation
    }
    auto end_nearest = chrono::steady_clock::now();
    
    //Output in ms
    auto duration_nearest = chrono::duration_cast<chrono::milliseconds>(end_nearest - start_nearest);
    cout << "Time taken for 1000 iterations using INTER_NEAREST: " << duration_nearest.count() << " ms" << endl;
    
    //Timing for Inter_Cubic
    auto start_cubic = chrono::steady_clock::now();
    for (int i = 0; i < 1000; ++i) {
        Mat dst_cubic;
        resize(src, dst_cubic, newSize, 0, 0, INTER_CUBIC); // Bicubic interpolation
    }
    auto end_cubic = chrono::steady_clock::now();
    
    //Output in ms
    auto duration_cubic = chrono::duration_cast<chrono::milliseconds>(end_cubic - start_cubic);
    cout << "Time taken for 1000 iterations using INTER_CUBIC: " << duration_cubic.count() << " ms" << endl;

    return 0;
}
