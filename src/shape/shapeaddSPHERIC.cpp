#include "../../include/Shape.h"

//void Shape::addSPHERIC() {
//
//    double radius;
//    double sizeR;
//    unsigned cellR;
//    ArrDouble dimOfLayer(this->numberOfDims);
//    ArrDouble sizesOfLayer(this->numberOfDims);
//    ArrUnsgn  cellsOfLayer(this->numberOfDims);
//
//    cout << "input radius of layer " << this->numberOfLayers << ":\n";
//    cin >> radius;
//
//    cout << "input mesh size of layer " << this->numberOfLayers << ":\n";
//    cin >> sizeR;
//
//    dimOfLayer.insert(0, radius);
//
//    cellR = (unsigned)ROUNDED(2.0*PI*radius/sizeR, 0.0);
//    cellR = (cellR/16 + 1)*16;
//    sizeR = 2.0*PI/cellR;
//
//    sizesOfLayer.insert(0, sizeR);
//
//    cellsOfLayer.insert(0, cellR);
//
//    this->dim.push_back(dimOfLayer);
//    this->cellSizes.push_back(sizesOfLayer);
//    this->cellNumbers.push_back(cellsOfLayer);
//}


void Shape::addSPHERIC(ArrDouble& sDim, ArrDouble& sSize, ArrDouble& sRatio) {

    unsigned cellR;
    ArrUnsgn sCell(this->numberOfDims);

    cellR = (unsigned)ROUNDED(2.0*PI*sDim[0]/sSize[0], 0.0);
    cellR = (cellR/16 + 1)*16;

    sSize.insert(0, 2.0*PI/(double)cellR) ;

    sCell.insert(0, cellR);

    this->dim.push_back(sDim);
    this->cellSizes.push_back(sSize);
    this->cellNumbers.push_back(sCell);
    this->cellToCellRatio.push_back(sRatio);
}
