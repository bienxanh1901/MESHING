#include "../include/Mesh.h"

void Mesh::basePoints(){

    arrDouble dim(this->shape.getDimsOfLayer(1));
    arrDouble sizem(this->shape.getSizesOfLayer(1));
    arrUnsgn cellNums(this->shape.getCellNumbersOfLayer(1));
    double sideP = (double)(cellNums[0]/8);
    double majorR = dim[0];
    double cornerX = majorR*tan(PI/6.0)/2.0;
    double minorR, cornerY;

    if(this->shape.getShape() == OVAL) {
        minorR = dim[2];
        cornerY = minorR*tan(PI/6.0)/2.0;
    } else {
        minorR = majorR;
        cornerY = cornerX;
    }

    //points of outer circular
    for(double theta = -PI/4; theta < 7*PI/4; theta+= sizem[0]){
        double costheta = cos(theta);
        double sintheta = sin(theta);
        double sizeX, sizeY;

        if(fabs(costheta) >= 1.0/sqrt(2.0)){
            sizeX = (majorR - cornerX/fabs(costheta))/sideP;
            sizeY = (minorR - cornerY/fabs(costheta))/sideP;
        }else {
            sizeX = (majorR - cornerX/fabs(sintheta))/sideP;
            sizeY = (minorR - cornerY/fabs(sintheta))/sideP;
        }

        for(double i = 0.0; i < sideP; i+=1.0){

            this->addPoint((majorR - i*sizeX)*sintheta, (minorR - i*sizeY)*costheta, 0.0);
        }
    }


    // points of inner rectangular
    double sizeX = 2.0*cornerX/(double)(cellNums[0]/4);
    double sizeY = 2.0*cornerY/(double)(cellNums[0]/4);

    for(double y = cornerY; y >= -cornerY - EPS; y-= sizeY){

        for(double x = -cornerX; x <= cornerX + EPS; x+= sizeX){

            this->addPoint(x, y, 0.0);
        }
    }
}

void Mesh::extrudePoints() {

    arrUnsgn cellNums(this->shape.getCellNumbersOfLayer(1));
    unsigned basePoints = cellNums[0]*cellNums[0]/8 + pow(cellNums[0]/4 + 1,2);
    double startZ = 0.0;
    Point point;

    for(unsigned layer = 1; layer <= this->shape.getNumberOfLayers(); layer++) {

        arrDouble dim(this->shape.getDimsOfLayer(layer));
        arrDouble sizem(this->shape.getSizesOfLayer(layer));

        for(double z = sizem[1]; z <= dim[1] + EPS; z+= sizem[1]) {

            for(unsigned i = 0; i < basePoints; i++){

                point = this->points[i] + Point(0.0, 0.0, startZ + z);
                this->addPoint(point);
            }
        }
        startZ+= dim[1];

    }
}
