#pragma once

//utility helper for converting 2D pixel coordinates into a linear vector index (lay out matrix elements for easier access and memory management).
//row and width variables are the inputted row and column of the image matrix, while width is the original number of columns.
//using this function allows us to easily access the correct position in the 1D vector that represents the 2D image.
inline int idx(int row, int col, int width)
{
    return row * width + col;
}