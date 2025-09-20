#include "monte_carlo.h"
#include <random>
#include <algorithm>

MonteCarlo::MonteCarlo(MonteCarloConfig config, SDLSystem& sdlSystem) : config(config), sdlSystem(sdlSystem), window(config.windowConfig, sdlSystem), stopped(false), lastSimUpdate(std::chrono::high_resolution_clock::now()), alphaCount(256, 0)
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
}

void MonteCarlo::run() {
    if (stopped) {
        return;
    }

    // CHANGE create timer class
    std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
    if (currentTime - lastSimUpdate >= std::chrono::duration<float>(1.0f / config.simFramesPerSecond)) {
        lastSimUpdate = currentTime;
        
        for (int i = 0; i < config.totalParticles; i++) {
            float dX = (static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f) * config.stepSize;
            float dY = (static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f) * config.stepSize;

            particles[i].updatePos(particles[i].getPosX() + dX, particles[i].getPosY() + dY);
            
            int index = std::clamp((int)(particles[i].getPosY()), 0, config.windowConfig.height - 1) * config.windowConfig.width + std::clamp((int)particles[i].getPosX(), 0, config.windowConfig.width - 1);
            alphaCount[index]++;

            int factor = (float)alphaCount[index] / MAX_ALPHA_COUNT * 255; 
            if (factor > 255) {
                factor = 255;
            }

            char red = 255;
            char green = 0xff - factor;
            char blue = 0xff - factor;

            window.updatePixel(particles[i].getPosX(), particles[i].getPosY(), red, green, blue, 0xff);
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
    window.close();
}