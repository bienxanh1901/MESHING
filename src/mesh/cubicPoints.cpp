#include "../../include/Mesh.h"

void Mesh::cubicPoints() {

    double ratioX, ratioY, sizeX, sizeY, dimX, dimY, dimZ,
           startX = 0.0, startY = 0.0, startZ = 0.0, z0 = 0.0;

    for(unsigned layer = 1; layer <= this->shape.getNumberOfLayers(); layer++) {

        arrDouble dim(DIM(layer));
        arrDouble sizem(SIZE(layer));
        arrUnsgn cellNums(CELL(layer));
        dimX = dim[0];
        dimY = dim[1];
        dimZ = dim[2];
        sizeX = sizem[0];
        sizeY = sizem[1];

        if(layer > 1) z0 = sizem[2];

        if(this->shape.getShape()==TRAPEZIOD){

            ratioX = (dim[0] - dim[3])/(double)cellNums[2];
            ratioY = (dim[1] - dim[4])/(double)cellNums[2];

            if(layer > 1) {
                dimX-= ratioX;
                dimY-= ratioY;
                sizeX = dimX/(double)cellNums[0];
                sizeY = dimY/(double)cellNums[1];
                startX+= ratioX/2.0;
                startY+= ratioY/2.0;
            }
        }

        for(double stepZ = z0; stepZ <= dimZ + EPS; stepZ+= sizem[2]) {

            if(this->shape.getShape() == TRAPEZIOD && stepZ > z0){
                dimX-= ratioX;
                dimY-= ratioY;
                sizeX = dimX/(double)cellNums[0];
                sizeY = dimY/(double)cellNums[1];
                startX+= ratioX/2.0;
                startY+= ratioY/2.0;
            }

            for(double stepY = 0; stepY <= dimY + EPS; stepY+= sizeY) {

                for(double stepX = 0; stepX <= dimX + EPS; stepX+= sizeX) {

                    this->addPoint(stepX + startX, stepY + startY, stepZ + startZ);
                }
            }
        }

        startZ += dim[2];
    }
}
