#include "sdl_system.h"
#include <stdexcept>
#include <string>
#include <iostream>

SDLSystem::SDLSystem() : quitted(false)
{
    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        throw std::runtime_error(std::string("SDL could not initialize! SDL_Error: ") + SDL_GetError());
    }
}

SDLSystem::~SDLSystem() {
    quit();
}

static std::string eventTypeToString(SDL_Event& e) {
    switch(e.type) {
        case SDL_QUIT: return "SDL_QUIT";
        case SDL_WINDOWEVENT:
            switch(e.window.event) {
                case SDL_WINDOWEVENT_CLOSE: return "SDL_WINDOWEVENT_CLOSE";
                case SDL_WINDOWEVENT_RESIZED: return "SDL_WINDOWEVENT_RESIZED";
                default: return "SDL_WINDOWEVENT_OTHER";
            }
        case SDL_KEYDOWN: return "SDL_KEYDOWN";
        case SDL_KEYUP: return "SDL_KEYUP";
        case SDL_MOUSEBUTTONDOWN: return "SDL_MOUSEBUTTONDOWN";
        case SDL_MOUSEBUTTONUP: return "SDL_MOUSEBUTTONUP";
        case SDL_MOUSEMOTION: return "SDL_MOUSEMOTION";
        case SDL_MOUSEWHEEL: return "SDL_MOUSEWHEEL";
        default: return "UNKNOWN_EVENT";
    }
}


void SDLSystem::pollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {

        if (event.type == SDL_QUIT) {
            quit();
        }

        if (callbacks.find(event.window.windowID) == callbacks.end()) {
            continue;
        }

        callbacks[event.window.windowID](event);
    }
}


void SDLSystem::quit() {

    if (quitted) {
        return;
    }

    for (auto [id, callback] : callbacks) {
        SDL_Event quitEvent;
        quitEvent.type = SDL_QUIT;
        callback(quitEvent);
        unregisterEventCallback(id);
    }

    SDL_Quit();

    quitted = true;
}