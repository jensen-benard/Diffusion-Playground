#ifndef CAMERA_H
#define CAMERA_H

struct CameraState {
    double centerX;
    double centerY;
    double zoom;
    double offsetX;
    double offsetY;
};

class Camera {
    public:
        Camera(CameraState initialConfig) : config(initialConfig) {};
        ~Camera() = default;

        struct Config {
            double centerX;
            double centerY;
            double zoom;
            double offsetX;
            double offsetY;
        };

        CameraState getConfig() const {
            return config;
        }

        void setConfig(CameraState config) {
            this->config = config;
        }

    private:
        CameraState config;
};

#endif

