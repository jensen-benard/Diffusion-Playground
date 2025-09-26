#include "simulation_controller.h"

#include "grid.h"
#include <cstddef>
#include <functional>

using namespace std;


SimulationController::SimulationController(Window& window, Solver& solver, SimulationConfig config) : window(window), solver(solver), config(config) 
{
    eventCallbacks.onClose = [this](){this->onWindowClose();};

    window.setEventCallbacks(eventCallbacks);
}


void SimulationController::run() {
    if (hasStopped()) return;

    solver.step();

    //zooming 
    double zoom = 1;        // 1.0 = no zoom, >1.0 = zoom in, <1.0 = zoom out
    double offsetX = 0.0;     // grid-space offset
    double offsetY = 0.0;
    double winCenterX = window.getWidth()  / 2.0;
    double winCenterY = window.getHeight() / 2.0;

    // Map density grid to window
    const Grid& densityGrid = solver.getDensityGrid();
    
    double scaleX = static_cast<double>(densityGrid.getWidth()) / static_cast<double>(window.getWidth());
    double scaleY = static_cast<double>(densityGrid.getHeight()) / static_cast<double>(window.getHeight());

    window.clearPixels(0, 0, 0, 255);

    for (size_t y = 0; y < window.getHeight(); y++) {
        for (size_t x = 0; x < window.getWidth(); x++) {
            // size_t gridX = std::min(static_cast<size_t>(x / scaleX), densityGrid.getWidth() - 1);
            // size_t gridY = std::min(static_cast<size_t>(y / scaleY), densityGrid.getHeight() - 1);

            // zooming and panning
            double gridXf = ((x - winCenterX) / (scaleX * zoom)) + offsetX + winCenterX / scaleX;
            double gridYf = ((y - winCenterY) / (scaleY * zoom)) + offsetY + winCenterY / scaleY;

            size_t gridX = std::min(static_cast<size_t>(gridXf), densityGrid.getWidth() - 1);
            size_t gridY = std::min(static_cast<size_t>(gridYf), densityGrid.getHeight() - 1);


            double density = densityGrid.getValueAtPos(gridX, gridY) / 5;

            unsigned char colourIntensity = static_cast<unsigned char>(std::min(1.0, density) * 255);

            window.setPixel(x, y, colourIntensity, 0, 0, 255);
        }
    }

    window.updateDisplay(); 

    if (solver.isMaxStepReached()) {
        stop();
    }
}


