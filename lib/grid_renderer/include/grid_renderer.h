#ifndef GRID_RENDERER_H
#define GRID_RENDERER_H


class Window;
class Grid;
class CameraState;

enum SamplingMode {
    LINEAR,
    NEAREST
};

class GridRenderer {
    public:
        GridRenderer(SamplingMode samplingMode) : samplingMode(samplingMode) {};
        ~GridRenderer() = default;

        void render(const Grid& grid, Window& window, const CameraState& cameraState);

    private:
        SamplingMode samplingMode;
};


#endif