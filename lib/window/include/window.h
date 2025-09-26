#ifndef WINDOW_H
#define WINDOW_H

#include "sdl_system.h"
#include <SDL2/SDL.h>
#include <vector>
#include "timer.h"
#include <functional>

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

        void setPixel(int x, int y, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

        void clearPixels(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

        void updateEventHandler(SDL_Event& event);
        void updateDisplay(); 

        void setEventCallbacks(EventCallbacks callbacks) { eventCallbacks = callbacks; }

        int getWidth() { return config.width; }
        int getHeight() { return config.height; }

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

        VariableTimer timer;
};

#endif