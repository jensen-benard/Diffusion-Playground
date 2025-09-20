#ifndef SDL_SYSTEM_H
#define SDL_SYSTEM_H 

#include<vector>
#include<functional>
#include<SDL2/SDL.h>

class SDLSystem {
    public:
    static SDLSystem& getInstance() {static SDLSystem instance; return instance;}

    SDLSystem(SDLSystem const&) = delete;
    void operator=(SDLSystem const&) = delete;
    SDLSystem(SDLSystem&&) = delete;
    void operator=(SDLSystem&&) = delete;

    void pollEvents();

    void registerEventCallback(const std::function<void(SDL_Event&)>& callback, unsigned int callbackId) { callbacks[callbackId] = callback; callbackId++;};
    void unregisterEventCallback(int callbackId) { callbacks.erase(callbackId); };

    void quit();

    void delay(int ms) {SDL_Delay(ms);};

    bool hasQuit() {return quitted;}
    
    private:
        SDLSystem();
        ~SDLSystem();

        bool quitted;

        std::unordered_map<unsigned int, std::function<void(SDL_Event&)>> callbacks;
};

#endif