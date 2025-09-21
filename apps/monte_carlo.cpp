#include "monte_carlo.h"
#include <random>
#include <algorithm>
#include <filesystem>
#include <iostream>

MonteCarlo::MonteCarlo(MonteCarloConfig config, SDLSystem& sdlSystem) : config(config), sdlSystem(sdlSystem), window(config.windowConfig, sdlSystem), timer(1.0f / config.simStepsPerSecond), stopped(false), alphaCount(256, 0), r2(TIME_STEPS, 0.0f)
{   
    // init particles
    for(int i = 0; i < config.totalParticles; i++) {
        particles.push_back(Particle(config.originX, config.originY, 0, config.windowConfig.width, 0, config.windowConfig.height));
    }

    window.clearDisplay(0xff, 0xff, 0xff, 0xff);

    EventCallbacks windowEventCallbacks {
        .onClose = [this]() {this->stop();}
    };

    window.setEventCallbacks(windowEventCallbacks);

    alphaCount = std::vector<int>(config.windowConfig.width * config.windowConfig.height, 0);

    timer.start();

    std::filesystem::create_directories("output");
    csv = std::ofstream("output/r2.csv");
    csv << "timeStep,r2\n"; // head row
}

void MonteCarlo::run() {
    if (stopped) {
        return;
    }

    // CHANGE create timer class
    timer.tick();
    if (timer.isDue()) {
        
        for (int i = 0; i < config.totalParticles; i++) {
            float dX = (static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f) * config.particleStepSize;
            float dY = (static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f) * config.particleStepSize;

            particles[i].updatePos(particles[i].getPosX() + dX, particles[i].getPosY() + dY);
            
            
            int index = std::clamp((int)(particles[i].getPosY()), 0, config.windowConfig.height - 1) * config.windowConfig.width + std::clamp((int)particles[i].getPosX(), 0, config.windowConfig.width - 1);
            alphaCount[index]++;

            int factor = (float)alphaCount[index] / MAX_ALPHA_COUNT * 255; 
            if (factor > 255) {
                factor = 255;
            }
            
            // Calculating r2
            int particlePosX = static_cast<int>(particles[i].getPosX());
            int particlePosY = static_cast<int>(particles[i].getPosY());
            r2[currentTimeStep] += (particlePosX - config.originX) * (particlePosX - config.originX) + (particlePosY - config.originY) * (particlePosY - config.originY);


            char red = 255;
            char green = 0xff - factor;
            char blue = 0xff - factor;

            window.updatePixel(particles[i].getPosX(), particles[i].getPosY(), red, green, blue, 0xff);
        }

        r2[currentTimeStep] = r2[currentTimeStep] / config.totalParticles;
        csv << currentTimeStep << "," << r2[currentTimeStep] << "\n";
        currentTimeStep++;

        if (currentTimeStep >= TIME_STEPS) {
            std::cout << "Simulation stopped" << std::endl;
            this->stop();
        }
    }

    window.updateDisplay();
}

void MonteCarlo::stop() {
    stopped = true;
}

bool MonteCarlo::hasStopped() {
    return stopped;
}

MonteCarlo::~MonteCarlo() {
    csv.close();
    window.close();
}