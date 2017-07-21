#include "../../include/Shape.h"

void Shape::editSPHERIC(unsigned layer, ArrDouble& sDim, ArrDouble& sSize, ArrDouble& sRatio) {

    unsigned cellR;
    ArrUnsgn sCell(this->numberOfDims);

    cellR = (unsigned)ROUNDED(2.0*PI*sDim[0]/sSize[0], 0.0);
    cellR = (cellR/16 + 1)*16;

    sSize.insert(0, 2.0*PI/(double)cellR) ;

    sCell.insert(0, cellR);

    this->dim[0] = sDim;
    this->cellSizes[0] = sSize;
    this->cellNumbers[0] = sCell;
    this->cellToCellRatio[0] = sRatio;

}
