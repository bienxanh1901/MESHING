#include "../include/Mesh.h"

void Mesh::basePoints(){

    double angleSize = 2.0*PI/(double)NODE(0);
    double RX = DIM(1), RY = DIM(3);
    double halfR = 0.5*RX;
    double p2 = halfR/sqrt(2.0);
    double cornerX = halfR - p2*(1.0 - tan(PI/6.0))/sqrt(2.0);
    halfR = 0.5*RY;
    p2 = halfR/sqrt(2.0);
    double cornerY = halfR - p2*(1.0 - tan(PI/6.0))/sqrt(2.0);

    unsigned sidePoints = NODE(0)/8;
    double costheta, sintheta;
    double x, y;
    double sizeX, sizeY;

    //points of outer circular
    for(double theta = -PI/4; theta < 7*PI/4; theta+= angleSize){
        costheta = cos(theta);
        sintheta = sin(theta);

        if(fabs(costheta) >= 1.0/sqrt(2.0)){
            sizeX = (RX - cornerX/fabs(costheta))/sidePoints;
            sizeY = (RY - cornerY/fabs(costheta))/sidePoints;
        }else {
            sizeX = (RX - cornerX/fabs(sintheta))/sidePoints;
            sizeY = (RY - cornerY/fabs(sintheta))/sidePoints;
        }

        for(unsigned i = 0; i < sidePoints; i++){
            x = (RX - (double)i*sizeX)*sintheta;
            y = (RY - (double)i*sizeY)*costheta;
            this->addPoint(x, y, 0.0);
        }
    }

    // points of inner rectangular
    sizeX = 2.0*cornerX/(double)(NODE(0)/4);
    sizeY = 2.0*cornerY/(double)(NODE(0)/4);

    for(y = cornerY; y >= -cornerY - EPS; y-= sizeY){

        for(x = -cornerX; x <= cornerX + EPS; x+= sizeX){

            this->addPoint(x, y, 0.0);
        }
    }
}

void Mesh::extrudePoints() {

    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned base = NODE(0)*sidePoints + pow(edgePoints,2);
    Point point;

    for(double z = SIZE(1); z <= DIM(2) + EPS; z+= SIZE(1)){

        for(unsigned i = 0; i < base; i++){

            point = this->points[i] + Point(0.0, 0.0, z);
            this->addPoint(point);
        }
    }
}
