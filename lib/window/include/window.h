#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

class Window {
    public:
        Window(int width, int height, int pixelChannels);
        ~Window();

        void attachPixelData(unsigned char* pixelData, int pixelDataSize, int bitsPerChannel, int redMask, int greenMask, int blueMask, int alphaMask);

        void updateEventHandler();
        void updateDisplay();

        bool hasClosed();

        void close();

    private:
        SDL_Window* window;
        SDL_Surface* windowSurface;
        SDL_Surface* dataSurface;

        int width;
        int height;
        int pixelChannels;

        bool closed;
};

#endif