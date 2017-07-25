#include "../../include/Mesh.h"

void Mesh::cubicInternalFacesandCells() {

    ArrUnsgn cellNums = CELL(1);
    unsigned lengthPoints = cellNums[0] + 1,
             widthPoints = cellNums[1] + 1,
             basePoints = lengthPoints*widthPoints,
             baseCells = cellNums[0]*cellNums[1],
             startPoints = 0;

    for(unsigned layer = 1; layer <= this->shape.getNumberOfLayers(); layer ++) {

        if(layer > 1) {

            startPoints+= basePoints*cellNums[2];
            cellNums = CELL(layer);
        }

        for(unsigned k = 1; k <= cellNums[2]; k++) {

<<<<<<< HEAD
            unsigned k1 = startPoints + (k - 1)*basePoints, k2 = k1 + basePoints;
=======
            unsigned k1 = startPoints + (k - 1)*basePoints,
                     k2 = k1 + basePoints;
>>>>>>> meshgrading

            for(unsigned j = 1; j <= cellNums[1]; j++) {

                unsigned j1 = (j - 1)*lengthPoints, j2 = j1 + lengthPoints;

                for(unsigned i = 1, i1 = 0; i <= cellNums[0]; i++, i1++) {

                    this->addCell(k1 + j1 + i1, k1 + j1 + i, k1 + j2 + i, k1 + j2 + i1,
                                  k2 + j1 + i1, k2 + j1 + i, k2 + j2 + i, k2 + j2 + i1);
                    this->mark.push_back(layer);

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

                    //reach to the top boundaries
                    if(layer == this->shape.getNumberOfLayers() && k == cellNums[2]) continue;

                    this->addFace(k1 + j1 + i1, k1 + j1 + i, k1 + j2 + i, k1 + j2 + i1);
                    this->addOwner(this->meshInfo.numberOfCells);
                    this->addNeighbor(this->meshInfo.numberOfCells + baseCells);
                }
            }
        }

        //restore cells of each layer
        if(layer == 1) this->cellsOfLayer.push_back(this->meshInfo.numberOfCells);
        else this->cellsOfLayer.push_back(this->meshInfo.numberOfCells - this->cellsOfLayer[layer - 2]);
    }

    this->meshInfo.numberOfInternalFaces = this->meshInfo.numberOfFaces;
}
