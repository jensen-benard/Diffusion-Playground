#include "window.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include "timer.h"
#include "sdl_system.h"

Window::Window(WindowConfig config, SDLSystem& sdlSystem) : 
    window(nullptr), config(config), sdlSystem(sdlSystem), 
    windowSurface(nullptr), closed(false), pixelMapSurface(nullptr), 
    timer(std::make_unique<VariableTimer>(1.0f / config.framesPerSecond))
{
    window = SDL_CreateWindow("Diffusion Playground", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, config.width, config.height, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        throw std::runtime_error(std::string("Window could not be created! SDL_Error: ") + SDL_GetError());
    }

    windowSurface = SDL_GetWindowSurface(window);

    if (windowSurface == nullptr) {
        throw std::runtime_error(std::string("Window surface could not be created! SDL_Error: ") + SDL_GetError());
    }

    pixelMap.resize(config.width * config.height * config.channelsPerPixel);

    pixelMapSurface = SDL_CreateRGBSurfaceFrom(pixelMap.data(), config.width, config.height, config.channelDepthPerPixel, config.pixelMapPitch, config.redMask, config.greenMask, config.blueMask, config.alphaMask);
    
    if (pixelMapSurface == nullptr) {
        throw std::runtime_error(std::string("Data surface could not be created! SDL_Error: ") + SDL_GetError());
    }

    sdlSystem.registerEventCallback([this](SDL_Event& event) {
        this->updateEventHandler(event);
    }, SDL_GetWindowID(window));

    timer->start();
}

Window::~Window() {
    close();
}

void Window::setPixel(int x, int y, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {

    if (x < 0 || x >= config.width || y < 0 || y >= config.height) {
        throw std::runtime_error(std::string("Pixel out of bounds! X: ") + std::to_string(x) + ", Y: " + std::to_string(y));
    }

    int index = (y * config.width + x) * config.channelsPerPixel;
    pixelMap[index + 0] = blue;
    pixelMap[index + 1] = green;
    pixelMap[index + 2] = red;
    pixelMap[index + 3] = alpha;
}


void Window::updateEventHandler(SDL_Event& event) {
    if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
        eventCallbacks.onClose();
        close();
    }
}

void Window::clearPixels(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {
    for(int y = 0; y < config.height; y++) {
        for(int x = 0; x < config.width; x++) {
            setPixel(x, y, red, green, blue, alpha);
        }
    }
}

void Window::updateDisplay() {

    if (timer->isDue()) {
        SDL_BlitSurface(pixelMapSurface, nullptr, windowSurface, nullptr);
        SDL_UpdateWindowSurface(window);
    }
}


bool Window::hasClosed() {
    return closed;
}


void Window::close() {
    
    if (closed) {
        return;
    }

    sdlSystem.unregisterEventCallback(SDL_GetWindowID(window));

    SDL_FreeSurface(pixelMapSurface);
    SDL_DestroyWindow(window);

    closed = true;
}