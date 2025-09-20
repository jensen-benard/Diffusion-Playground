#ifndef PARTICLE_H
#define PARTICLE_H

class Particle {
    public:
        Particle(float posX, float posY,float minX, float maxX, float minY, float maxY) : posX(posX), posY(posY), minX(minX), maxX(maxX), minY(minY), maxY(maxY) {}

        void updatePos(float posX, float posY);

        float getPosX() {return posX;}
        float getPosY() {return posY;}
        float getMinX() {return minX;}
        float getMaxX() {return maxX;}
        float getMinY() {return minY;}
        float getMaxY() {return maxY;}

    private:
        float posX, posY;
        float minX, maxX, minY, maxY;
};

#endif