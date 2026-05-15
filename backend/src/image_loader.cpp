// Image loading and saving implementation based on stb_image and stb_image_write.
// Converts image pixels to float values for convolution processing.
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "image_loader.h"

#include "../external/stb_image.h"
#include "../external/stb_image_write.h"

#include <iostream>
#include <algorithm>

using namespace std;

bool loadImage(
    const string& path,
    vector<float>& image,
    int& width,
    int& height,
    int& channels)
{
    const int desiredChannels = 3;

    unsigned char* data = stbi_load(
        path.c_str(),
        &width,
        &height,
        &channels,
        desiredChannels
    );

    if (!data)
    {
        cout << "Failed to load image\n";
        return false;
    }

    channels = desiredChannels;
    int pixelCount = width * height;
    image.resize(pixelCount * channels);

    for (int i = 0; i < pixelCount; i++)
    {
        for (int c = 0; c < channels; c++)
        {
            image[c * pixelCount + i] = static_cast<float>(
                data[i * channels + c]
            );
        }
    }

    stbi_image_free(data);

    return true;
}

bool saveImage(
    const string& path,
    const vector<float>& image,
    int width,
    int height,
    int channels)
{
    int pixelCount = width * height;
    vector<unsigned char> output(pixelCount * channels);

    for (int i = 0; i < pixelCount; i++)
    {
        for (int c = 0; c < channels; c++)
        {
            output[i * channels + c] = static_cast<unsigned char>(
                clamp(image[c * pixelCount + i], 0.0f, 255.0f)
            );
        }
    }

    int success = stbi_write_png(
        path.c_str(),
        width,
        height,
        channels,
        output.data(),
        width * channels
    );

    return success != 0;
}