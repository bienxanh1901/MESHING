#include "../../include/Shape.h"

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
