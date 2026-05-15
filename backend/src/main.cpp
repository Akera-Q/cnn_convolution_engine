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

    string inputPath = argv[1];
    string outputPath = argv[2];
    string filterType = argv[3];

    vector<float> input;

    int width;
    int height;

    if (!loadImage(inputPath, input, width, height))
    {
        return 1;
    }

    vector<float> kernel;

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

    int outputWidth = width - 2;
    int outputHeight = height - 2;

    vector<float> output(outputWidth * outputHeight, 0.0f);

    auto start = high_resolution_clock::now();

    convolutionAVX2(
        input,
        kernel,
        output,
        width,
        height
    );

    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Execution Time: "
         << duration.count()
         << " ms\n";

    if (!saveImage(outputPath, output, outputWidth, outputHeight))
    {
        cout << "Failed to save image\n";
        return 1;
    }

    return 0;
}