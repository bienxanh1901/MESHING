#include "../../include/Shape.h"

void Shape::addOVAL(ArrDouble& sDim, ArrDouble& sSize, ArrDouble& sRatio) {

    unsigned cellR, cellZ;
    ArrUnsgn sCell(2);

    if(this->numberOfLayers == 1) {

        cellR = (unsigned)ROUNDED(2.0*PI*sDim[0]/sSize[0], 0.0);
        cellR = (cellR/16 + 1)*16;

        cellZ = (unsigned)ROUNDED(sDim[1]/sSize[1], 0.0);

        sSize.insert(0, 2.0*PI/(double)cellR) ;

        if(sRatio[1] == 1.0) {

            sSize.insert(1, sDim[1]/(double)cellZ) ;

        } else {
            //ncell must be even number
            cellZ = 2*(cellZ/2);
            sSize.insert(1, sDim[1]/2.0*(1.0 - sRatio[1])/(1.0 - pow(sRatio[1], cellZ/2)));

        }

        sCell.insert(0, cellR);
        sCell.insert(1, cellZ);

    } else {

        ArrDouble dim2(this->dim.back()),
                  size2(this->cellSizes.back()),
                  rat2(this->cellToCellRatio.back());
        ArrUnsgn cell2(this->cellNumbers.back());

        sDim.insert(0, dim2[0]);
        sDim.insert(2, dim2[2]);

        sSize.insert(0, size2[0]);

        sCell.insert(0, cell2[0]);

        sRatio.insert(0, rat2[0]);

        cellZ = (unsigned)ROUNDED(sDim[1]/sSize[1], 0.0);

        if(sRatio[1] == 1.0) {

            sSize.insert(1, sDim[1]/(double)cellZ) ;

        } else {

            //ncell must be even number
            cellZ = 2*(cellZ/2);
            sSize.insert(1, sDim[1]/2.0*(1.0 - sRatio[1])/(1.0 - pow(sRatio[1], cellZ/2)));

        }

        sCell.insert(1, cellZ);
    }

    this->dim.push_back(sDim);
    this->cellSizes.push_back(sSize);
    this->cellNumbers.push_back(sCell);
    this->cellToCellRatio.push_back(sRatio);
}
