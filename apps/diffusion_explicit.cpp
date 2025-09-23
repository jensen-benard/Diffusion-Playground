#include "diffusion_explicit.h"
#include <iostream>
#include <filesystem>

DiffusionExplicit::DiffusionExplicit(DiffusionExplicitConfig config, SDLSystem& sdlSystem) : config(config), sdlSystem(sdlSystem), window(config.windowConfig, sdlSystem), timer(1.0f / config.simFramesPerSecond), stopped(false), prevStepConcentrationGrid((config.windowConfig.width+2) * (config.windowConfig.height+2), 0.0f), currentTimeStep(0), r2(config.maxSteps, 0.0f) {
    window.clearPixels(0xff, 0xff, 0xff, 0xff);

    EventCallbacks windowEventCallbacks {
        .onClose = [this]() {this->stop();}
    };

    window.setEventCallbacks(windowEventCallbacks);

    // Set Dirichlet boundary conditions as 0.0f
    for (int y = 0; y < config.windowConfig.height; y++) {
        int x = 0;
        int index = (y * (config.windowConfig.width + 2) + x);
        prevStepConcentrationGrid[index] = 0.0f;

        x = config.windowConfig.width + 1;
        index = (y * (config.windowConfig.width + 2) + x);
        prevStepConcentrationGrid[index] = 0.0f;
    }

    for (int x = 0; x < config.windowConfig.width; x++) {
        int y = 0;
        int index = (y * (config.windowConfig.width + 2) + x);
        prevStepConcentrationGrid[index] = 0.0f;

        y = config.windowConfig.height + 1;
        index = (y * (config.windowConfig.width + 2) + x);
        prevStepConcentrationGrid[index] = 0.0f;
    }

    // Set initial concentration
    int x = (config.windowConfig.width+2) / 2;
    int y = (config.windowConfig.height+2) / 2;
    int index = (y * (config.windowConfig.width + 2) + x);
    prevStepConcentrationGrid[index] = 1000.0f;

    std::filesystem::create_directories("output");
    csv = std::ofstream("output/r2_explicit.csv");
    csv << "timeStep,r2\n"; // head row

    timer.start();
}


DiffusionExplicit::~DiffusionExplicit() {
    window.close();
}

int DiffusionExplicit::getIndex(int x, int y) {
    return y * (config.windowConfig.width + 2) + x;
}


void DiffusionExplicit::run() {
    if (stopped) {
        return;
    }

    timer.tick();
    if (timer.isDue()) {
        window.clearPixels(0xff, 0xff, 0xff, 0xff);

        std::vector<float> currStepConcentrationGrid = prevStepConcentrationGrid;

        float sum_concentration = 0.0f;

        for (int y = 1; y < config.windowConfig.height; y++) {
            for (int x = 1; x < config.windowConfig.width; x++) {
                float cLeft = prevStepConcentrationGrid[getIndex(x - 1, y)];
                float cRight = prevStepConcentrationGrid[getIndex(x + 1, y)];
                float cUp = prevStepConcentrationGrid[getIndex(x, y - 1)];
                float cDown = prevStepConcentrationGrid[getIndex(x, y + 1)];
                float cCenter = prevStepConcentrationGrid[getIndex(x, y)];
                float laplacian = (cLeft + cRight + cUp + cDown - 4.0f * cCenter) / (config.gridSpacing * config.gridSpacing);
                
                currStepConcentrationGrid[getIndex(x, y)] = cCenter + config.diffusionConstant * laplacian * config.solverDeltaTime;
                float value = currStepConcentrationGrid[getIndex(x, y)];
                float mapped = pow(value/1000.0f, 0.03f); // square root stretches out low values
                uint8_t color = static_cast<uint8_t>(255 * mapped);
                window.setPixel(x, y, 0x00, color, 0x00, 0xff);
                
                // Calculate r2
                float originX = (config.windowConfig.width+2) / 2.0f;
                float originY = (config.windowConfig.height+2) / 2.0f;
                float r2_displacement = (x - originX) * (x - originX) + (y - originY) * (y - originY);
                r2[currentTimeStep] += cCenter * r2_displacement;
                sum_concentration += cCenter;
            }
        }

        r2[currentTimeStep] /= sum_concentration;

        prevStepConcentrationGrid = currStepConcentrationGrid;

        csv << currentTimeStep << "," << r2[currentTimeStep] << "\n";

        if (currentTimeStep < config.maxSteps-1) {
            currentTimeStep++;
        } else {
            std::cout << "Max steps reached!" << std::endl;
            stopped = true;
        }
    }

    window.updateDisplay();
}

bool DiffusionExplicit::hasStopped() {
    return stopped;
}

void DiffusionExplicit::stop() {
    stopped = true;
}