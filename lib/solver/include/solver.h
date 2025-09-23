#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include "grid.h"


class Solver {
    public:
        virtual void step() = 0;
        virtual bool isMaxStepReached() const = 0;
        virtual const Grid& getDensityGrid() = 0;
};

#endif