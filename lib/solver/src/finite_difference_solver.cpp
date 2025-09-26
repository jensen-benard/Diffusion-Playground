#include "finite_difference_solver.h"

#include "scalar_grid.h"
#include "math.h"
#include <cstdint>

FiniteDifferenceSolver::FiniteDifferenceSolver(FiniteDifferenceSolverConfig config) : config(config), 
    densityGrid(std::make_unique<ScalarGrid>(config.densityGridWidth, config.densityGridHeight)),
    prevStepConcentrationGrid(config.solverWidth * config.solverHeight, 0.0f)
{
    setBoundaryConditions();

    // Set initial concentration
    size_t x = (config.solverWidth) / 2;
    size_t y = (config.solverHeight) / 2;
    size_t index = getIndex(x, y);
    prevStepConcentrationGrid[index] = 1000.0f;
}

FiniteDifferenceSolver::~FiniteDifferenceSolver() {}

size_t FiniteDifferenceSolver::getIndex(size_t x, size_t y) {
    return y * config.solverWidth + x;
}


void FiniteDifferenceSolver::setBoundaryConditions() {
    
    // Set Dirichlet boundary conditions as 0.0f
    for (int y = 0; y < config.solverHeight; y++) {
        int x = 0;
        prevStepConcentrationGrid[getIndex(x, y)] = 0.0f;

        x = config.solverWidth - 1;
        prevStepConcentrationGrid[getIndex(x, y)] = 0.0f;
    }

    for (int x = 0; x < config.solverWidth; x++) {
        int y = 0;
        prevStepConcentrationGrid[getIndex(x, y)] = 0.0f;

        y = config.solverHeight - 1;
        prevStepConcentrationGrid[getIndex(x, y)] = 0.0f;
    }
}

void FiniteDifferenceSolver::step() 
{

    std::vector<double> currStepConcentrationGrid = prevStepConcentrationGrid;

    for (size_t y = 1; y < config.solverHeight - 1; y++) {
        for (size_t x = 1; x < config.solverWidth - 1; x++) {
            float cLeft = prevStepConcentrationGrid[getIndex(x - 1, y)];
            float cRight = prevStepConcentrationGrid[getIndex(x + 1, y)];
            float cUp = prevStepConcentrationGrid[getIndex(x, y - 1)];
            float cDown = prevStepConcentrationGrid[getIndex(x, y + 1)];
            float cCenter = prevStepConcentrationGrid[getIndex(x, y)];
            float laplacian = (cLeft + cRight + cUp + cDown - 4.0f * cCenter) / (config.gridSpacing * config.gridSpacing);
            
            currStepConcentrationGrid[getIndex(x, y)] = cCenter + config.diffusionConstant * laplacian * config.deltaTime;
            if (x >= 0 && x < config.densityGridWidth && y >= 0 && y < config.densityGridHeight) {
                densityGrid->setValueAtPos(x, y, currStepConcentrationGrid[getIndex(x, y)]);
            }
        }
    }

    prevStepConcentrationGrid = currStepConcentrationGrid;

}

const Grid& FiniteDifferenceSolver::getDensityGrid() {
    return *densityGrid;
}