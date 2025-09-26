#include "engine.h"

#include <cstddef>
#include <functional>
#include "window.h"
#include "grid_renderer.h"
#include "simulation_manager.h"
#include "grid.h"
#include "camera.h"
#include "recorder.h"



Engine::Engine(SimulationManager& simulationManager, Window& window, GridRenderer& gridRenderer, Recorder& recorder, CameraState& cameraState) : 
    simulationManager(simulationManager), window(window), gridRenderer(gridRenderer), eventCallbacks(std::make_unique<EventCallbacks>()), 
    cameraState(cameraState), recorder(recorder)
{
    eventCallbacks->onClose = [this](){this->onWindowClose();};

    window.setEventCallbacks(*eventCallbacks);
}


void Engine::run() {
    if (stopped) return;

    simulationManager.update();

    SimulationState simulationState = simulationManager.getState();

    

    window.clearPixels(0, 0, 0, 255);

    gridRenderer.render(simulationState.densityGrid, window, cameraState);

    window.updateDisplay(); 

    if (simulationManager.hasStopped()) {

        stop();
    }
}


