#pragma once

#include <vector>
#include <string>

using namespace std;

bool loadImage(
    const string& path,
    vector<float>& image,
    int& width,
    int& height
);

bool saveImage(
    const string& path,
    const vector<float>& image,
    int width,
    int height
);