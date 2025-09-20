#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <vector>
#include "sdl_system.h"
#include <chrono>

struct WindowConfig {
    int width;
    int height;
    int framesPerSecond;
    int channelsPerPixel;
    int bitsPerChannel;
    int channelDepthPerPixel;
    int pixelMapPitch;
    unsigned int redMask;
    unsigned int greenMask;
    unsigned int blueMask;
    unsigned int alphaMask;
};

struct EventCallbacks {
    std::function<void()> onClose;
};


class Window {
    public:
        Window(WindowConfig config, SDLSystem& sdlSystem);
        ~Window();

        void updatePixel(int x, int y, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

        void clearDisplay(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

        void updateEventHandler(SDL_Event& event);
        void updateDisplay(); 

        void setEventCallbacks(EventCallbacks callbacks) { eventCallbacks = callbacks; }

        bool hasClosed();

        void close();

    private:
        SDL_Window* window;
        SDL_Surface* windowSurface;
        SDL_Surface* pixelMapSurface;

        WindowConfig config;

        std::vector<unsigned char> pixelMap;

        SDLSystem& sdlSystem;

        EventCallbacks eventCallbacks;

        bool closed;

        std::chrono::high_resolution_clock::time_point lastUpdate;
};

#endif