#include "../../include/Shape.h"

void Shape::editLayer(unsigned layer) {

    if(layer != 0) {
        switch(this->type)
        {
            case SPHERIC:
                this->editSPHERIC(layer);
                break;
            case CYLINDER:
                this->editCYLINDER(layer);
                break;
            case CUBOID:
                this->editCUBOID(layer);
                break;
            case OVAL:
                this->editOVAL(layer);
                break;
            case TRAPEZIOD:
                this->editTRAPEZIOID(layer);
                break;
            case INVALID__SHAPE:
            default:
                cout << "can't recognize the type of SHAPE!!!\n";
        }
    }
}

