#pragma once

// Utility helper for converting 2D pixel coordinates into a linear vector index.
inline int idx(int row, int col, int width)
{
    return row * width + col;
}