#ifndef SCALAR_GRID_H
#define SCALAR_GRID_H

#include "grid.h"
#include <vector>
#include <cstddef>

class ScalarGrid : public Grid {
    public:
        ScalarGrid(std::size_t width, std::size_t height);
        ~ScalarGrid() = default;


        double getValueAtPos(std::size_t x, std::size_t y) const override;
        void setValueAtPos(std::size_t x, std::size_t y, float value) override;
        void clear() override { std::fill(densityGrid.begin(), densityGrid.end(), 0.0); }
        void increment(std::size_t x, std::size_t y, float value) override;

        std::size_t getWidth() const override { return width; }
        std::size_t getHeight() const override { return height; }
    private:
        std::vector<double> densityGrid;

        std::size_t width;
        std::size_t height;
};

#endif