#include "../include/Mesh.h"

void Mesh::cubicPoints() {

    double ratioX, ratioY;
    double dimX, dimY;
    double sizeX, sizeY;
    double startX, startY;

    dimX = DIM(1);
    dimY = DIM(2);
    sizeX = SIZE(0);
    sizeY = SIZE(1);
    startX = 0.0;
    startY = 0.0;

    if(this->meshInfo.meshShape.getShape()==TRAPEZIOD){
        ratioX = SIZE(2)*(DIM(1) - DIM(4))/DIM(3);
        ratioY = SIZE(2)*(DIM(2) - DIM(5))/DIM(3);
    }

    for(double stepZ = 0; stepZ <= DIM(3) + EPS; stepZ+= SIZE(2)) {

        for(double stepY = 0; stepY <= dimY + EPS; stepY+= sizeY) {

            for(double stepX = 0; stepX <= dimX + EPS; stepX+= sizeX) {

                this->addPoint(stepX + startX, stepY + startY, stepZ);
            }
        }

        if(this->meshInfo.meshShape.getShape() == TRAPEZIOD){
            dimX-= ratioX;
            dimY-= ratioY;
            sizeX = dimX/(double)NODE(0);
            sizeY = dimY/(double)NODE(1);
            startX = (DIM(1) - dimX)/2.0;
            startY = (DIM(2) - dimY)/2.0;
        }
    }
}
