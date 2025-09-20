#include "window.h"
#include <iostream>
#include <stdexcept>
#include <string>

Window::Window(int width, int height, int pixelChannels) : window(nullptr), width(width), height(height), pixelChannels(pixelChannels)
{
    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        throw std::runtime_error(std::string("SDL could not initialize! SDL_Error: ") + SDL_GetError());
    }

    window = SDL_CreateWindow("Diffusion Playground", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        throw std::runtime_error(std::string("Window could not be created! SDL_Error: ") + SDL_GetError());
    }

    windowSurface = SDL_GetWindowSurface(window);

    if (windowSurface == nullptr) {
        throw std::runtime_error(std::string("Window surface could not be created! SDL_Error: ") + SDL_GetError());
    }
}

Window::~Window() {
    close();
}

void Window::attachPixelData(unsigned char* pixelData, int pixelDataSize, int bitsPerChannel, int redMask, int greenMask, int blueMask, int alphaMask) {

    if (pixelData == nullptr) {
        throw std::runtime_error("Pixel data is null!");
    }

    if (pixelDataSize != width * height * pixelChannels) {
        throw std::runtime_error("Pixel data size does not match window size!");
    }

    int pixelChannelDepth = pixelChannels * bitsPerChannel;
    int pitch = pixelChannels * width;

    dataSurface = SDL_CreateRGBSurfaceFrom(pixelData, width, height, pixelChannelDepth, pitch, redMask, greenMask, blueMask, alphaMask);

    if (dataSurface == nullptr) {
        throw std::runtime_error(std::string("Data surface could not be created! SDL_Error: ") + SDL_GetError());
    }
}


void Window::updateEventHandler() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            close();
        }
    }
}

void Window::updateDisplay() {
    SDL_BlitSurface(dataSurface, nullptr, windowSurface, nullptr);
    SDL_UpdateWindowSurface(window);
}


bool Window::hasClosed() {
    return closed;
}


void Window::close() {
    closed = true;
    
    SDL_FreeSurface(dataSurface);
    SDL_DestroyWindow(window);
    SDL_Quit();
}