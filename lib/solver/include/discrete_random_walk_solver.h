#ifndef DISCRETE_RANDOM_WALK_SOLVER_H
#define DISCRETE_RANDOM_WALK_SOLVER_H

#include <random>
#include <vector>
#include <cstddef>
#include <memory>
#include "solver.h"

struct WalkerInitialCondition {
    double posX;
    double posY;
    unsigned int count;
};

class ScalarGrid;

// CHANGE - change densityGRidwidth and hegith to resolution based instead. 
struct DiscreteRandomWalkSolverConfig {
    std::vector<WalkerInitialCondition> walkerInitialConditions;
    double walkerStepSize;
    int maxSteps;
    double solverWidth;
    double solverHeight;
    std::size_t densityGridWidth;
    std::size_t densityGridHeight;
    unsigned int randomNumberGeneratorSeed; 
};

class Walker;

class DiscreteRandomWalkSolver : public Solver {
    public:
        DiscreteRandomWalkSolver(DiscreteRandomWalkSolverConfig config);

        ~DiscreteRandomWalkSolver();

        void step() override;
        bool isMaxStepReached() const override { return maxStepReached; };
        const Grid& getDensityGrid() override;
        unsigned int getCurrentStep() const override { return currentStep; }
 
    private:
        double getRandomStep();
        void initWalkers();

        DiscreteRandomWalkSolverConfig config;
        int currentStep = 0;
        bool maxStepReached = false;

        std::vector<Walker> walkers;

        std::mt19937 randomNumberGenerator;
        std::uniform_real_distribution<double> uniformDistribution;

        std::unique_ptr<ScalarGrid> densityGrid;
};

#endif