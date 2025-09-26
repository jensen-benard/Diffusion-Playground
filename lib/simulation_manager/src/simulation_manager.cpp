#include "simulation_manager.h"
#include "timer.h"
#include "solver.h"


SimulationManager::SimulationManager(Solver& solver, SimulationConfig config) : 
solver(solver), config(config), timer(std::make_unique<FixedTimer>(1.0 / config.stepsPerSecond)) {}

SimulationManager::~SimulationManager() {}


void SimulationManager::update() {

    if(stopped) { return; }

    
    timer->tick();

    if (timer->isDue()) {
        solver.step();
    }

    if (solver.isMaxStepReached()) {
        stopped = true;
    }
}

bool SimulationManager::hasStopped() {
    return stopped;
}


SimulationState SimulationManager::getState() {
    return {solver.getDensityGrid(), solver.getCurrentStep()};
}