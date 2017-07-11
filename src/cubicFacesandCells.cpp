#include "../include/Mesh.h"

void Mesh::cubicInternalFacesandCells() {

    unsigned lengthPoints = NODE(0) + 1;
    unsigned widthPoints = NODE(1) + 1;
    unsigned layerPoints = lengthPoints*widthPoints;
    unsigned lengthCells = NODE(0);
    unsigned layerCells = NODE(1)*lengthCells;

    unsigned k1, k2, j1, j2, i1;

    for(unsigned k = 1; k <= NODE(2); k++) {
        k1 = (k - 1)*layerPoints;
        k2 = k*layerPoints;

        for(unsigned j = 1; j <= NODE(1); j++) {
            j1 = (j - 1)*lengthPoints;
            j2 = j*lengthPoints;

            for(unsigned i = 1; i <= NODE(0); i++) {
                i1 = i - 1;

                this->addCell(k1 + j1 + i1, k1 + j1 + i, k1 + j2 + i, k1 + j2 + i1,
                              k2 + j1 + i1, k2 + j1 + i, k2 + j2 + i, k2 + j2 + i1);

                if(i < NODE(0)) {
                    this->addFace(k1 + j1 + i, k1 + j2 + i, k2 + j2 + i, k2 + j1 + i);
                    this->addOwner(this->numberOfCells);
                    this->addNeighbor(this->numberOfCells + 1);
                }

                if(j < NODE(1)) {
                    this->addFace(k1 + j2 + i1, k2 + j2 + i1, k2 + j2 + i, k1 + j2 + i);
                    this->addOwner(this->numberOfCells);
                    this->addNeighbor(this->numberOfCells + lengthCells);
                }

                if(k < NODE(2)) {
                    this->addFace(k1 + j1 + i1, k1 + j1 + i, k1 + j2 + i, k1 + j2 + i1);
                    this->addOwner(this->numberOfCells);
                    this->addNeighbor(this->numberOfCells + layerCells);
                }
            }
        }
    }

    this->numberOfInternalFaces = this->numberOfFaces;
}
