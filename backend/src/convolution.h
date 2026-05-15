#pragma once

#include <vector>
using namespace std;

//perform a 3x3 convolution using AVX2 and OpenMP. actual implementation is in convolution.cpp, this is just the declaration to keep the header clean.
void convolutionAVX2(
    const vector<float>& input,         //input image data in planar RGB format (separate planes for R, G, B channels).
    const vector<float>& kernel,        //3x3 convolution kernel values (e.g., blur, edge, sharpen).
    vector<float>& output,              //output buffer to store the convolved image results, also in planar RGB format.
    int width,                          //width of the input image (number of columns).
    int height,                         //height of the input image (number of rows).
    int channels                        //number of color channels in the input image.
);
//one channel is one layer making it use gray scale. three make it use RGB. four will be used later for RGBA (alpha channel for transparency).