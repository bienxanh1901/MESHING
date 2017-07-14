#include "../include/Mesh.h"

void Mesh::cylinderBoundaryBot(){
    arrUnsgn cellNums(this->shape.getCellNumbersOfLayer(1));
    unsigned baseC = cellNums[0]*cellNums[0]/8 + pow(cellNums[0]/4,2);

    containerIDs pointCells;

    for(unsigned i = 0; i < baseC; i++) {

        pointCells = this->cells[i].getPointsIDList();
        this->addFace( pointCells[3] - 1, pointCells[2] - 1, pointCells[1] - 1, pointCells[0] - 1);
        this->addOwner(i + 1);

    }

    this->boundaries.push_back(baseC);
}


void Mesh::cylinderBoundaryTop(){
    arrUnsgn cellNums(this->shape.getCellNumbersOfLayer(1));
    unsigned baseC = cellNums[0]*cellNums[0]/8 + pow(cellNums[0]/4,2);

    containerIDs pointCells;

    for(unsigned i = this->meshInfo.numberOfCells - baseC; i < this->meshInfo.numberOfCells; i++) {

        pointCells = this->cells[i].getPointsIDList();
        this->addFace( pointCells[4] - 1, pointCells[5] - 1, pointCells[6] - 1, pointCells[7] - 1);
        this->addOwner(i + 1);
    }

    this->boundaries.push_back(baseC);
}


void Mesh::cylinderBoundariesAround()
{
    arrUnsgn cellNums(this->shape.getCellNumbersOfLayer(1));
    unsigned sideP = cellNums[0]/8;
    unsigned baseP = cellNums[0]*sideP + pow(cellNums[0]/4 + 1, 2);
    unsigned baseC = cellNums[0]*sideP + pow(cellNums[0]/4, 2);
    unsigned startP = 0;
    unsigned j1, j2, k1, k2, k3;


    // left boundary
    for(unsigned layer = 1; layer <= this->shape.getNumberOfLayers(); layer++) {

        if(layer > 1) {

            startP+= baseP*cellNums[1];
            cellNums = arrUnsgn(this->shape.getCellNumbersOfLayer(layer));
        }

        for(unsigned k = 1; k <= cellNums[1]; k++){

            k1 = startP + (k - 1)*baseP;
            k2 = k1 + baseP;
            k3 = (k - 1)*baseC;

            for(unsigned j = 1; j <= cellNums[0]/2; j++){

                j1 = (j - 1)*sideP;
                j2 = j1 + sideP;

                this->addFace(k1 + j1, k2 + j1, k2 + j2, k1 + j2);
                this->addOwner(k3 + j1 + 1);
            }
        }
    }

    this->boundaries.push_back(this->shape.getNumberOfLayers()*cellNums[0]*cellNums[1]/2);


    // right boundary
    startP = 0;
    for(unsigned layer = 1; layer <= this->shape.getNumberOfLayers(); layer++) {

        if(layer > 1) {

            startP+= baseP*cellNums[1];
            cellNums = arrUnsgn(this->shape.getCellNumbersOfLayer(layer));
        }

        for(unsigned k = 1; k <= cellNums[1]; k++) {

            k1 = startP + (k - 1)*baseP;
            k2 = k1 + baseP;
            k3 = (k - 1)*baseC;

            for(unsigned j = cellNums[0]/2 + 1; j <= cellNums[0]; j++){

                j1 = (j - 1)*sideP;
                j2 = j1 + sideP;
                if(j == cellNums[0])j2 = 0;

                this->addFace(k1 + j1, k2 + j1, k2 + j2, k1 + j2);
                this->addOwner(k3 + j1 + 1);
            }
        }
    }

    this->boundaries.push_back(this->shape.getNumberOfLayers()*cellNums[0]*cellNums[1]/2);
}
