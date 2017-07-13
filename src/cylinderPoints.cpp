#include "../include/Mesh.h"

void Mesh::basePoints(){

    arrDouble dim(this->shape.getDimsOfLayer(1));
    arrDouble sizem(this->shape.getSizesOfLayer(1));
    arrUnsgn cellNums(this->shape.getCellNumbersOfLayer(1));
    unsigned sidePoints = cellNums[0]/8;
    double majorR = dim[0];
    double halfR = 0.5*majorR;
    double p2 = halfR/sqrt(2.0);
    double cornerX = halfR - p2*(1.0 - tan(PI/6.0))/sqrt(2.0);
    double minorR, cornerY;

    if(this->shape.getShape() == OVAL) {
        minorR = dim[2];
        halfR = 0.5*minorR;
        p2 = halfR/sqrt(2.0);
        cornerY = halfR - p2*(1.0 - tan(PI/6.0))/sqrt(2.0);
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
            sizeX = (majorR - cornerX/fabs(costheta))/(double)sidePoints;
            sizeY = (minorR - cornerY/fabs(costheta))/(double)sidePoints;
        }else {
            sizeX = (majorR - cornerX/fabs(sintheta))/sidePoints;
            sizeY = (minorR - cornerY/fabs(sintheta))/sidePoints;
        }

        for(unsigned i = 0; i < sidePoints; i++){

            this->addPoint((majorR - (double)i*sizeX)*sintheta, (minorR - (double)i*sizeY)*costheta, 0.0);
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
    unsigned sidePoints = cellNums[0]/8;
    unsigned edgePoints = cellNums[0]/4 + 1;
    unsigned basePoints = cellNums[0]*sidePoints + pow(edgePoints,2);
    Point point;

    for(unsigned layer = 1; layer <= this->shape.getNumberOfLayers(); layer++) {

        if(layer > 1) cellNums = arrUnsgn(this->shape.getCellNumbersOfLayer(layer));
        arrDouble dim(this->shape.getDimsOfLayer(layer));
        arrDouble sizem(this->shape.getSizesOfLayer(layer));

        for(double z = sizem[1]; z <= dim[1] + EPS; z+= sizem[1]) {

            for(unsigned i = 0; i < basePoints; i++){

                point = this->points[i] + Point(0.0, 0.0, z);
                this->addPoint(point);
            }
        }

    }

}
