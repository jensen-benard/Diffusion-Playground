#include "grid_renderer.h"
#include <cstddef>
#include "grid.h"
#include "window.h"
#include "camera.h"

using std::size_t;
using std::min;

void GridRenderer::render(const Grid& grid, Window& window, const CameraState& cameraConfig)
{
    double scaleX = static_cast<double>(grid.getWidth()) / static_cast<double>(window.getWidth());
    double scaleY = static_cast<double>(grid.getHeight()) / static_cast<double>(window.getHeight());

    for (size_t pixelPosY = 0; pixelPosY < window.getHeight(); pixelPosY++) {
        for (size_t pixelPosX = 0; pixelPosX < window.getWidth(); pixelPosX++) {

            // zooming and panning
            double gridXd = ((pixelPosX - cameraConfig.centerX) / (scaleX * cameraConfig.zoom)) + cameraConfig.offsetX + cameraConfig.centerX / scaleX;
            double gridYd = ((pixelPosY - cameraConfig.centerY) / (scaleY * cameraConfig.zoom)) + cameraConfig.offsetY + cameraConfig.centerY / scaleY;

            size_t gridX = min(static_cast<size_t>(gridXd), grid.getWidth() - 1);
            size_t gridY = min(static_cast<size_t>(gridYd), grid.getHeight() - 1);


            double density = grid.getValueAtPos(gridX, gridY) / 5;

            unsigned char colourIntensity = static_cast<unsigned char>(std::min(1.0, density) * 255);

            window.setPixel(pixelPosX, pixelPosY, colourIntensity, 0, 0, 255);
        }
    }
}