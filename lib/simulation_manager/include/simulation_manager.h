#ifndef SIMULATION_MANAGER_H
#define SIMULATION_MANAGER_H

#include <memory>

class Solver;
class FixedTimer;
class Grid;

struct SimulationConfig {
    double stepsPerSecond;
};

struct SimulationState {
    const Grid& densityGrid;
    unsigned int currentStep;
};

class SimulationManager {
public:
    SimulationManager(Solver& solver, SimulationConfig config);
    ~SimulationManager();

    void update();

    bool hasStopped();

    SimulationState getState();
    

private:
    Solver& solver;
    SimulationConfig config;

    bool stopped = false;

    std::unique_ptr<FixedTimer> timer;
};

#endif
