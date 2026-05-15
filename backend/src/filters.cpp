//filter kernel definitions for blur, edge, and sharpen effects.
#include "filters.h"

//each matrix performs its respective convolution operation when applied to the input image, producing the desired visual effect.
vector<float> getBlurKernel()
{
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