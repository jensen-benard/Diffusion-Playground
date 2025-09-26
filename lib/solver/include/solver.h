#ifndef SOLVER_H
#define SOLVER_H

#include <vector>

class Grid;


class Solver {
    public:
        virtual void step() = 0;
        virtual bool isMaxStepReached() const = 0;
        virtual const Grid& getDensityGrid() = 0;
        virtual unsigned int getCurrentStep() const = 0;
};

#endif