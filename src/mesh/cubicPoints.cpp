#include "../../include/Mesh.h"

void Mesh::cubicPoints() {

    double sizeX, sizeY, sizeZ, dimX, dimY, dimZ,
           startX = 0.0, startY = 0.0, startZ = 0.0, z0 = 0.0;

    for(unsigned layer = 1; layer <= this->shape.getNumberOfLayers(); layer++) {

        ArrDouble dim(DIM(layer)),
                  sizem(SIZE(layer)),
                  ratiom(RAT(layer));
        ArrUnsgn cellNums(CELL(layer));
        dimX = dim[0];
        dimY = dim[1];
        dimZ = dim[2];
        sizeX = sizem[0];
        sizeY = sizem[1];
        sizeZ = sizem[2];
        double tanX, tanY;

        if(layer > 1) z0 = sizeZ;

<<<<<<< HEAD
=======
        // in case of TRAPEZIOD, we recalculate the dimension
>>>>>>> meshgrading
        if(this->shape.getShape() == TRAPEZIOD){

            tanX = dimZ/((dimX - dim[3])/2.0);
            tanY = dimZ/((dimY - dim[4])/2.0);

            if(layer > 1) {
                dimX-= 2*sizeZ/tanX;
                dimY-= 2*sizeZ/tanY;

                if(ratiom[0] == 1.0) {

                    sizeX = dimX/(double)cellNums[0];

                } else {

                    sizeX = dimX/2.0*(1.0 - ratiom[0])/(1.0 - pow(ratiom[0], cellNums[0]/2));

                }

                if(ratiom[1] == 1.0) {

                    sizeY = dimY/(double)cellNums[1];

                } else {

                    sizeY = dimY/2.0*(1.0 - ratiom[1])/(1.0 - pow(ratiom[1], cellNums[1]/2));
                }

                startX+= sizeZ/tanX;
                startY+= sizeZ/tanY;
            }
        }

        for(double stepZ = z0; stepZ <= dimZ + EPS; stepZ+= sizeZ) {

<<<<<<< HEAD
=======
            // in case of TRAPEZIOD, we recalculate the dimension
>>>>>>> meshgrading
            if(this->shape.getShape() == TRAPEZIOD && stepZ > z0){

                dimX-= 2*sizeZ/tanX;
                dimY-= 2*sizeZ/tanY;

                if(ratiom[0] == 1.0) {

                    sizeX = dimX/(double)cellNums[0];

                } else {

                    sizeX = dimX/2.0*(1.0 - ratiom[0])/(1.0 - pow(ratiom[0], cellNums[0]/2));

                }

                if(ratiom[1] == 1.0) {

                    sizeY = dimY/(double)cellNums[1];

                } else {

                    sizeY = dimY/2.0*(1.0 - ratiom[1])/(1.0 - pow(ratiom[1], cellNums[1]/2));
                }

                startX+= sizeZ/tanX;
                startY+= sizeZ/tanY;

            }



            for(double stepY = 0.0; stepY <= dimY + EPS; stepY+= sizeY) {

                for(double stepX = 0.0; stepX <= dimX + EPS; stepX+= sizeX) {

                    this->addPoint(stepX + startX, stepY + startY, stepZ + startZ);

                    if(stepX > 0.0 && stepX < dimX - EPS && ratiom[0] != 1.0) {

                        if(stepX < dimX/2.0 - EPS) {

                            sizeX*= ratiom[0];

                        } else if(stepX > dimX/2.0 + EPS){

                            sizeX/=ratiom[0];
                        }

                    }

                }

                if(stepY > 0.0 && stepY < dimY - EPS && ratiom[1] != 1.0) {

                    if(stepY < dimY/2.0 - EPS) {

                        sizeY*= ratiom[1];

                    } else if(stepY > dimY/2.0 + EPS){

                        sizeY/=ratiom[1];

                    }

                }

            }

            if(stepZ > 0.0 && stepZ < dimZ - EPS && ratiom[2] != 1.0) {

                if(stepZ < dimZ/2.0 - EPS) {

                    sizeZ*= ratiom[2];

                } else if(stepZ > dimZ/2.0 + EPS){

                    sizeZ/=ratiom[2];

                }

            }
        }

        startZ += dim[2];
    }
}
