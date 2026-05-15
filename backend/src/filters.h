#pragma once

// Kernel factory declarations used by the backend filter selection.
#include <vector>
using namespace std;

vector<float> getBlurKernel();
vector<float> getEdgeKernel();
vector<float> getSharpenKernel();