#include "../include/Mesh.h"

void Mesh::cubicInternalFacesandCells() {

    arrUnsgn cellNums = this->shape.getCellNumbersOfLayer(1);
    unsigned lengthPoints = cellNums[0] + 1;
    unsigned widthPoints = cellNums[1] + 1;
    unsigned basePoints = lengthPoints*widthPoints;
    unsigned baseCells = cellNums[0]*cellNums[1];
    unsigned startPoints = 0;

    unsigned k1, k2, j1, j2, i1;

    for(unsigned layer = 1; layer <= this->shape.getNumberOfLayers(); layer ++) {

        if(layer > 1) {
            startPoints+= basePoints*cellNums[2];
            cellNums = this->shape.getCellNumbersOfLayer(layer);
        }

        for(unsigned k = 1; k <= cellNums[2]; k++) {

            k1 = startPoints + (k - 1)*basePoints;
            k2 = k1 + basePoints;

            for(unsigned j = 1; j <= cellNums[1]; j++) {

                j1 = (j - 1)*lengthPoints;
                j2 = j1 + lengthPoints;

                for(unsigned i = 1; i <= cellNums[0]; i++) {

                    i1 = i - 1;

                    this->addCell(k1 + j1 + i1, k1 + j1 + i, k1 + j2 + i, k1 + j2 + i1,
                                  k2 + j1 + i1, k2 + j1 + i, k2 + j2 + i, k2 + j2 + i1);

                    if(i < cellNums[0]) {

                        this->addFace(k1 + j1 + i, k1 + j2 + i, k2 + j2 + i, k2 + j1 + i);
                        this->addOwner(this->meshInfo.numberOfCells);
                        this->addNeighbor(this->meshInfo.numberOfCells + 1);
                    }

                    if(j < cellNums[1]) {

                        this->addFace(k1 + j2 + i1, k2 + j2 + i1, k2 + j2 + i, k1 + j2 + i);
                        this->addOwner(this->meshInfo.numberOfCells);
                        this->addNeighbor(this->meshInfo.numberOfCells + cellNums[0]);
                    }

                    if(k < cellNums[2] && layer < this->shape.getNumberOfLayers()) {

                        this->addFace(k1 + j1 + i1, k1 + j1 + i, k1 + j2 + i, k1 + j2 + i1);
                        this->addOwner(this->meshInfo.numberOfCells);
                        this->addNeighbor(this->meshInfo.numberOfCells + baseCells);
                    }
                }
            }
        }
    }

    this->meshInfo.numberOfInternalFaces = this->meshInfo.numberOfFaces;
}
