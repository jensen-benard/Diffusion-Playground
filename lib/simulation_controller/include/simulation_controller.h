#ifndef SIMULATION_CONTROLLER_H
#define SIMULATION_CONTROLLER_H

#include "window.h"
#include "solver.h"

struct SimulationConfig {
    double stepsPerSecond;

    double width;
    double height;
};

class SimulationController {
    public:
        SimulationController(Window& window, Solver& solver, SimulationConfig config) : window(window), solver(solver), config(config) {};
        ~SimulationController() {};

        void run();
        bool hasStopped() { return stopped; }
        void stop() { stopped = true; }
        
    private:
        Window& window;
        Solver& solver;

        SimulationConfig config;

        bool stopped = false;

};

#endif