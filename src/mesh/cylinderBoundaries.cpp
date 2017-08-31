#include "../../include/Mesh.h"

void Mesh::cylinderBoundaryBot(){

    ArrUnsgn cellNums(CELL(1));
    unsigned baseC = cellNums[0]*cellNums[0]/8 + pow(cellNums[0]/4,2);

    ContainerIDs pointCells;

    for(unsigned i = 0; i < baseC; i++) {

        pointCells = this->cells[i].getPointsIDList();
        this->addFace( pointCells[3] - 1, pointCells[2] - 1, pointCells[1] - 1, pointCells[0] - 1);
        this->addOwner(i + 1);

    }

    this->boundaries.push_back(baseC);
}


void Mesh::cylinderBoundaryTop(){
    ArrUnsgn cellNums(CELL(1));
    unsigned baseC = cellNums[0]*cellNums[0]/8 + pow(cellNums[0]/4,2);

    ContainerIDs pointCells;

    for(unsigned i = this->meshInfo.numberOfCells - baseC; i < this->meshInfo.numberOfCells; i++) {

        pointCells = this->cells[i].getPointsIDList();
        this->addFace( pointCells[4] - 1, pointCells[5] - 1, pointCells[6] - 1, pointCells[7] - 1);
        this->addOwner(i + 1);
    }

    this->boundaries.push_back(baseC);
}


void Mesh::cylinderBoundariesAround()
{
    ArrUnsgn cellNums(CELL(1));
    unsigned sideP = cellNums[0]/8,
             baseP = cellNums[0]*sideP + pow(cellNums[0]/4 + 1, 2),
             baseC = cellNums[0]*sideP + pow(cellNums[0]/4, 2),
             startPoints = 0, startCells = 0, nfaces = 0;

    // left boundary
    for(unsigned layer = 1; layer <= this->shape.getNumberOfLayers(); layer++) {

        if(layer > 1) {

            startPoints+= baseP*cellNums[1];
            startCells+= baseC*cellNums[1];
            cellNums = ArrUnsgn(CELL(layer));
        }

        for(unsigned k = 1; k <= cellNums[1]; k++){

            unsigned k1 = startPoints + (k - 1)*baseP,
                     k2 = k1 + baseP,
                     k3 = startCells + (k - 1)*baseC;

            for(unsigned j = 1; j <= cellNums[0]/2; j++){

                unsigned j1 = (j - 1)*sideP,
                         j2 = j1 + sideP;

                this->addFace(k1 + j1, k2 + j1, k2 + j2, k1 + j2);
                this->addOwner(k3 + j1 + 1);
            }
        }
        nfaces+= cellNums[0]*cellNums[1]/2;
    }

    this->boundaries.push_back(nfaces);


    // right boundary
    startPoints = 0;
    startCells = 0;
    nfaces = 0;
    cellNums = ArrUnsgn(CELL(1));

    for(unsigned layer = 1; layer <= this->shape.getNumberOfLayers(); layer++) {

        if(layer > 1) {

            startPoints+= baseP*cellNums[1];
            startCells+= baseC*cellNums[1];
            cellNums = ArrUnsgn(CELL(layer));
        }

        for(unsigned k = 1; k <= cellNums[1]; k++) {

            unsigned k1 = startPoints + (k - 1)*baseP,
                     k2 = k1 + baseP,
                     k3 = startCells + (k - 1)*baseC;

            for(unsigned j = cellNums[0]/2 + 1; j <= cellNums[0]; j++){

                unsigned j1 = (j - 1)*sideP,
                         j2 = (j == cellNums[0]?0:(j1 + sideP));

                this->addFace(k1 + j1, k2 + j1, k2 + j2, k1 + j2);
                this->addOwner(k3 + j1 + 1);
            }
        }
        nfaces+= cellNums[0]*cellNums[1]/2;
    }

    this->boundaries.push_back(nfaces);
}
