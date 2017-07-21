#include "../../include/Shape.h"

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
            case INVALID__SHAPE:
            default:
                cout << "can't recognize the type of SHAPE!!!\n";
        }
    }
}


void Shape::deleteCUBOID(unsigned layer) {

    vector<ArrDouble>::iterator it = (this->dim.begin() + layer - 1);
    this->dim.erase(it);
    it = (this->cellSizes.begin() + layer - 1);
    this->cellSizes.erase(it);
    vector<ArrUnsgn>::iterator it2 = (this->cellNumbers.begin() + layer - 1);
    this->cellNumbers.erase(it2);
}


void Shape::deleteTRAPEZIOID(unsigned layer) {

    if(layer == 1) {
        this->dim.erase(this->dim.begin());
        this->cellSizes.erase(this->cellSizes.begin());
        this->cellNumbers.erase(this->cellNumbers.begin());
    }
    if(layer == this->numberOfLayers) {

        this->dim.pop_back();
        this->cellSizes.pop_back();
        this->cellNumbers.pop_back();
    }

    vector<ArrDouble>::iterator it = (this->dim.begin() + layer - 1);
    (it + 1)->insert(0, (*it)[0]);
    (it + 1)->insert(1, (*it)[1]);
    this->dim.erase(it);

    it = (this->cellSizes.begin() + layer - 1);
    this->cellSizes.erase(it);

    vector<ArrUnsgn>::iterator it2 = (this->cellNumbers.begin() + layer - 1);
    this->cellNumbers.erase(it2);

}


void Shape::deleteCYLINDER(unsigned layer) {

    vector<ArrDouble>::iterator it = (this->dim.begin() + layer - 1);
    this->dim.erase(it);
    it = (this->cellSizes.begin() + layer - 1);
    this->cellSizes.erase(it);
    vector<ArrUnsgn>::iterator it2 = (this->cellNumbers.begin() + layer - 1);
    this->cellNumbers.erase(it2);
}


void Shape::deleteOVAL(unsigned layer) {

    vector<ArrDouble>::iterator it = (this->dim.begin() + layer - 1);
    this->dim.erase(it);
    it = (this->cellSizes.begin() + layer - 1);
    this->cellSizes.erase(it);
    vector<ArrUnsgn>::iterator it2 = (this->cellNumbers.begin() + layer - 1);
    this->cellNumbers.erase(it2);
}


void Shape::deleteSPHERIC(unsigned layer) {

    vector<ArrDouble>::iterator it = (this->dim.begin() + layer - 1);
    this->dim.erase(it);
    it = (this->cellSizes.begin() + layer - 1);
    this->cellSizes.erase(it);
    vector<ArrUnsgn>::iterator it2 = (this->cellNumbers.begin() + layer - 1);
    this->cellNumbers.erase(it2);
}
