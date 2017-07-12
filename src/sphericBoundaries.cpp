#include "../include/Mesh.h"

void Mesh::sphericTopBoundary() {

    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned edgeCells = NODE(0)/4;
    unsigned layer = sidePoints*edgePoints;
    unsigned layerC = sidePoints*edgeCells;
    unsigned i1, i2, i3, j1, j2, j3;

    for(unsigned i = 0; i < NODE(0); i++) {

        i1 = i*layer;
        i2 = i1 + layer;
        if(i == NODE(0) - 1) i2 = 0;
        i3 = i*layerC + 1;

        for(unsigned j = 0; j < edgeCells/2; j++) {
            j1 = j*sidePoints;
            j2 = j1 + sidePoints;
            j3 = j*sidePoints;

            this->addFace(i1 + j1, i2 + j1, i2 + j2, i1 + j2);
            this->addOwner(i3 + j3);
        }
    }

    this->sphericFrontBoundary();
    this->boundaries.push_back(this->meshInfo.numberOfFaces - this->meshInfo.numberOfInternalFaces);

}

void Mesh::sphericBotBoundary() {

    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned edgeCells = NODE(0)/4;
    unsigned layer = sidePoints*edgePoints;
    unsigned layerC = sidePoints*edgeCells;
    unsigned i1, i2, i3, j1, j2, j3;

    for(unsigned i = 0; i < NODE(0); i++) {

        i1 = i*layer;
        i2 = i1 + layer;
        if(i == NODE(0) - 1) i2 = 0;
        i3 = i*layerC + 1;

        for(unsigned j = edgeCells/2; j < edgeCells; j++) {
            j1 = j*sidePoints;
            j2 = j1 + sidePoints;
            j3 = j*sidePoints;

            this->addFace(i1 + j1, i2 + j1, i2 + j2, i1 + j2);
            this->addOwner(i3 + j3);
        }
    }

    this->sphericRearBoundary();
    this->boundaries.push_back((this->meshInfo.numberOfFaces - this->meshInfo.numberOfInternalFaces)/2);

}


void Mesh::sphericFrontBoundary() {

    unsigned sidePoints = NODE(0)/8;
    unsigned edgeCells = NODE(0)/4;
    unsigned frontC = (edgeCells - 2)*(edgeCells - 2)*sidePoints + 4*(edgeCells - 1)*sidePoints;
    unsigned baseC  = sidePoints*edgeCells*NODE(0);

    containerIDs pointCells;

    for(unsigned i = baseC; i < baseC + frontC; i+= sidePoints) {

        pointCells = this->cells[i].getPointsIDList();
        this->addFace(pointCells[0] - 1, pointCells[1] - 1, pointCells[2] - 1, pointCells[3] - 1);
        this->addOwner(i + 1);

    }

}


void Mesh::sphericRearBoundary() {

    unsigned sidePoints = NODE(0)/8;
    unsigned edgeCells = NODE(0)/4;
    unsigned frontC = (edgeCells - 2)*(edgeCells - 2)*sidePoints + 4*(edgeCells - 1)*sidePoints;
    unsigned baseC  = sidePoints*edgeCells*NODE(0) + frontC;

    containerIDs pointCells;

    for(unsigned i = baseC; i < baseC + frontC; i+= sidePoints) {

        pointCells = this->cells[i].getPointsIDList();
        this->addFace(pointCells[0] - 1, pointCells[1] - 1, pointCells[2] - 1, pointCells[3] - 1);
        this->addOwner(i + 1);

    }

}
