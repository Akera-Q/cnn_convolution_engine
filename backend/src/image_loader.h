#pragma once

// Image loader/saver declarations used by the backend processor.
// The implementation converts input images to planar RGB float buffers and
// writes processed results back to PNG files.
#include <vector>
#include <string>

using namespace std;

bool loadImage(
    const string& path,
    vector<float>& image,
    int& width,
    int& height,
    int& channels
);

bool saveImage(
    const string& path,
    const vector<float>& image,
    int width,
    int height,
    int channels
);