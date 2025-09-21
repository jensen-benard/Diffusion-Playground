#include "monte_carlo.h"
#include "sdl_system.h"

int main(int argc, char* args[]) {
    MonteCarloConfig config = {
        .windowConfig = {
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
        },
        .originX = config.windowConfig.width / 2,
        .originY = config.windowConfig.height / 2,
        .totalParticles = 10000,
        .simFramesPerSecond = 60,
        .stepSize = 10,
        .maxSteps = 100,
        .recordMeanSquaredDisplacement = false
    };

    config.windowConfig.pixelMapPitch = config.windowConfig.width * config.windowConfig.channelsPerPixel;
    

    SDLSystem& sdlSystem = SDLSystem::getInstance();

    MonteCarlo monteCarlo(config, sdlSystem);
    
    while(!sdlSystem.hasQuit()) {
        sdlSystem.pollEvents();
        monteCarlo.run();
    }
    return 0;
}