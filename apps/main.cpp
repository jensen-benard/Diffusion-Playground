#include "monte_carlo.h"
#include "diffusion_explicit.h"
#include "sdl_system.h"
#include "window.h"

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


    

    SDLSystem& sdlSystem = SDLSystem::getInstance();
    
    while(!sdlSystem.hasQuit()) {
        sdlSystem.pollEvents();
    }
    return 0;
}