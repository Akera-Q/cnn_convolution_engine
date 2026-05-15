#pragma once

#include <vector>
using namespace std;

// Perform a 3x3 convolution using AVX2 and OpenMP.
// The caller supplies the input image, the kernel values,
// an output buffer, the input image dimensions, and the channel count.
void convolutionAVX2(
    const vector<float>& input,
    const vector<float>& kernel,
    vector<float>& output,
    int width,
    int height,
    int channels
);