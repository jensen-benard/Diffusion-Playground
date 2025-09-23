#include "monte_carlo.h"
#include "diffusion_explicit.h"
#include "sdl_system.h"

int main(int argc, char* args[]) {

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

    MonteCarloConfig config = {
        .windowConfig = windowConfig,
        .originX = config.windowConfig.width / 2,
        .originY = config.windowConfig.height / 2,
        .totalParticles = 10000,
        .simStepsPerSecond = 60,
        .particleStepSize = 10,
        .maxSteps = 100,
        .recordMeanSquaredDisplacement = false
    };

    DiffusionExplicitConfig diffusionExplicitConfig = {
        .windowConfig = windowConfig,
        .diffusionConstant = 100.0f,
        .gridSpacing = 4.0f,
        .solverDeltaTime = 0.01f,
        .simFramesPerSecond = 60,
        .maxSteps = 1000,
    };


    

    SDLSystem& sdlSystem = SDLSystem::getInstance();

    //MonteCarlo monteCarlo(config, sdlSystem);

    DiffusionExplicit diffusionExplicit(diffusionExplicitConfig, sdlSystem);
    
    while(!sdlSystem.hasQuit()) {
        sdlSystem.pollEvents();
        //monteCarlo.run();
        diffusionExplicit.run();
    }
    return 0;
}