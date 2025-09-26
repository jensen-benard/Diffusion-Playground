#include "sdl_system.h"
#include "window.h"
#include "discrete_random_walk_solver.h"
#include "solver.h"
#include "simulation_controller.h"
#include <cstddef>


int main(int argc, char* args[]) {

    SDLSystem& sdlSystem = SDLSystem::getInstance();


    WindowConfig windowConfig = {
        .width = 1200,
        .height = 800,
        .framesPerSecond = 60,
        .channelsPerPixel = 4,
        .bitsPerChannel = 8,
        .channelDepthPerPixel = 32,
        .pixelMapPitch = 0,
        .redMask = 0x00ff0000,
        .greenMask = 0x0000ff00,
        .blueMask = 0x000000ff,
        .alphaMask = 0xff000000
    };

    windowConfig.pixelMapPitch = windowConfig.width * windowConfig.channelsPerPixel;

    Window window(windowConfig, sdlSystem);

    WalkerInitialCondition walkerInitialCondition = {
        .posX = static_cast<double>(windowConfig.width / 2),
        .posY = static_cast<double>(windowConfig.height / 2),
        .count = 1000
    };

    DiscreteRandomWalkSolverConfig monteCarloDiffusionConfig = {
        .walkerInitialConditions = {walkerInitialCondition},
        .walkerStepSize = 1.0f,
        .maxSteps = 1000,
        .solverWidth = static_cast<double>(windowConfig.width),
        .solverHeight = static_cast<double>(windowConfig.height),
        .densityGridWidth = static_cast<size_t>(windowConfig.width),
        .densityGridHeight = static_cast<size_t>(windowConfig.height),
        .randomNumberGeneratorSeed = 42
    };

    DiscreteRandomWalkSolver discreteRandomWalkSolver(monteCarloDiffusionConfig);

    SimulationConfig simulationConfig = {
        .stepsPerSecond = 60,
    };

    SimulationController simulationController(window, discreteRandomWalkSolver, simulationConfig);
    
    while(!sdlSystem.hasQuit()) {
        sdlSystem.pollEvents();
        simulationController.run();
    }
    return 0;
}