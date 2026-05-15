#pragma once

//declares functions that return convolution kernels(matrices that define the filter).
//helps to keep the main convolution code clean and focused on processing, while the kernel definitions are organized separately.
#include <vector>
using namespace std;

vector<float> getBlurKernel();
vector<float> getEdgeKernel();
vector<float> getSharpenKernel();