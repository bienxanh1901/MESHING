#include "../include/Shape.h"

void Shape::addLayer() {

    this->numberOfLayers+= 1;
    switch(this->type)
    {
        case SPHERIC:
            this->addSPHERIC();
            break;
        case CYLINDER:
            this->addCYLINDER();
            break;
        case CUBOID:
            this->addCUBOID();
            break;
        case OVAL:
            this->addOVAL();
            break;
        case TRAPEZIOD:
            this->addTRAPEZIOID();
            break;
        default:
    }
}





