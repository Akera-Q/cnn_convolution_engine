//convolution implementation using AVX2 and OpenMP for fast 3x3 filtering.
#include "convolution.h"
#include "utils.h"
#include <immintrin.h>
#include <omp.h>
#include <algorithm>

using namespace std;

constexpr int KERNEL_SIZE = 3;      //fixed 3x3 filter size.
constexpr int BLOCK_SIZE = 32;      //block size for tiling.

//function implementation. declared in convolution.h, defined here to keep the header clean.
void convolutionAVX2(
    const vector<float>& input,         //input image data in planar RGB format (separate planes for R, G, B channels).
    const vector<float>& kernel,        //3x3 convolution kernel values (e.g., blur, edge, sharpen).
    vector<float>& output,              //output buffer to store the convolved image results, also in planar RGB format.
    int width,                          //width of the input image (number of columns).
    int height,                         //height of the input image (number of rows).
    int channels                        //number of color channels in the input image.
)
{
    int outputWidth = width - KERNEL_SIZE + 1;          //needed for a valid conolution. it prevents accessing out of bounds pixels when applying the 3x3 kernel near the edges of the image.
    int outputHeight = height - KERNEL_SIZE + 1;        //same reason as above.
    int inputPlaneSize = width * height;
    int outputPlaneSize = outputWidth * outputHeight;

    // Precompute kernel values to avoid redundant _mm256_set1_ps calls in the hot loop.
    __m256 kernelVecs[KERNEL_SIZE][KERNEL_SIZE];
    for (int ki = 0; ki < KERNEL_SIZE; ki++)
    {
        for (int kj = 0; kj < KERNEL_SIZE; kj++)
        {
            kernelVecs[ki][kj] = _mm256_set1_ps(
                kernel[idx(ki, kj, KERNEL_SIZE)]
            );
        }
    }

    // Process each RGB channel independently in planar layout.
    for (int c = 0; c < channels; c++)
    {
        const float* inputPlane = &input[c * inputPlaneSize];
        float* outputPlane = &output[c * outputPlaneSize];
        //collapse(2) parallelizes the two nested loops as if they were one loop, allowing for better load balancing across threads. 
        //schedule(static) divides the iterations into equal-sized chunks that are statically assigned to threads.
        //this can improve cache performance and reduce overhead in this case since the workload is predictable.
        #pragma omp parallel for collapse(2) schedule(static)
        for (int ii = 0; ii < outputHeight; ii += BLOCK_SIZE)
        {
            for (int jj = 0; jj < outputWidth; jj += BLOCK_SIZE)
            {
                int iLimit = min(ii + BLOCK_SIZE, outputHeight);
                int jLimit = min(jj + BLOCK_SIZE, outputWidth);

                for (int i = ii; i < iLimit; i++)
                {
                    int j = jj;
                    // Process 16 pixels (2x AVX2 vectors) per iteration for better ILP and cache efficiency.
                    for (; j + 16 <= jLimit; j += 16)
                    {
                        __m256 sum0 = _mm256_setzero_ps();
                        __m256 sum1 = _mm256_setzero_ps();

                        for (int ki = 0; ki < KERNEL_SIZE; ki++)
                        {
                            for (int kj = 0; kj < KERNEL_SIZE; kj++)
                            {
                                __m256 inputVec0 = _mm256_loadu_ps(
                                    &inputPlane[idx(i + ki, j + kj, width)]
                                );
                                __m256 inputVec1 = _mm256_loadu_ps(
                                    &inputPlane[idx(i + ki, j + 8 + kj, width)]
                                );

                                sum0 = _mm256_add_ps(
                                    sum0,
                                    _mm256_mul_ps(inputVec0, kernelVecs[ki][kj])
                                );
                                sum1 = _mm256_add_ps(
                                    sum1,
                                    _mm256_mul_ps(inputVec1, kernelVecs[ki][kj])
                                );
                            }
                        }

                        _mm256_storeu_ps(
                            &outputPlane[idx(i, j, outputWidth)],
                            sum0
                        );
                        _mm256_storeu_ps(
                            &outputPlane[idx(i, j + 8, outputWidth)],
                            sum1
                        );
                    }

                    // Process remaining pixels in 8-pixel chunks.
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

                                sum = _mm256_add_ps(
                                    sum,
                                    _mm256_mul_ps(inputVec, kernelVecs[ki][kj])
                                );
                            }
                        }

                        _mm256_storeu_ps(
                            &outputPlane[idx(i, j, outputWidth)],
                            sum
                        );
                    }

                    // Scalar tail for remaining pixels.
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