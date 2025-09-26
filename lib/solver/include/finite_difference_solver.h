#ifndef FINITE_DIFFERENCE_SOLVER_H
#define FINITE_DIFFERENCE_SOLVER_H

#include "solver.h"
#include <memory>
#include <vector>
#include <cstddef>

class ScalarGrid;

struct FiniteDifferenceSolverConfig {

    double diffusionConstant;
    double gridSpacing;
    double deltaTime;

    int maxSteps;
    double solverWidth;
    double solverHeight;
    std::size_t densityGridWidth;
    std::size_t densityGridHeight;
};

class FiniteDifferenceSolver : public Solver {
    public:
        FiniteDifferenceSolver(FiniteDifferenceSolverConfig config);
        ~FiniteDifferenceSolver();

        void step() override;
        bool isMaxStepReached() const override { return maxStepReached; }
        const Grid& getDensityGrid() override;
        unsigned int getCurrentStep() const override { return currentStep; }

    private:
        size_t getIndex(size_t x, size_t y);
        void setBoundaryConditions();

        FiniteDifferenceSolverConfig config;
        unsigned int currentStep = 0;
        bool maxStepReached = false;

        std::vector<double> prevStepConcentrationGrid;

        std::unique_ptr<ScalarGrid> densityGrid;


};

#endif