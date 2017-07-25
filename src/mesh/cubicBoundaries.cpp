#include "../../include/Mesh.h"

void Mesh::cubicBoundaryLeft(){

    ArrUnsgn cellNums(CELL(1));
    unsigned lengthPoints = cellNums[0] + 1,
             widthPoints = cellNums[1] + 1,
             basePoints = lengthPoints*widthPoints,
             baseCells = cellNums[0]*cellNums[1],
             startPoints = 0, startCells = 0, faceCnt = 0;

    for(unsigned layer = 1; layer <= this->shape.getNumberOfLayers(); layer ++) {

        if(layer > 1) {

            startPoints+= basePoints*cellNums[2];
            startCells+= baseCells*cellNums[2];
            cellNums = CELL(layer);
        }

        faceCnt+= cellNums[1]*cellNums[2];


        for(unsigned k = 1; k <= cellNums[2]; k++){

            unsigned k1 = startPoints + (k - 1)*basePoints,
                     k2 = k1 + basePoints,
                     k3 = startCells + (k - 1)*baseCells;

            for(unsigned j = 1; j <= cellNums[1]; j++){

                unsigned j1 = (j - 1)*lengthPoints,
                         j2 = j1 + lengthPoints,
                         j3 = (j - 1)*cellNums[1];

                this->addFace(k1 + j1, k2 + j1, k2 + j2, k1 + j2);
                this->addOwner(k3 + j3 + 1);
            }
        }
    }

    this->boundaries.push_back(faceCnt);

}

void Mesh::cubicBoundaryRight(){

    ArrUnsgn cellNums(CELL(1));
    unsigned lengthPoints = cellNums[0] + 1,
             widthPoints = cellNums[1] + 1,
             basePoints = lengthPoints*widthPoints,
             baseCells = cellNums[0]*cellNums[1],
             startPoints = 0, startCells = 0, faceCnt = 0;

    for(unsigned layer = 1; layer <= this->shape.getNumberOfLayers(); layer ++) {

        if(layer > 1) {

            startPoints+= basePoints*cellNums[2];
            startCells+= baseCells*cellNums[2];
            cellNums = CELL(layer);
        }

        faceCnt+= cellNums[1]*cellNums[2];


        for(unsigned k = 1; k <= cellNums[2]; k++){

            unsigned k1 = startPoints + (k - 1)*basePoints,
                     k2 = k1 + basePoints,
                     k3 = startCells + (k - 1)*baseCells;

            for(unsigned j = 1; j <= cellNums[1]; j++){

                unsigned j1 = j*lengthPoints - 1,
                         j2 = j1 + lengthPoints,
                         j3 = j*cellNums[1];

                this->addFace(k1 + j1, k1 + j2, k2 + j2, k2 + j1);
                this->addOwner(k3 + j3);
            }
        }
    }

    this->boundaries.push_back(faceCnt);

}

void Mesh::cubicBoundaryFront(){

    ArrUnsgn cellNums(CELL(1));
    unsigned lengthPoints = cellNums[0] + 1,
             widthPoints = cellNums[1] + 1,
             basePoints = lengthPoints*widthPoints,
             baseCells = cellNums[0]*cellNums[1],
             startPoints = 0, startCells = 0, faceCnt = 0;

    for(unsigned layer = 1; layer <= this->shape.getNumberOfLayers(); layer ++) {

        if(layer > 1) {

            startPoints+= basePoints*cellNums[2];
            startCells+= baseCells*cellNums[2];
            cellNums = CELL(layer);
        }

        faceCnt+= cellNums[0]*cellNums[2];

        for(unsigned k = 1; k <= cellNums[2]; k++){

            unsigned k1 = startPoints + (k - 1)*basePoints,
                     k2 = k1 + basePoints,
                     k3 = startCells + (k - 1)*baseCells;

            for(unsigned i = 1, i1 = 0; i <= cellNums[0]; i++, i1++){

                this->addFace(k1 + i1, k1 + i, k2 + i, k2 + i1);
                this->addOwner(k3 + i);
            }
        }
    }

    this->boundaries.push_back(faceCnt);

}


void Mesh::cubicBoundaryRear() {

    ArrUnsgn cellNums(CELL(1));
    unsigned lengthPoints = cellNums[0] + 1,
             widthPoints = cellNums[1] + 1,
             basePoints = lengthPoints*widthPoints,
             baseCells = cellNums[0]*cellNums[1],
             startPoints = 0, startCells = 0, faceCnt = 0;

    for(unsigned layer = 1; layer <= this->shape.getNumberOfLayers(); layer ++) {

        if(layer > 1) {

            startPoints+= basePoints*cellNums[2];
            startCells+= baseCells*cellNums[2];
            cellNums = CELL(layer);
        }

        faceCnt+= cellNums[0]*cellNums[2];

        for(unsigned k = 1; k <= cellNums[2]; k++){

            unsigned k1 = startPoints + k*basePoints - lengthPoints,
                     k2 = k1 + basePoints,
                     k3 = startCells + k*baseCells - cellNums[0];

            for(unsigned i = 1, i1 = 0; i <= cellNums[0]; i++, i1++){

                this->addFace(k1 + i1, k2 + i1, k2 + i, k1 + i);
                this->addOwner(k3 + i);
            }
        }
    }

    this->boundaries.push_back(faceCnt);
}

void Mesh::cubicBoundaryBot(){

    ArrUnsgn cellNums(CELL(1));
    unsigned lengthPoints = cellNums[0] + 1,
             baseCells = cellNums[0]*cellNums[1];

    for(unsigned j = 1; j <= cellNums[1]; j++){

        unsigned j1 = (j - 1)*lengthPoints, j2 = j1 + lengthPoints,
                 j3 = (j - 1)*cellNums[1];

        for(unsigned i = 1, i1 = 0; i <= cellNums[0]; i++, i1++){

            this->addFace(j1 + i1, j2 + i1, j2 + i, j1 + i);
            this->addOwner(j3 + i);
        }
    }
    this->boundaries.push_back(baseCells);
}

void Mesh::cubicBoundaryTop(){

    ArrUnsgn cellNums(CELL(1));
    unsigned lengthPoints = cellNums[0] + 1,
             widthPoints = cellNums[1] + 1,
             basePoints = lengthPoints*widthPoints,
             baseCells = cellNums[0]*cellNums[1],
             startPoints = 0, startCells = 0;

    for(unsigned layer = 1; layer <= this->shape.getNumberOfLayers(); layer ++) {

        startPoints+= basePoints*cellNums[2];
        startCells+= baseCells*cellNums[2];
        cellNums = CELL(layer);
    }
    startCells -= baseCells;

    for(unsigned j = 1; j <= cellNums[1]; j++){

        unsigned j1 = startPoints + (j - 1)*lengthPoints,
                 j2 = j1 + lengthPoints,
                 j3 = startCells + (j - 1)*cellNums[1];

        for(unsigned i = 1, i1 = 0; i <= cellNums[0]; i++, i1++){

            this->addFace(j1 + i1, j1 + i, j2 + i, j2 + i1);
            this->addOwner(j3 + i);
        }
    }

    this->boundaries.push_back(baseCells);

}
