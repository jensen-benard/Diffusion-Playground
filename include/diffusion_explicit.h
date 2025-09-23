#ifndef DIFFUSION_EXPLICIT_H
#define DIFFUSION_EXPLICIT_H

#include <vector>
#include "window.h"
#include "timer.h"
#include <fstream>

struct DiffusionExplicitConfig {
    // Window parameters
    WindowConfig windowConfig;
    
    // Simulation parameters
    float diffusionConstant;
    float gridSpacing;
    float solverDeltaTime;
    int simFramesPerSecond;
    int maxSteps;
};


class DiffusionExplicit {
    public:
        DiffusionExplicit(DiffusionExplicitConfig config, SDLSystem& sdlSystem);
        ~DiffusionExplicit();

        void run();

        void stop();

        bool hasStopped();


    private:
        DiffusionExplicitConfig config;
        SDLSystem& sdlSystem;

        EventCallbacks windowEventCallbacks {
            .onClose = [this]() {this->stop();}
        };

        bool stopped = false;

        std::vector<float> prevStepConcentrationGrid;

        Window window;
        
        FixedTimer timer;

        int getIndex(int x, int y);

        int currentTimeStep;

        std::vector<float> r2;

        std::ofstream csv;
};

#endif