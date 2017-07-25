#include "../../include/Mesh.h"

void Mesh::basePoints(){

    ArrDouble dim(DIM(1)),
              sizem(SIZE(1)),
              ratiom(RAT(1));
    ArrUnsgn cellNums(CELL(1));


    double sideP = (double)(cellNums[0]/8),
           majorR = dim[0],
           cornerX = majorR*tan(PI/6.0)/2.0,
           minorR, cornerY;

    if(this->shape.getShape() == OVAL) {

        minorR = dim[2];
        cornerY = minorR*tan(PI/6.0)/2.0;

    } else {

        minorR = majorR;
        cornerY = cornerX;

    }

    //points of outer circular
    for(double theta = -PI/4; theta < 7*PI/4 - EPS; theta+= sizem[0]){

<<<<<<< HEAD
        double costheta = cos(theta), sintheta = sin(theta),
=======
        double costheta = cos(theta),
               sintheta = sin(theta),
>>>>>>> meshgrading
               sizeX, sizeY,
               dimX, dimY;

        if(fabs(costheta) >= 1.0/sqrt(2.0)){

            dimX = majorR - cornerX/fabs(costheta);
            dimY = minorR - cornerY/fabs(costheta);

        }else {

            dimX = majorR - cornerX/fabs(sintheta);
            dimY = minorR - cornerY/fabs(sintheta);

        }


        if(ratiom[0] == 1.0){

            sizeX = dimX/sideP;
            sizeY = dimY/sideP;

        }else {
<<<<<<< HEAD

            sizeX = dimX*(1.0 - ratiom[0])/(1.0 - pow(ratiom[0], sideP));
            sizeY = dimY*(1.0 - ratiom[0])/(1.0 - pow(ratiom[0], sideP));
=======
            sizeX = dimX/sideP;
            sizeY = dimY/sideP;
            sizeX = (dimX - sizeX)*(1.0 - ratiom[0])/(1.0 - pow(ratiom[0], sideP - 1.0));
            sizeY = (dimY - sizeY)*(1.0 - ratiom[0])/(1.0 - pow(ratiom[0], sideP - 1.0));
>>>>>>> meshgrading

        }

        for(double x = 0.0, y = 0.0; x < dimX - EPS && y < dimY - EPS; x+= sizeX, y+= sizeY){

            this->addPoint((majorR - x)*sintheta, (minorR - y)*costheta, 0.0);

            if(x > 0.0 && y > 0.0 && ratiom[0] != 1.0) {

                    sizeX*= ratiom[0];
                    sizeY*= ratiom[0];

            }
        }
    }


    // points of inner rectangular
    double sizeX = 2.0*cornerX/(double)(cellNums[0]/4),
           sizeY = 2.0*cornerY/(double)(cellNums[0]/4);

    for(double y = cornerY; y >= -cornerY - EPS; y-= sizeY){

        for(double x = -cornerX; x <= cornerX + EPS; x+= sizeX){

            this->addPoint(x, y, 0.0);

        }
    }
}

void Mesh::extrudePoints() {

    ArrUnsgn cellNums(CELL(1));
    unsigned basePoints = cellNums[0]*cellNums[0]/8 + pow(cellNums[0]/4 + 1,2);
    double startZ = 0.0;
    Point point;

    for(unsigned layer = 1; layer <= this->shape.getNumberOfLayers(); layer++) {

        ArrDouble dim(DIM(layer)),
                  sizem(SIZE(layer)),
                  ratiom(RAT(layer));
        double sizeZ = sizem[1];


        for(double z = sizem[1]; z <= dim[1] + EPS; z+= sizeZ) {

            for(unsigned i = 0; i < basePoints; i++){

                point = this->points[i] + Point(0.0, 0.0, startZ + z);
                this->addPoint(point);
            }

            if(z > 0.0 && z < dim[1] - EPS && ratiom[1] != 1.0) {

                if(z < dim[1]/2.0 - EPS) {

                    sizeZ*= ratiom[1];

                } else if(z > dim[1]/2.0 + EPS){

                    sizeZ/=ratiom[1];

                }

            }
        }
        startZ+= dim[1];

    }
}
