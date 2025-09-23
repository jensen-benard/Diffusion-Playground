#ifndef GRID_H
#define GRID_H

#include <cstddef>

enum boundaryCondition {
    NO_BOUNDARY   
};

class Grid {
    public:
        virtual ~Grid() = default;

        virtual double getValueAtPos(std::size_t x, std::size_t y) const = 0;
        virtual void setValueAtPos(std::size_t x, std::size_t y, float value) = 0;
        virtual void increment(std::size_t x, std::size_t y, float value) = 0;
        virtual void clear() = 0;

        virtual std::size_t getWidth() const = 0;
        virtual std::size_t getHeight() const = 0;


    private:
};

#endif