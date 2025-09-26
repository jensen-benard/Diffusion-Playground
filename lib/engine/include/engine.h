#ifndef ENGINE_H
#define ENGINE_H

#include <memory>

class Window;
class GridRenderer;
class SimulationManager;
struct EventCallbacks;
struct CameraState;

class Engine {
    public:
        Engine(SimulationManager& simulationManager, Window& window, GridRenderer& gridRenderer, CameraState& cameraConfig);
        ~Engine() {};

        void run();
        bool hasStopped() { return stopped; }
        void stop() { stopped = true; }

        void onWindowClose() { stop(); }
        
    private:
        SimulationManager& simulationManager;
        Window& window;

        CameraState& cameraState;

        GridRenderer& gridRenderer;

        bool stopped = false;

        std::unique_ptr<EventCallbacks> eventCallbacks;

};

#endif