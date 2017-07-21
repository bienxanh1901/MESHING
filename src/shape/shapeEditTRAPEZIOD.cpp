#include "../../include/Shape.h"


void Shape::editTRAPEZIOID(unsigned layer, ArrDouble& sDim, ArrDouble& sSize, ArrDouble& sRatio) {

    unsigned cellX, cellY, cellZ;
    ArrUnsgn sCell(3);

    if(layer == 1) {

        cellX = (unsigned)ROUNDED(sDim[0]/sSize[0], 0.0);
        cellY = (unsigned)ROUNDED(sDim[1]/sSize[1], 0.0);
        cellZ = (unsigned)ROUNDED(sDim[2]/sSize[2], 0.0);

        if(sRatio[0] == 1.0) {

            sSize.insert(0, sDim[0]/(double)cellX) ;

        } else {

            sSize.insert(0, sDim[0]/2.0*(1.0 - sRatio[0])/(1.0 - pow(sRatio[0], cellX/2)));

        }

        if(sRatio[1] == 1.0) {

            sSize.insert(1, sDim[1]/(double)cellY) ;

        } else {

            sSize.insert(1, sDim[1]/2.0*(1.0 - sRatio[1])/(1.0 - pow(sRatio[1], cellY/2)));

        }

        if(sRatio[2] == 1.0) {

            sSize.insert(2, sDim[2]/(double)cellZ) ;

        } else {

            sSize.insert(2, sDim[2]/2.0*(1.0 - sRatio[2])/(1.0 - pow(sRatio[2], cellZ/2)));

        }

        sCell.insert(0, cellX);
        sCell.insert(1, cellY);
        sCell.insert(2, cellZ);

        for(unsigned i = 0; i < this->numberOfLayers; i++) {

            if(i > 0) {
                sDim.insert(0,(this->dim[i - 1])[3]);
                sDim.insert(1,(this->dim[i - 1])[4]);
                sDim.insert(2, (this->dim[i])[2]);
                sDim.insert(3, (this->dim[i])[3]);
                sDim.insert(4, (this->dim[i])[4]);
                sSize.insert(2, (this->cellSizes[i])[2]);
                sCell.insert(2, (this->cellNumbers[i])[2]);
                sRatio.insert(2, (this->cellToCellRatio[i])[2]);

            }

            this->dim[i] = sDim;
            this->cellSizes[i] = sSize;
            this->cellNumbers[i] = sCell;
            this->cellToCellRatio[i] = sRatio;

        }

    } else {

        cellZ = (unsigned)ROUNDED(sDim[2]/sSize[2], 0.0);

        if(sRatio[2] == 1.0) {

            sSize.insert(2, sDim[2]/(double)cellZ) ;

        } else {

            sSize.insert(2, sDim[2]/2.0*(1.0 - sRatio[2])/(1.0 - pow(sRatio[2], cellZ/2)));

        }

        sDim.insert(0, (this->dim[layer - 2])[3]);
        sDim.insert(1, (this->dim[layer - 2])[4]);
        sSize.insert(0, (this->cellSizes[layer - 2])[0]);
        sSize.insert(1, (this->cellSizes[layer - 2])[1]);
        sCell.insert(0, (this->cellNumbers[layer - 2])[0]);
        sCell.insert(1, (this->cellNumbers[layer - 2])[1]);
        sRatio.insert(0, (this->cellToCellRatio[layer - 2])[0]);
        sRatio.insert(1, (this->cellToCellRatio[layer - 2])[1]);


        this->dim[layer - 1] = sDim;
        this->cellSizes[layer - 1] = sSize;
        this->cellNumbers[layer - 1] = sCell;
        this->cellToCellRatio[layer - 1] = sRatio;
    }


}
