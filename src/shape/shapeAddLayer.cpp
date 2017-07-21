#include "../../include/Shape.h"

void Shape::addLayer(ArrDouble& sDim, ArrDouble& sSize, ArrDouble& sRatio) {

    if(this->numberOfLayers == 1 && this->type == SPHERIC) return;

    this->numberOfLayers+= 1;

    switch(this->type)
    {
        case SPHERIC:
            this->addSPHERIC(sDim, sSize, sRatio);
            break;
        case CYLINDER:
            this->addCYLINDER(sDim, sSize, sRatio);
            break;
        case CUBOID:
            this->addCUBOID(sDim, sSize, sRatio);
            break;
        case OVAL:
            this->addOVAL(sDim, sSize, sRatio);
            break;
        case TRAPEZIOD:
            this->addTRAPEZIOID(sDim, sSize, sRatio);
            break;
        case INVALID__SHAPE:
        default:
            cout << "can't recognize the type of SHAPE!!!\n";
    }
}





