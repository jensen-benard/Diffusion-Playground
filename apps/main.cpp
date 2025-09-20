#include<SDL2/SDL.h>
#include<iostream>
#include<cstdlib>
#include<fstream>
#include<filesystem>
#include<string>
#include "particle.h"
#include "window.h"
#include <vector>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;
const int CHANNELS = 4;
unsigned char* data = new unsigned char[SCREEN_WIDTH * SCREEN_HEIGHT * CHANNELS];


const int TOTAL_PARTICLES = 100000;
std::vector<Particle> particles(TOTAL_PARTICLES, Particle(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0, SCREEN_WIDTH - 1, 0, SCREEN_HEIGHT - 1));
int* alphaCount = new int[SCREEN_WIDTH * SCREEN_HEIGHT];
const float MAX_ALPHA_COUNT = 100;

const int stepSize = 5;

const float FPS = 60.0f;
const int TIME_STEPS = 1000;
float* r2 = new float[TIME_STEPS];

int currentTimeStep = 0; // first timestep
int originX = static_cast<int>(SCREEN_WIDTH / 2);
int originY = static_cast<int>(SCREEN_HEIGHT / 2);

Window window(SCREEN_WIDTH, SCREEN_HEIGHT, CHANNELS);


int main(int argc, char* args[]) {

    // init particles
    for (int i = 0; i < TOTAL_PARTICLES; i++) {
        particles[i].updatePos(originX, originY);
    }

    std::filesystem::create_directories("output");
    std::ofstream csv("output/r2.csv");
    csv << "timeStep,r2,deltaT\n"; // head row

    window.attachPixelData(data, SCREEN_WIDTH * SCREEN_HEIGHT * CHANNELS, 8, 0X00FF0000, 0X0000FF00, 0X000000FF, 0XFF000000);

    // Set white background.
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            int index = (y * SCREEN_WIDTH + x) * CHANNELS;
            data[index + 0] = 255; // B
            data[index + 1] = 255; // G
            data[index + 2] = 255; // R
            data[index + 3] = 255; // A
            alphaCount[y * SCREEN_WIDTH + x] = 0;
        }
    }

    while (!window.hasClosed() && currentTimeStep < TIME_STEPS) { 
        // Particles and pixels update
        for (int i = 0; i < TOTAL_PARTICLES; i++) {
            float dX = (static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f) * stepSize;
            float dY = (static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f) * stepSize;

            particles[i].updatePos(particles[i].getPosX() + dX, particles[i].getPosY() + dY);
            
            int particlePosX = static_cast<int>(particles[i].getPosX());
            int particlePosY = static_cast<int>(particles[i].getPosY());
            int index = (particlePosY * SCREEN_WIDTH + particlePosX) * CHANNELS;

            if(alphaCount[index / CHANNELS] < MAX_ALPHA_COUNT) {
                alphaCount[index / CHANNELS]+=1;
            }
            
            float factor = alphaCount[index / CHANNELS] / MAX_ALPHA_COUNT;

            data[index + 0] = static_cast<unsigned char>(255 * (1.0f - factor)); // B
            data[index + 1] = static_cast<unsigned char>(255 * (1.0f - factor)); // G
            data[index + 2] = 255; // R
            data[index + 3] = 255; // A
            
            // Calculating r2
            r2[currentTimeStep] += (particlePosX - originX) * (particlePosX - originX) + (particlePosY - originY) * (particlePosY - originY);
        }

        r2[currentTimeStep] /= TOTAL_PARTICLES;

        csv << currentTimeStep << "," << r2[currentTimeStep] << "," << 1.0f / FPS << "\n";

        window.updateEventHandler();

        window.updateDisplay();

        SDL_Delay(1/FPS * 1000);
        currentTimeStep++;
        //std::cout << "Current time step: " << currentTimeStep << "\n";
        
    }

    csv.close();

    delete[] data;
    delete[] alphaCount;
    delete[] r2;

    return 0;
}
