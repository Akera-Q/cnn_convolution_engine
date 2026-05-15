// Main entry point for the backend image processor.
// Loads an input image, applies a convolution filter, and writes the output image.

#include <iostream>
#include <chrono>

#include "convolution.h"
#include "image_loader.h"
#include "filters.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        cout << "Usage: ./cnn_processor input output filter\n";
        return 1;
    }

    // Read the command-line arguments: input path, output path, and filter type.
    string inputPath = argv[1];
    string outputPath = argv[2];
    string filterType = argv[3];

    vector<float> input;

    int width;
    int height;
    int channels;

    if (!loadImage(inputPath, input, width, height, channels))
    {
        return 1;
    }

    vector<float> kernel;

    // Choose the selected filter kernel from the available predefined options.
    if (filterType == "blur")
    {
        kernel = getBlurKernel();
    }
    else if (filterType == "edge")
    {
        kernel = getEdgeKernel();
    }
    else
    {
        kernel = getSharpenKernel();
    }

    // After a 3x3 convolution, the output image is smaller by one pixel
    // on each border in both dimensions.
    int outputWidth = width - 2;
    int outputHeight = height - 2;

    // Allocate the output buffer for all RGB channels and initialize.
    vector<float> output(
        outputWidth * outputHeight * channels,
        0.0f
    );

    auto start = high_resolution_clock::now();

    convolutionAVX2(
        input,
        kernel,
        output,
        width,
        height,
        channels
    );

    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Execution Time: "
         << duration.count()
         << " ms\n";

    if (!saveImage(outputPath, output, outputWidth, outputHeight, channels))
    {
        cout << "Failed to save image\n";
        return 1;
    }

    return 0;
}