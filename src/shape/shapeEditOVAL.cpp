#include "../../include/Shape.h"

void Shape::editOVAL(unsigned layer, ArrDouble& sDim, ArrDouble& sSize, ArrDouble& sRatio) {

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

            sSize.insert(1, sDim[1]/2.0*(1.0 - sRatio[1])/(1.0 - pow(sRatio[1], cellZ/2)));

        }

        sCell.insert(0, cellR);
        sCell.insert(1, cellZ);

        for(unsigned i = 0; i < this->numberOfLayers; i++) {

            if(i > 0) {

                sDim.insert(1, (this->dim[i])[1]);
                sSize.insert(1, (this->cellSizes[i])[1]);
                sCell.insert(1, (this->cellNumbers[i])[1]);
                sRatio.insert(1, (this->cellNumbers[i])[1]);

            }

            this->dim[i] = sDim;
            this->cellSizes[i] = sSize;
            this->cellNumbers[i] = sCell;
            this->cellToCellRatio[i] = sRatio;

        }

    } else {

        cellZ = (unsigned)ROUNDED(sDim[1]/sSize[1], 0.0);

        if(sRatio[1] == 1.0) {

            sSize.insert(1, sDim[1]/(double)cellZ) ;

        } else {

            sSize.insert(1, sDim[1]/2.0*(1.0 - sRatio[1])/(1.0 - pow(sRatio[1], cellZ/2)));

        }

        sDim.insert(0, (this->dim[0])[0]);
        sSize.insert(0, (this->cellSizes[0])[0]);
        sCell.insert(0, (this->cellNumbers[0])[0]);
        sCell.insert(1, cellZ);
        sRatio.insert(0, (this->cellNumbers[0])[0]);

        this->dim[layer - 1] = sDim;
        this->cellSizes[layer - 1] = sSize;
        this->cellNumbers[layer - 1] = sCell;
        this->cellToCellRatio[layer - 1] = sRatio;

    }

}
