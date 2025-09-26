#include "sdl_system.h"
#include "window.h"
#include "discrete_random_walk_solver.h"
#include "finite_difference_solver.h"
#include "solver.h"
#include "engine.h"
#include <cstddef>
#include "simulation_manager.h"
#include "grid_renderer.h"
#include "camera.h"


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

    WalkerInitialCondition walkerInitialCondition1 = {
        .posX = static_cast<double>(windowConfig.width / 2),
        .posY = static_cast<double>(windowConfig.height / 2),
        .count = 1000
    };

    WalkerInitialCondition walkerInitialCondition2 = {
        .posX = static_cast<double>((windowConfig.width+50) / 2),
        .posY = static_cast<double>((windowConfig.height+50) / 2),
        .count = 1000
    };

    DiscreteRandomWalkSolverConfig monteCarloDiffusionConfig = {
        .walkerInitialConditions = {walkerInitialCondition2},
        .walkerStepSize = 1.0f,
        .maxSteps = 1000,
        .solverWidth = static_cast<double>(windowConfig.width),
        .solverHeight = static_cast<double>(windowConfig.height),
        .densityGridWidth = static_cast<size_t>(windowConfig.width),
        .densityGridHeight = static_cast<size_t>(windowConfig.height),
        .randomNumberGeneratorSeed = 1
    };

    DiscreteRandomWalkSolver discreteRandomWalkSolver(monteCarloDiffusionConfig);

    FiniteDifferenceSolverConfig config = {
        .diffusionConstant = 100.0,
        .gridSpacing = 4,
        .deltaTime = 0.01,
        .maxSteps = 1000,
        .solverWidth = static_cast<double>(windowConfig.width),
        .solverHeight = static_cast<double>(windowConfig.height),
        .densityGridWidth = static_cast<size_t>(windowConfig.width),
        .densityGridHeight = static_cast<size_t>(windowConfig.height)
    };

    FiniteDifferenceSolver finiteDifferenceSolver(config);

    SimulationConfig simulationConfig = {
        .stepsPerSecond = 60,
    };

    SimulationManager simulationManager1(finiteDifferenceSolver, simulationConfig);
    SimulationManager simulationManager2(discreteRandomWalkSolver, simulationConfig);

    GridRenderer gridRenderer(SamplingMode::NEAREST);

    CameraState cameraState = {
        .centerX = static_cast<double>(windowConfig.width / 2),
        .centerY = static_cast<double>(windowConfig.height / 2),
        .zoom = 10.0,
        .offsetX = 0.0,
        .offsetY = 0.0
    };


    Engine engine1(simulationManager1, window, gridRenderer, cameraState);
    Engine engine2(simulationManager2, window, gridRenderer, cameraState);
    
    while(!sdlSystem.hasQuit()) {
        sdlSystem.pollEvents();
        engine1.run();
        //engine2.run();
    }
    return 0;
}