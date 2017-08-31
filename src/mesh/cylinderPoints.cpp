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

        double costheta = cos(theta),
               sintheta = sin(theta),
               dimX, dimY, x2, y2,
               deltaSX, deltaSY, deltaEX, deltaEY;

        if(fabs(costheta) >= 1.0/sqrt(2.0)){

            x2 = cornerX/fabs(costheta);
            y2 = cornerY/fabs(costheta);

        }else {

            x2 = cornerX/fabs(sintheta);
            y2 = cornerY/fabs(sintheta);

        }

        dimX = majorR - x2;
        dimY = minorR - y2;

        if(ratiom[0] == 1.0){

            deltaSX = dimX/sideP;
            deltaSY = dimY/sideP;
            deltaEX = EPS;
            deltaEY = EPS;

        }else {
            double k = pow(ratiom[0], sideP - 1.0);
            deltaSX = dimX*(1.0 - ratiom[0])/(1.0 - pow(ratiom[0], sideP));
            deltaSY = dimY*(1.0 - ratiom[0])/(1.0 - pow(ratiom[0], sideP));
            deltaEX = k*deltaSX - EPS;
            deltaEY = k*deltaSY - EPS;

        }

        for(double x = majorR, y = minorR; x > x2 + deltaEX && y > y2 + deltaEY; x-= deltaSX, y-= deltaSY){

            this->addPoint(x*sintheta, y*costheta, 0.0);

            if(x < majorR && y < minorR && ratiom[0] != 1.0) {

                    deltaSX*= ratiom[0];
                    deltaSY*= ratiom[0];

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


        for(double z = sizeZ; z <= dim[1] + EPS; z+= sizeZ) {

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
