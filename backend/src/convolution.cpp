// Convolution implementation using AVX2 and OpenMP for fast 3x3 filtering.
#include "convolution.h"
#include "utils.h"
#include <immintrin.h>
#include <omp.h>
#include <algorithm>

using namespace std;

constexpr int KERNEL_SIZE = 3;
constexpr int BLOCK_SIZE = 32;

void convolutionAVX2(
    const vector<float>& input,
    const vector<float>& kernel,
    vector<float>& output,
    int width,
    int height,
    int channels)
{
    int outputWidth = width - KERNEL_SIZE + 1;
    int outputHeight = height - KERNEL_SIZE + 1;
    int inputPlaneSize = width * height;
    int outputPlaneSize = outputWidth * outputHeight;

    // Process each channel independently in planar layout.
    #pragma omp parallel for collapse(3) schedule(static)
    for (int c = 0; c < channels; c++)
    {
        for (int ii = 0; ii < outputHeight; ii += BLOCK_SIZE)
        {
            for (int jj = 0; jj < outputWidth; jj += BLOCK_SIZE)
            {
                int iLimit = min(ii + BLOCK_SIZE, outputHeight);
                int jLimit = min(jj + BLOCK_SIZE, outputWidth);
                const float* inputPlane = &input[c * inputPlaneSize];
                float* outputPlane = &output[c * outputPlaneSize];

                for (int i = ii; i < iLimit; i++)
                {
                    int j = jj;
                    for (; j + 8 <= jLimit; j += 8)
                    {
                        __m256 sum = _mm256_setzero_ps();

                        for (int ki = 0; ki < KERNEL_SIZE; ki++)
                        {
                            for (int kj = 0; kj < KERNEL_SIZE; kj++)
                            {
                                __m256 inputVec = _mm256_loadu_ps(
                                    &inputPlane[idx(i + ki, j + kj, width)]
                                );

                                __m256 kernelVec = _mm256_set1_ps(
                                    kernel[idx(ki, kj, KERNEL_SIZE)]
                                );

                                sum = _mm256_add_ps(
                                    sum,
                                    _mm256_mul_ps(inputVec, kernelVec)
                                );
                            }
                        }

                        _mm256_storeu_ps(
                            &outputPlane[idx(i, j, outputWidth)],
                            sum
                        );
                    }

                    for (; j < jLimit; j++)
                    {
                        float scalarSum = 0.0f;

                        for (int ki = 0; ki < KERNEL_SIZE; ki++)
                        {
                            for (int kj = 0; kj < KERNEL_SIZE; kj++)
                            {
                                scalarSum += inputPlane[idx(i + ki, j + kj, width)] *
                                    kernel[idx(ki, kj, KERNEL_SIZE)];
                            }
                        }

                        outputPlane[idx(i, j, outputWidth)] = scalarSum;
                    }
                }
            }
        }
    }
}