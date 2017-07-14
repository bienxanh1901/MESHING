#include "../include/Mesh.h"

void Mesh::cylinderInternalFacesandCells() {

    arrUnsgn cellNums(this->shape.getCellNumbersOfLayer(1));
    unsigned baseP = cellNums[0]*cellNums[0]/8 + pow(cellNums[0]/4 + 1,2);
    unsigned startP = 0;

    for(unsigned layer = 1; layer <= this->shape.getNumberOfLayers(); layer ++) {

        if(layer > 1) {

            startP+= baseP*cellNums[1];
            cellNums = arrUnsgn(this->shape.getCellNumbersOfLayer(layer));
        }

        for(unsigned k = 1; k <= cellNums[1]; k++) {
            this->cylinderOuterPart(layer, k, startP);
            this->cylinderInnerPart(layer, k, startP);
        }
    }

    this->meshInfo.numberOfInternalFaces = this->meshInfo.numberOfFaces;
}

void Mesh::cylinderOuterPart(unsigned layer, unsigned k, unsigned startP) {

    arrUnsgn cellNums(this->shape.getCellNumbersOfLayer(layer));
    unsigned sideP = cellNums[0]/8;
    unsigned outerP = cellNums[0]*sideP;
    unsigned baseP = outerP + pow(cellNums[0]/4 + 1, 2);
    unsigned baseC = outerP + pow(cellNums[0]/4, 2);
    unsigned j1, j2, i1, i2, k1, k2;

    k1 = startP + (k - 1)*baseP;
    k2 = k1 + baseP;

    for(unsigned j = 0; j < cellNums[0]; j++) {

        j1 = j*sideP;
        j2 = j1 + sideP;
        if(j == cellNums[0] - 1) j2 = 0;

        for(unsigned i = 1; i < sideP; i++) {
            i1 = i - 1;

            this-> addCell(k1 + j1 + i1, k1 + j1 + i, k1 + j2 + i, k1 + j2 + i1,
                           k2 + j1 + i1, k2 + j1 + i, k2 + j2 + i, k2 + j2 + i1);

            this->addFace(k1 + j1 + i, k1 + j2 + i, k2 + j2 + i, k2 + j1 + i);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(this->meshInfo.numberOfCells + 1);

            if(j == 0) {
                this->addFace(k1 + i1, k1 + i, k2 + i, k2 + i1);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(outerP - sideP + this->meshInfo.numberOfCells);
            }

            if(j < cellNums[0] -1) {
                this->addFace(k1 + j2 + i1, k2 + j2 + i1, k2 + j2 + i, k1 + j2 + i);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(this->meshInfo.numberOfCells + sideP);
            }

            if(layer == this->shape.getNumberOfLayers() && k == cellNums[1]) continue;
            this->addFace(k2 + j1 + i1, k2 + j1 + i, k2 + j2 + i, k2 + j2 + i1);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(baseC + this->meshInfo.numberOfCells);

        }

        //connect with inner part
        j1 = (j + 1)*sideP - 1;
        j2 = j1 + sideP;
        if(j == cellNums[0] - 1) j2 = sideP - 1;

        this->meshConnected2D(layer, j, i1, i2);

        this-> addCell(k1 + j1, k1 + i1, k1 + i2, k1 + j2,
                       k2 + j1, k2 + i1, k2 + i2, k2 + j2);

        this->addFace(k1 + i1, k1 + i2, k2 + i2, k2 + i1);
        this->addOwner(this->meshInfo.numberOfCells);
        this->addNeighbor(i1 + 1);

        if(j == 0) {
            this->addFace(k1 + j1, k1 + i1, k2 + i1, k2 + j1);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(outerP);
        }

        if(j < cellNums[0] -1) {
            this->addFace(k1 + j2, k2 + j2, k2 + i2, k1 + i2);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(this->meshInfo.numberOfCells + 1);
        }

        if(layer == this->shape.getNumberOfLayers() && k == cellNums[1]) continue;

        this->addFace(k2 + j1, k2 + i1, k2 + i2, k2 + j2);
        this->addOwner(this->meshInfo.numberOfCells);
        this->addNeighbor(baseC + this->meshInfo.numberOfCells);
    }

}

void Mesh::cylinderInnerPart(unsigned layer, unsigned k, unsigned startP) {

    arrUnsgn cellNums(this->shape.getCellNumbersOfLayer(layer));
    unsigned edgeP = cellNums[0]/4 + 1;
    unsigned outerP = cellNums[0]*cellNums[0]/8;
    unsigned baseP = outerP + pow(edgeP,2);
    unsigned baseC = outerP + pow(edgeP - 1,2);
    unsigned j1, j2, i1, k1, k2;

    k1 = startP + outerP + (k - 1)*baseP;
    k2 = k1 + baseP;

    for(unsigned j = 1; j < edgeP; j++) {
        j1 = (j - 1)*edgeP;
        j2 = j1 + edgeP;

        for(unsigned i = 1; i < edgeP; i++) {
            i1 = i - 1;

            this-> addCell(k1 + j2 + i1, k1 + j2 + i, k1 + j1 + i, k1 + j1 + i1,
                           k2 + j2 + i1, k2 + j2 + i, k2 + j1 + i, k2 + j1 + i1);

            if(i < edgeP - 1) {
                this->addFace(k1 + j1 + i, k2 + j1 + i, k2 + j2 + i, k1 + j2 + i);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(this->meshInfo.numberOfCells + 1);
            }

            if(j < edgeP - 1) {
                this->addFace(k1 + j2 + i1, k1 + j2 + i, k2 + j2 + i, k2 + j2 + i1);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(this->meshInfo.numberOfCells + edgeP - 1);
            }

            //reach to the top boundaries
            if(layer == this->shape.getNumberOfLayers() && k == cellNums[1]) continue;

            this->addFace(k2 + j1 + i1, k2 + j2 + i1, k2 + j2 + i, k2 + j1 + i);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(baseC + this->meshInfo.numberOfCells);
        }
    }
}
