#include "discrete_random_walk_solver.h"
#include <random>

void DiscreteRandomWalkSolver::initWalkers()
{
    walkers.reserve(config.totalWalkers);
    for (int i = 0; i < config.totalWalkers; i++) {
        walkers.emplace_back(config.walkerInitialConditions[i].posX, config.walkerInitialConditions[i].posY);
    }
}

DiscreteRandomWalkSolver::DiscreteRandomWalkSolver(DiscreteRandomWalkSolverConfig config) :
    config(config), 
    randomNumberGenerator(config.randomNumberGeneratorSeed),
    uniformDistribution(-config.walkerStepSize, config.walkerStepSize),
    densityGrid(config.densityGridWidth, config.densityGridHeight)
{
    initWalkers();
}


DiscreteRandomWalkSolver::~DiscreteRandomWalkSolver() {}

double DiscreteRandomWalkSolver::getRandomStep() {
    return uniformDistribution(randomNumberGenerator);
}


void DiscreteRandomWalkSolver::step() 
{
    if (currentStep >= config.maxSteps) {
        maxStepReached = true;
        return;
    }

    densityGrid.clear();

    for (auto& walker : walkers) {
        // Update the density Grid
        double scaleX = static_cast<double>(config.densityGridWidth) / config.solverWidth;
        double scaleY = static_cast<double>(config.densityGridHeight) / config.solverHeight;

        int gridX = static_cast<int>(walker.getPosX() * scaleX);
        int gridY = static_cast<int>(walker.getPosY() * scaleY);

        if (gridX >= 0 && gridX < config.densityGridWidth && gridY >= 0 && gridY < config.densityGridHeight) {
            densityGrid.increment(gridX, gridY, 1.0);
        }
        
        // Update solver
        double deltaXStep = getRandomStep();
        double deltaYStep = getRandomStep();

        double nextPosX = walker.getPosX() + deltaXStep;
        double nextPosY = walker.getPosY() + deltaYStep;
        
        // No boundary conditions

        walker.setPos(nextPosX, nextPosY);
    }

    currentStep++;
}