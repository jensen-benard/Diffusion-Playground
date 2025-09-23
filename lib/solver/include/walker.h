#ifndef WALKER_H
#define WALKER_H

class Walker {
    public:
        Walker(double posX, double posY) : posX(posX), posY(posY), originX(posX), originY(posY){}

        void setPos(double posX, double posY ) {this->posX = posX; this->posY = posY;}
        void setOrigin(double originX, double originY) {this->originX = originX; this->originY = originY;}

        double getPosX() {return posX;}
        double getPosY() {return posY;}
        double getOriginX() {return originX;}
        double getOriginY() {return originY;}

    private:
        double posX, posY;
        double originX, originY;
};

#endif