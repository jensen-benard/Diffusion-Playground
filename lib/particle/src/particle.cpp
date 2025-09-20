#include "particle.h"


void Particle::updatePos(float posX, float posY) {
    this->posX = posX;
    this->posY = posY;

    if (posX < minX) this->posX = minX;
    if (posX > maxX) this->posX = maxX;
    if (posY < minY) this->posY = minY;
    if (posY > maxY) this->posY = maxY;
}