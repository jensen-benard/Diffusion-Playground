#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

#include <vector>
#include "particle.h"
#include "window.h"
#include "sdl_system.h"
#include "timer.h"
#include <fstream>

struct MonteCarloConfig {
    // Window parameters
    WindowConfig windowConfig;

    // Particle parameters
    int originX;
    int originY;
    int totalParticles;

    // Simulation parameters 
    int simStepsPerSecond;
    int particleStepSize;
    int maxSteps;
    bool recordMeanSquaredDisplacement;
};


class MonteCarlo {
    public:
        MonteCarlo(MonteCarloConfig config, SDLSystem& sdlSystem);
        ~MonteCarlo();

        void run();
        
        bool hasStopped();

        void stop();


    private:
        Window window;
        std::vector<unsigned char> pixelData;

        std::vector<Particle> particles;
    
        MonteCarloConfig config;

        SDLSystem& sdlSystem;

        EventCallbacks windowEventCallbacks;

        bool stopped;

        std::vector<int> alphaCount;

        int MAX_ALPHA_COUNT = 100; // CHANGE implement into monte carlo config

        FixedTimer timer;
        
        int TIME_STEPS = 1000;
        std::vector<float> r2;
        int currentTimeStep = 0;
        std::ofstream csv;
};


#endif