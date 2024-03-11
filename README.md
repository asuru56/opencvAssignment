# opencvAssignment
OpenCV Assignment For Internship at DeepEdge.ai

S.No             User Defined Functions for 1000 Iterations  OpenCV functions for 1000 Iterations 
Nearest Neighbor 3248 ms                                     10 ms
BiLinear         129259 ms                                   20 ms
BiCubic          75077 ms                                    108 ms

Run the OpenCV with :  g++ -o myprogram myprogram`x`.cpp `pkg-config --cflags --libs opencv4` 
./myprogram

in Linux 

Program Breakdown: 

For Nearest Neighbor 

Ref:https://stackoverflow.com/questions/1550878/nearest-neighbor-interpolation-algorithm-in-matlab 

For Linear : 

If we choose a coordinate system in which the four points where f is known are (0, 0), (0, 1), (1, 0), and (1, 1), then the interpolation formula simplifies to
Thats what is done here for X1,X2,Y1,Y2 defined as in the code for x2 = x1+1 and y2 = x2+1 

Ref: https://en.wikipedia.org/wiki/Bilinear_interpolation 

For Bicubic Interpolation: 
Ref: https://www.paulinternet.nl/?page=bicubic 
