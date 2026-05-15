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
    int& height)
{
    int channels;

    unsigned char* data = stbi_load(
        path.c_str(),
        &width,
        &height,
        &channels,
        1
    );

    if (!data)
    {
        cout << "Failed to load image\n";
        return false;
    }

    image.resize(width * height);

    for (int i = 0; i < width * height; i++)
    {
        image[i] = static_cast<float>(data[i]);
    }

    stbi_image_free(data);

    return true;
}

bool saveImage(
    const string& path,
    const vector<float>& image,
    int width,
    int height)
{
    vector<unsigned char> output(width * height);

    for (int i = 0; i < width * height; i++)
    {
        output[i] = static_cast<unsigned char>(
            clamp(image[i], 0.0f, 255.0f)
        );
    }

    int success = stbi_write_png(
        path.c_str(),
        width,
        height,
        1,
        output.data(),
        width
    );

    return success != 0;
}