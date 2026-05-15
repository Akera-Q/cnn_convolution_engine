#pragma once

#include <vector>
using namespace std;

void convolutionAVX2(
    const vector<float>& input,
    const vector<float>& kernel,
    vector<float>& output,
    int width,
    int height
);