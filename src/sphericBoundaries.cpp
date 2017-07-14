#include "../include/Mesh.h"

void Mesh::sphericTopBoundary() {

    arrUnsgn cellNums(this->shape.getCellNumbersOfLayer(1));
    unsigned sideP = cellNums[0]/8;
    unsigned edgeC = cellNums[0]/4;
    unsigned layerP = sideP*(edgeC + 1);
    unsigned layerC = sideP*edgeC;

    for(unsigned i = 0; i < cellNums[0]; i++) {

        unsigned i1 = i*layerP;
        unsigned i2 = i1 + layerP;
        if(i == cellNums[0] - 1) i2 = 0;
        unsigned i3 = i*layerC + 1;

        for(unsigned j = 0; j < edgeC/2; j++) {

            unsigned j1 = j*sideP;
            unsigned j2 = j1 + sideP;
            unsigned j3 = j*sideP;

            this->addFace(i1 + j1, i2 + j1, i2 + j2, i1 + j2);
            this->addOwner(i3 + j3);
        }
    }

    this->sphericFrontBoundary();
    this->boundaries.push_back(this->meshInfo.numberOfFaces - this->meshInfo.numberOfInternalFaces);

}

void Mesh::sphericBotBoundary() {

    arrUnsgn cellNums(this->shape.getCellNumbersOfLayer(1));
    unsigned sideP = cellNums[0]/8;
    unsigned edgeC = cellNums[0]/4;
    unsigned layerP = sideP*(edgeC + 1);
    unsigned layerC = sideP*edgeC;

    for(unsigned i = 0; i < cellNums[0]; i++) {

        unsigned i1 = i*layerP;
        unsigned i2 = i1 + layerP;
        if(i == cellNums[0] - 1) i2 = 0;
        unsigned i3 = i*layerC + 1;

        for(unsigned j = edgeC/2; j < edgeC; j++) {

            unsigned j1 = j*sideP;
            unsigned j2 = j1 + sideP;
            unsigned j3 = j*sideP;

            this->addFace(i1 + j1, i2 + j1, i2 + j2, i1 + j2);
            this->addOwner(i3 + j3);
        }
    }

    this->sphericRearBoundary();
    this->boundaries.push_back((this->meshInfo.numberOfFaces - this->meshInfo.numberOfInternalFaces)/2);

}


void Mesh::sphericFrontBoundary() {

    arrUnsgn cellNums(this->shape.getCellNumbersOfLayer(1));
    unsigned sideP = cellNums[0]/8;
    unsigned frontC = pow(cellNums[0]/4 - 2, 2) + 4*(cellNums[0]/4 - 1)*sideP;
    unsigned baseC  = sideP*cellNums[0]/4*cellNums[0];

    containerIDs pointCells;

    for(unsigned i = baseC; i < baseC + frontC; i+= sideP) {

        pointCells = this->cells[i].getPointsIDList();
        this->addFace(pointCells[0] - 1, pointCells[1] - 1, pointCells[2] - 1, pointCells[3] - 1);
        this->addOwner(i + 1);

    }

}


void Mesh::sphericRearBoundary() {

    arrUnsgn cellNums(this->shape.getCellNumbersOfLayer(1));
    unsigned sideP = cellNums[0]/8;
    unsigned frontC = pow(cellNums[0]/4 - 2, 2) + 4*(cellNums[0]/4 - 1)*sideP;
    unsigned baseC  = sideP*cellNums[0]/4*cellNums[0] + frontC;

    containerIDs pointCells;

    for(unsigned i = baseC; i < baseC + frontC; i+= sideP) {

        pointCells = this->cells[i].getPointsIDList();
        this->addFace(pointCells[0] - 1, pointCells[1] - 1, pointCells[2] - 1, pointCells[3] - 1);
        this->addOwner(i + 1);

    }

}
