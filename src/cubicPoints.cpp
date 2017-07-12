#include "../include/Mesh.h"

void Mesh::cubicPoints() {

    double ratioX, ratioY, sizeX, sizeY, dimX, dimY, dimZ;
    double startX, startY, startZ;
    arrDouble dim, sizem;
    arrUnsgn cellNums = this->shape.getCellNumbersOfLayer(1);

    startX = 0.0;
    startY = 0.0;
    startZ = 0.0;

    for(unsigned layer = 1; layer <= this->shape.getNumberOfLayers(); layer++) {
        dim = this->shape.getDimsOfLayer(layer);
        sizem = this->shape.getSizesOfLayer(layer);
        dimX = dim[0];
        dimY = dim[1];
        dimZ = dim[2] - sizem[2];
        sizeX = sizem[0];
        sizeY = sizem[1];

        if(this->shape.getShape()==TRAPEZIOD){
            ratioX = sizem[0]*(dim[0] - dim[3])/dim[2];
            ratioY = sizem[1]*(dim[1] - dim[4])/dim[2];
        }

        for(double stepZ = 0; stepZ <= dimZ + EPS; stepZ+= sizem[2]) {

            for(double stepY = 0; stepY <= dimY + EPS; stepY+= sizeY) {

                for(double stepX = 0; stepX <= dimX + EPS; stepX+= sizeX) {

                    this->addPoint(stepX + startX, stepY + startY, stepZ + startZ);
                }
            }

            if(this->shape.getShape() == TRAPEZIOD){
                dimX-= ratioX;
                dimY-= ratioY;
                sizeX = dimX/(double)cellNums[0];
                sizeY = dimY/(double)cellNums[1];
                startX = (dim[0] - dimX)/2.0;
                startY = (dim[1] - dimY)/2.0;
            }
        }

        startX = 0.0;
        startY = 0.0;
        startZ += dim[2];
    }
}
