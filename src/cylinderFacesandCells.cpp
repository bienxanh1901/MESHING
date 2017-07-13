#include "../include/Mesh.h"

void Mesh::baseFacesandCells(){
    arrUnsgn cellNums(this->shape.getCellNumbersOfLayer(1));
    unsigned sidePoints = cellNums[0]/8;
    unsigned edgePoints = cellNums[0]/4 + 1;
    unsigned outerPoints = cellNums[0]*sidePoints;
    unsigned base = outerPoints + pow(edgePoints,2);
    unsigned basePoints = outerPoints + pow(edgePoints,2);
    unsigned baseCells = outerPoints + pow(edgePoints - 1,2);
    unsigned j1, j2, i1, i2;

    // faces and cells of outer circular
    for(unsigned j = 0; j < cellNums[0]; j++) {

        j1 = j*sidePoints;
        j2 = j1 + sidePoints;
        if(j == cellNums[0] -1) j2 = 0;

        for(unsigned i = 1; i < sidePoints; i++) {
            i1 = i - 1;

            this-> addCell(j1 + i1, j1 + i, j2 + i, j2 + i1,
                           basePoints + j1 + i1, basePoints + j1 + i, basePoints + j2 + i, basePoints + j2 + i1);

            this->addFace(j1 + i, j2 + i, basePoints + j2 + i, basePoints + j1 + i);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(this->meshInfo.numberOfCells + 1);

            if(j == 0) {
                this->addFace(i1, i, basePoints + i, basePoints + i1);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(outerPoints - sidePoints + this->meshInfo.numberOfCells);
            }

            if(j < cellNums[0] -1) {
                this->addFace(j2 + i1, basePoints + j2 + i1, basePoints + j2 + i, j2 + i);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(this->meshInfo.numberOfCells + sidePoints);
            }

            if(cellNums[1] > 1) {
                this->addFace(basePoints + j1 + i1, basePoints + j1 + i, basePoints + j2 + i, basePoints + j2 + i1);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(baseCells + this->meshInfo.numberOfCells);
            }
        }

        j1 = (j + 1)*sidePoints - 1;
        j2 = j1 + sidePoints;
        if(j == cellNums[0] - 1) j2 = sidePoints - 1;

        this->findPointsconnected2D(j, i1, i2);

        this-> addCell(j1, i1, i2, j2,
                       basePoints + j1, basePoints + i1, basePoints + i2, basePoints + j2);

        this->addFace(i1, i2, basePoints + i2, basePoints + i1);
        this->addOwner(this->meshInfo.numberOfCells);
        this->addNeighbor(i1 + 1);

        if(j == 0) {
            this->addFace(j1, i1, basePoints + i1, basePoints + j1);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(outerPoints);
        }

        if(j < cellNums[0] -1) {
            this->addFace(j2, basePoints + j2, basePoints + i2, i2);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(this->meshInfo.numberOfCells + 1);
        }

        if(cellNums[1] > 1) {
            this->addFace(basePoints + j1, basePoints + i1, basePoints + i2, basePoints + j2);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(baseCells + this->meshInfo.numberOfCells);
        }
    }

    // faces and cells of inner rectangular
    for(unsigned j = 1; j < edgePoints; j++) {
        j1 = outerPoints + (j-1)*edgePoints;
        j2 = j1 + edgePoints;

        for(unsigned i = 1; i < edgePoints; i++){
            i1 = i - 1;

            this-> addCell(j1 + i1, j2 + i1, j2 + i, j1 + i,
                           basePoints + j1 + i1, basePoints + j2 + i1, basePoints + j2 + i, basePoints + j1 + i);

            if(i < edgePoints - 1) {
                this->addFace(j1 + i, basePoints + j1 + i, basePoints + j2 + i, j2 + i);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(this->meshInfo.numberOfCells + 1);
            }

            if(j < edgePoints - 1) {
                this->addFace(j2 + i1, j2 + i, basePoints + j2 + i, basePoints + j2 + i1);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(this->meshInfo.numberOfCells + edgePoints - 1);
            }

            if(cellNums[1] > 1) {
                this->addFace(basePoints + j1 + i1, basePoints + j2 + i1, basePoints + j2 + i, basePoints + j1 + i);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(baseCells + this->meshInfo.numberOfCells);
            }
        }
    }
}

void Mesh::extrudeFaces() {
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned base = NODE(0)*sidePoints + pow(edgePoints,2);
    unsigned baseF = this->meshInfo.numberOfFaces;
    unsigned baseC = this->meshInfo.numberOfCells;
    unsigned ID;
    containerPoints pointsList, pointFaces;

    for(unsigned k = 1; k < NODE(1); k++) {

        for(unsigned j = 0; j< baseF; j++) {

            pointFaces = this->faces[j].getPointsList();

            for(containerPoints::iterator it = pointFaces.begin(); it != pointFaces.end(); it++) {
                ID = it->getID() + k*base - 1;
                pointsList.push_back(this->points[ID]);
            }

            this->addFace(pointsList);
            this->addOwner(this->owner[j] + k*baseC);
            this->addNeighbor(this->neighbor[j] + k*baseC);
        }
    }

    this->meshInfo.numberOfInternalFaces = this->meshInfo.numberOfFaces;
}

void Mesh::extrudeCells() {
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned outerPoints = NODE(0)*sidePoints;
    unsigned base = NODE(0)*sidePoints + pow(edgePoints,2);
    unsigned baseC = outerPoints + pow(edgePoints - 1,2);
    unsigned ID;
    containerPoints pointsList, pointCells;

    for(unsigned k = 1; k < NODE(1); k++) {
        for(unsigned j = 0; j< baseC; j++) {
            pointCells = this->cells[j].getPointsList();
            for(containerPoints::iterator it = pointCells.begin(); it != pointCells.end(); it++){
                ID = it->getID() + k*base - 1;
                pointsList.push_back(this->points[ID]);
            }
            this->addCell(pointsList);
        }
    }
}
