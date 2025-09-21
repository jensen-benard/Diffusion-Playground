#include "timer.h"

using namespace std::chrono;


void FixedTimer::start() {
    lastUpdateTime = steady_clock::now();
}

void FixedTimer::tick() {
    steady_clock::time_point currentTime = steady_clock::now();
    duration<double> timeSinceLastUpdate = currentTime - lastUpdateTime;

    accumulator += timeSinceLastUpdate.count();
    lastUpdateTime = currentTime;
}


bool FixedTimer::isDue() {
    if (accumulator >= timeStep) {
        accumulator -= timeStep;
        return true;
    }
    return false;
}


void VariableTimer::start() {
    lastUpdateTime = steady_clock::now();
}


bool VariableTimer::isDue() {
    steady_clock::time_point currentTime = steady_clock::now();
    duration<double> timeSinceLastUpdate = currentTime - lastUpdateTime;

    if (timeSinceLastUpdate.count() < targetDeltaTime) {
        return false;
    } else {
        lastUpdateTime = currentTime;
        return true;
    }
}