#include<SDL2/SDL.h>
#include<iostream>
#include<cstdlib>
#include<fstream>
#include<filesystem>
#include<string>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;
const int CHANNELS = 4;
unsigned char* data = new unsigned char[SCREEN_WIDTH * SCREEN_HEIGHT * CHANNELS];

SDL_Surface* dataSurface = nullptr;


class Particle {
    public:
        Particle() {x = 0; y = 0;}
        Particle(int x, int y) : x(x), y(y) {}
        void update(int x, int y) { this->x = x; this->y = y;  if (x < 0) this->x = 0; if (x >= SCREEN_WIDTH) this->x = SCREEN_WIDTH - 1; if (y < 0) this->y = 0; if (y >= SCREEN_HEIGHT) this->y = SCREEN_HEIGHT - 1;}
        int x, y;
};

const int TOTAL_PARTICLES = 100000;
Particle* particles = new Particle[TOTAL_PARTICLES];
int* alphaCount = new int[SCREEN_WIDTH * SCREEN_HEIGHT];
const float MAX_ALPHA_COUNT = 100;

const int stepSize = 5;

const float FPS = 60.0f;
const int TIME_STEPS = 1000;
float* r2 = new float[TIME_STEPS];

int currentTimeStep = 0; // first timestep
int originX = static_cast<int>(SCREEN_WIDTH / 2);
int originY = static_cast<int>(SCREEN_HEIGHT / 2);


int main(int argc, char* args[]) {

    // init particles
    for (int i = 0; i < TOTAL_PARTICLES; i++) {
        particles[i].update(originX, originY);
    }

    std::filesystem::create_directories("output");
    std::ofstream csv("output/r2.csv");
    csv << "timeStep,r2,deltaT\n"; // head row

    SDL_Window* window = nullptr;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return 1;
    }

    window = SDL_CreateWindow( "Gaussian", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

    if( window == nullptr )
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
    } else {
            //Get window surface
            SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
            dataSurface = SDL_CreateRGBSurfaceFrom(data, SCREEN_WIDTH, SCREEN_HEIGHT, CHANNELS * 8, SCREEN_WIDTH * CHANNELS, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
            
            if (dataSurface == nullptr) {
                std::cout << "Surface could not be created! SDL_Error: " << SDL_GetError() << "\n";
            }

            //Hack to get window to stay up
            SDL_Event e; 
            bool quit = false; 

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
            while(!quit && currentTimeStep < TIME_STEPS)
            { 
                // Particles and pixels update
                for (int i = 0; i < TOTAL_PARTICLES; i++) {
                    int dX = (static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f) * stepSize;
                    int dY = (static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f) * stepSize;
                    particles[i].update(particles[i].x + dX, particles[i].y + dY);
                    int index = (particles[i].y * SCREEN_WIDTH + particles[i].x) * CHANNELS;

                    if(alphaCount[index / CHANNELS] < MAX_ALPHA_COUNT) {
                        alphaCount[index / CHANNELS]+=1;
                    }
                    
                    float factor = alphaCount[index / CHANNELS] / MAX_ALPHA_COUNT;

                    data[index + 0] = static_cast<unsigned char>(255 * (1.0f - factor)); // B
                    data[index + 1] = static_cast<unsigned char>(255 * (1.0f - factor)); // G
                    data[index + 2] = 255; // R
                    data[index + 3] = 255; // A
                    
                    // Calculating r2
                    r2[currentTimeStep] += (particles[i].x - originX) * (particles[i].x - originX) + (particles[i].y - originY) * (particles[i].y - originY);
                }

                r2[currentTimeStep] /= TOTAL_PARTICLES;

                csv << currentTimeStep << "," << r2[currentTimeStep] << "," << 1.0f / FPS << "\n";

                SDL_BlitSurface(dataSurface, NULL, screenSurface, NULL);
                SDL_UpdateWindowSurface(window);

                SDL_PollEvent(&e);
                if(e.type == SDL_QUIT) { 
                    quit = true;
                } 

                SDL_Delay(1/FPS * 1000);
                currentTimeStep++;
                std::cout << "Current time step: " << currentTimeStep << "\n";
                
            }
    }

    csv.close();

    delete[] particles;
    delete[] data;
    delete[] alphaCount;
    delete[] r2;

    SDL_FreeSurface(dataSurface);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
