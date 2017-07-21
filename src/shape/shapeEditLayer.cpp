#include "../../include/Shape.h"

void Shape::editLayer(unsigned layer, ArrDouble& sDim, ArrDouble& sSize, ArrDouble& sRatio) {

    if(layer != 0) {
        switch(this->type)
        {
            case SPHERIC:
                this->editSPHERIC(layer, sDim, sSize, sRatio);
                break;
            case CYLINDER:
                this->editCYLINDER(layer, sDim, sSize, sRatio);
                break;
            case CUBOID:
                this->editCUBOID(layer, sDim, sSize, sRatio);
                break;
            case OVAL:
                this->editOVAL(layer, sDim, sSize, sRatio);
                break;
            case TRAPEZIOD:
                this->editTRAPEZIOID(layer, sDim, sSize, sRatio);
                break;
            case INVALID__SHAPE:
            default:
                cout << "can't recognize the type of SHAPE!!!\n";
        }
    }
}

