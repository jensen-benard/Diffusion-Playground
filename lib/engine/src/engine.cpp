#include "engine.h"

#include <cstddef>
#include <functional>
#include "window.h"
#include "grid_renderer.h"
#include "simulation_manager.h"
#include "grid.h"
#include "camera.h"



Engine::Engine(SimulationManager& simulationManager, Window& window, GridRenderer& gridRenderer, CameraState& cameraState) : 
    simulationManager(simulationManager), window(window), gridRenderer(gridRenderer), eventCallbacks(std::make_unique<EventCallbacks>()), cameraState(cameraState)
{
    eventCallbacks->onClose = [this](){this->onWindowClose();};

    window.setEventCallbacks(*eventCallbacks);
}


void Engine::run() {
    if (hasStopped()) return;

    simulationManager.update();

    // Map density grid to window
    SimulationState simulationState = simulationManager.getState();

    window.clearPixels(0, 0, 0, 255);

    gridRenderer.render(simulationState.densityGrid, window, cameraState);

    window.updateDisplay(); 

    if (simulationManager.hasStopped()) {
        stop();
    }
}


