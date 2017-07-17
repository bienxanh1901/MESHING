#include "../../include/Shape.h"

void Shape::addSPHERIC() {

    double radius;
    double sizeR;
    unsigned cellR;
    arrDouble dimOfLayer(this->numberOfDims);
    arrDouble sizesOfLayer(this->numberOfDims);
    arrUnsgn  cellsOfLayer(this->numberOfDims);

    cout << "input radius of layer " << this->numberOfLayers << ":\n";
    cin >> radius;

    cout << "input mesh size of layer " << this->numberOfLayers << ":\n";
    cin >> sizeR;

    dimOfLayer.insert(0, radius);

    cellR = (unsigned)ROUNDED(2.0*PI*radius/sizeR, 0.0);
    cellR = (cellR/16 + 1)*16;
    sizeR = 2.0*PI/cellR;

    sizesOfLayer.insert(0, sizeR);

    cellsOfLayer.insert(0, cellR);

    this->dim.push_back(dimOfLayer);
    this->cellSizes.push_back(sizesOfLayer);
    this->cellNumbers.push_back(cellsOfLayer);
}
