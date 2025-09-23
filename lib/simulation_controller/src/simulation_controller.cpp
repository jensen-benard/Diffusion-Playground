#include "simulation_controller.h"

#include "grid.h"
#include <cstddef>

using namespace std;

void SimulationController::run() {
    if (hasStopped()) return;

    solver.step();

    // Map density grid to window
    const Grid& densityGrid = solver.getDensityGrid();
    
    double scaleX = static_cast<double>(densityGrid.getWidth()) / static_cast<double>(window.getWidth());
    double scaleY = static_cast<double>(densityGrid.getHeight()) / static_cast<double>(window.getHeight());

    window.clearPixels(0, 0, 0, 255);

    for (size_t y = 0; y < window.getHeight(); y++) {
        for (size_t x = 0; x < window.getWidth(); x++) {
            size_t gridX = std::min(static_cast<size_t>(x / scaleX), densityGrid.getWidth() - 1);
            size_t gridY = std::min(static_cast<size_t>(y / scaleY), densityGrid.getHeight() - 1);

            double density = densityGrid.getValueAtPos(gridX, gridY);

            unsigned char colourIntensity = static_cast<unsigned char>(std::min(1.0, density) * 255);

            window.setPixel(x, y, colourIntensity, 0, 0, 255);
        }
    }

    window.updateDisplay(); 
}

