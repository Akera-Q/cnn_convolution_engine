// Filter kernel definitions for blur, edge, and sharpen effects.
#include "filters.h"

vector<float> getBlurKernel()
{
    // Average filter that computes a mean over the 3x3 neighborhood.
    return {
        1.0f / 9, 1.0f / 9, 1.0f / 9,
        1.0f / 9, 1.0f / 9, 1.0f / 9,
        1.0f / 9, 1.0f / 9, 1.0f / 9
    };
}

vector<float> getEdgeKernel()
{
    return {
        -1, -1, -1,
        -1,  8, -1,
        -1, -1, -1
    };
}

vector<float> getSharpenKernel()
{
    return {
         0, -1,  0,
        -1,  5, -1,
         0, -1,  0
    };
}