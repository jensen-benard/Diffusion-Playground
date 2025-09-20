#include "particle.h"
#include <algorithm>


void Particle::updatePos(float posX, float posY) {

    // CHANGE remove clamps and make function inline
    this->posX = std::clamp(posX, minX+1, maxX-1);
    this->posY = std::clamp(posY, minY+1, maxY-1);
}