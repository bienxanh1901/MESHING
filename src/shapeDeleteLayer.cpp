#include "../include/Shape.h"

void Shape::deleteLayer(unsigned layer) {

    if(layer != 0) {

        this->numberOfLayers-= 1;
        switch(this->type)
        {
            case SPHERIC:
                this->deleteSPHERIC(layer);
                break;
            case CYLINDER:
                this->deleteCYLINDER(layer);
                break;
            case CUBOID:
                this->deleteCUBOID(layer);
                break;
            case OVAL:
                this->deleteOVAL(layer);
                break;
            case TRAPEZIOD:
                this->deleteTRAPEZIOID(layer);
                break;
            default:
        }
    }
}


void Shape::deleteCUBOID(unsigned layer) {

    vector<arrDouble>::iterator it = (this->dim.begin() + layer - 1);
    this->dim.erase(it);
    it = (this->cellSizes.begin() + layer - 1);
    this->cellSizes.erase(it);
    it = (this->cellNumbers.begin() + layer - 1);
    this->cellNumbers.erase(it);
}


void Shape::deleteTRAPEZIOID() {

    if(layer == 1) {

        this->dim.pop_front();
        this->cellSizes.pop_front();
        this->cellNumbers.pop_front();
    }
    if(layer == this->numberOfLayers) {

        this->dim.pop_back();
        this->cellSizes.pop_back();
        this->cellNumbers.pop_back();
    }

    vector<arrDouble>::iterator it = (this->dim.begin() + layer - 1);
    (it + 1)->insert(0, (*it)[0]);
    (it + 1)->insert(1, (*it)[1]);
    this->dim.erase(it);

    it = (this->cellSizes.begin() + layer - 1);
    this->cellSizes.erase(it);

    it = (this->cellNumbers.begin() + layer - 1);
    this->cellNumbers.erase(it);

}


void Shape::deleteCYLINDER() {

    vector<arrDouble>::iterator it = (this->dim.begin() + layer - 1);
    this->dim.erase(it);
    it = (this->cellSizes.begin() + layer - 1);
    this->cellSizes.erase(it);
    it = (this->cellNumbers.begin() + layer - 1);
    this->cellNumbers.erase(it);
}


void Shape::addOVAL() {

    vector<arrDouble>::iterator it = (this->dim.begin() + layer - 1);
    this->dim.erase(it);
    it = (this->cellSizes.begin() + layer - 1);
    this->cellSizes.erase(it);
    it = (this->cellNumbers.begin() + layer - 1);
    this->cellNumbers.erase(it);
}


void Shape::addSPHERIC() {

    vector<arrDouble>::iterator it = (this->dim.begin() + layer - 1);
    this->dim.erase(it);
    it = (this->cellSizes.begin() + layer - 1);
    this->cellSizes.erase(it);
    it = (this->cellNumbers.begin() + layer - 1);
    this->cellNumbers.erase(it);
}
