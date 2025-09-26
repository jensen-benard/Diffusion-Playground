#ifndef SIMULATION_CONTROLLER_H
#define SIMULATION_CONTROLLER_H

#include "window.h"
#include "solver.h"

struct SimulationConfig {
    double stepsPerSecond;
};

class SimulationController {
    public:
        SimulationController(Window& window, Solver& solver, SimulationConfig config);
        ~SimulationController() {};

        void run();
        bool hasStopped() { return stopped; }
        void stop() { stopped = true; }

        void onWindowClose() { stop(); }
        
    private:
        Window& window;
        Solver& solver;

        SimulationConfig config;

        bool stopped = false;

        EventCallbacks eventCallbacks;

};

#endif