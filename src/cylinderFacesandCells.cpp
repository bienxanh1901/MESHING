#include "../include/Mesh.h"

void Mesh::baseFacesandCells(){
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned outerPoints = NODE(0)*sidePoints;
    unsigned base = outerPoints + pow(edgePoints,2);
    unsigned baseC = outerPoints + pow(edgePoints - 1,2);
    unsigned j1, j2, i1, i2;

    // faces and cells of outer circular
    for(unsigned j = 0; j < NODE(0); j++) {

        j1 = j*sidePoints;
        j2 = (j+1)*sidePoints;
        if(j == NODE(0) -1) j2 = 0;

        for(unsigned i = 1; i < sidePoints; i++) {
            i1 = i - 1;

            this-> addCell(j1 + i1, j1 + i, j2 + i, j2 + i1,
                           base + j1 + i1, base + j1 + i, base + j2 + i, base + j2 + i1);
            this->addFace(j1 + i, j2 + i, base + j2 + i, base + j1 + i);
            this->addOwner(this->numberOfCells);
            this->addNeighbor(this->numberOfCells + 1);

            if(j == 0) {
                this->addFace(i1, i, base + i, base + i1);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(outerPoints - sidePoints + this->numberOfCells);
            }

            if(j < NODE(0) -1) {
                this->addFace(j2 + i1, base + j2 + i1, base + j2 + i, j2 + i);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(this->numberOfCells + sidePoints);
            }

            if(NODE(1) > 1) {
                this->addFace(base + j1 + i1, base + j1 + i, base + j2 + i, base + j2 + i1);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(baseC + this->numberOfCells);
            }
        }

        j1 = (j + 1)*sidePoints - 1;
        j2 = (j + 2)*sidePoints - 1;
        if(j == NODE(0) - 1) j2 = sidePoints - 1;

        this->findPointsconnected2D(j, i1, i2);

        this-> addCell(j1, i1, i2, j2,
                           base + j1, base + i1, base + i2, base + j2);

        this->addFace(i1, i2, base + i2, base + i1);
        this->addOwner(this->numberOfCells);
        this->addNeighbor(i1 + 1);

        if(j == 0) {
            this->addFace(j1, i1, base + i1, base + j1);
            this->addOwner(this->numberOfCells);
            this->addNeighbor(outerPoints);
        }

        if(j < NODE(0) -1) {
            this->addFace(j2, base + j2, base + i2, i2);
            this->addOwner(this->numberOfCells);
            this->addNeighbor(this->numberOfCells + 1);
        }

        if(NODE(1) > 1) {
            this->addFace(base + j1, base + i1, base + i2, base + j2);
            this->addOwner(this->numberOfCells);
            this->addNeighbor(baseC + this->numberOfCells);
        }
    }

    // faces and cells of inner rectangular
    for(unsigned j = 1; j < edgePoints; j++) {
        j1 = outerPoints + (j-1)*edgePoints;
        j2 = outerPoints + j*edgePoints;

        for(unsigned i = 1; i < edgePoints; i++){
            i1 = i - 1;

            this-> addCell(j1 + i1, j2 + i1, j2 + i, j1 + i,
                           base + j1 + i1, base + j2 + i1, base + j2 + i, base + j1 + i);

            if(i < edgePoints - 1) {
                this->addFace(j1 + i, base + j1 + i, base + j2 + i, j2 + i);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(this->numberOfCells + 1);
            }

            if(j < edgePoints - 1) {
                this->addFace(j2 + i1, j2 + i, base + j2 + i, base + j2 + i1);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(this->numberOfCells + edgePoints - 1);
            }

            if(NODE(1) > 1) {
                this->addFace(base + j1 + i1, base + j2 + i1, base + j2 + i, base + j1 + i);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(baseC + this->numberOfCells);
            }
        }
    }
}

void Mesh::extrudeFaces() {
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned base = NODE(0)*sidePoints + pow(edgePoints,2);
    unsigned baseF = this->numberOfFaces;
    unsigned baseC = this->numberOfCells;
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

    this->numberOfInternalFaces = this->numberOfFaces;
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
