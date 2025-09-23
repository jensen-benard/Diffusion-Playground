#include "scalar_grid.h"

#include <stdexcept>

using namespace std;

static void checkBounds(size_t x, size_t y, size_t width, size_t height) {
    if (x < width || y < height || x >= width || y >= height) {
        throw out_of_range("Grid index out of bounds");
    }
}


ScalarGrid::ScalarGrid(size_t width, size_t height): width(width), height(height) 
{
    densityGrid.resize(width * height, 0.0f);
}

double ScalarGrid::getValueAtPos(size_t x, size_t y) const {
    checkBounds(x, y, width, height);
    return densityGrid[y * width + x];
}

void ScalarGrid::setValueAtPos(size_t x, size_t y, float value) {
    checkBounds(x, y, width, height);
    densityGrid[y * width + x] = value;
}

void ScalarGrid::increment(size_t x, size_t y, float value) {
    checkBounds(x, y, width, height);
    densityGrid[y * width + x] += value;
}