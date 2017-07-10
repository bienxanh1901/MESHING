#include "../include/Mesh.h"

void Mesh::leftRightBotTopPartsCells() {
    unsigned sidePoints = NODE(0)/8;
    unsigned edgeCells = NODE(0)/4;
    unsigned edgePoints = edgeCells + 1;
    unsigned layer = sidePoints*edgePoints;
    unsigned layerC = sidePoints*edgeCells;
    unsigned frontC = (edgeCells - 2)*(edgeCells - 2)*sidePoints + 4*(edgeCells - 1)*sidePoints;
    unsigned baseC  = layerC*NODE(0);
    unsigned baseC2  = baseC + frontC ;
    unsigned i1, i2, i3, i4, j1, j2, k1, k2, k3;

    i3 = baseC;
    i4 = baseC2 + 4*(edgeCells - 1)*sidePoints;
    for(unsigned i = 0; i < NODE(0); i++) {

        i1 = i*layer;
        i2 = i1 + layer;
        if(i == NODE(0) - 1) i2 = 0;

        // for cells connection with front
        if(i%edgeCells != 0) i3+= sidePoints;
        if(i == NODE(0) - 1) i3 = baseC;

        // for cells connection with rear
        if(i == 1) i4 += 4*(edgeCells - 1)*sidePoints;
        if(i%edgeCells != 0) i4-= sidePoints;
        if(i == 0) i4 = baseC2;

        for(unsigned j = 0; j < edgePoints - 1; j++) {
            j1 = j*sidePoints;
            j2 = j1 + sidePoints;


            for(unsigned k = 1; k < sidePoints; k++) {
                k1 = k - 1;
                this->addCell(i1 + j1 + k1, i2 + j1 + k1, i2 + j2 + k1, i1 + j2 + k1,
                              i1 + j1 + k, i2 + j1 + k, i2 + j2 + k, i1 + j2 + k);
                if(i == 0) {
                    this->addFace(i1 + j1 + k1, i1 + j2 + k1, i1 + j2 + k, i1 + j1 + k);
                    this->addOwner(this->numberOfCells);
                    this->addNeighbor(baseC - layerC + j1 + k);
                }

                if(i < NODE(0) - 1) {
                    this->addFace(i2 + j1 + k1, i2 + j1 + k, i2 + j2 + k, i2 + j2 + k1);
                    this->addOwner(this->numberOfCells);
                    this->addNeighbor(this->numberOfCells + layerC);
                }

                if(j == 0) {
                    this->addFace(i1 + j1 + k1, i1 + j1 + k, i2 + j1 + k, i2 + j1 + k1);
                    this->addOwner(this->numberOfCells);
                    this->addNeighbor(i3 + k);
                }

                this->addFace(i1 + j2 + k1, i2 + j2 + k1, i2 + j2 + k, i1 + j2 + k);
                this->addOwner(this->numberOfCells);
                if(j == edgePoints - 2) this->addNeighbor(i4 + k);
                else this->addNeighbor(this->numberOfCells + sidePoints);

                this->addFace(i1 + j1 + k, i1 + j2 + k, i2 + j2 + k, i2 + j1 + k);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(this->numberOfCells + 1);
            }

            //connection with cubic
            j1 = (j + 1)*sidePoints - 1;
            j2 = j1 + sidePoints;

            this->findPointsconnected3D(i, j, k1, k2, k3);

            this->addCell(i1 + j1, i2 + j1, i2 + j2, i1 + j2,
                          k1, k2, k2 + 1, k1 + 1);
            if(i == 0) {
                this->addFace(i1 + j1, i1 + j2, k1 + 1, k1);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(baseC - layerC + j1 + 1);
            }

            if(i < NODE(0) - 1) {
                this->addFace(i2 + j1, k2, k2 + 1, i2 + j2);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(this->numberOfCells + layerC);
            }

            if(j == 0) {
                this->addFace(i1 + j1, k1, k2, i2 + j1);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(i3 + sidePoints);
            }

            this->addFace(i1 + j2, i2 + j2, k2 + 1, k1 + 1);
            this->addOwner(this->numberOfCells);
            if(j == edgePoints - 2) this->addNeighbor(i4 + sidePoints);
            else this->addNeighbor(this->numberOfCells + sidePoints);

            this->addFace(k1, k1 + 1, k2 + 1, k2);
            this->addOwner(this->numberOfCells);
            this->addNeighbor(k3);
        }
    }
}

void Mesh::frontPartCells() {
    unsigned sidePoints = NODE(0)/8;
    unsigned edgeCells = NODE(0)/4;
    unsigned edgePoints = edgeCells + 1;
    unsigned layer = sidePoints*edgePoints;
    unsigned layerC = edgePoints*edgePoints;
    unsigned layerCells = edgeCells*edgeCells;
    unsigned base = NODE(0)*layer;
    unsigned outerPoints= base + 2*(edgePoints - 2)*(edgePoints - 2)*sidePoints;
    unsigned frontC = (edgeCells - 2)*(edgeCells - 2)*sidePoints + 4*(edgeCells - 1)*sidePoints;
    unsigned baseC  = sidePoints*edgeCells*NODE(0);
    unsigned outerCells = baseC + 2*frontC;
    unsigned i1, i2, j1, j2, k1, k2, k3;


    this->sphericFrontConnectivity();

    for(unsigned i = 1; i < edgePoints - 2; i++) {
        i1 = base + (i - 1)*(edgePoints - 2)*sidePoints;
        i2 = i1 + (edgePoints - 2)*sidePoints;
        for(unsigned j = 1; j < edgePoints - 2; j++) {
            j1 = (j - 1)*sidePoints;
            j2 = j1 + sidePoints;

            for(unsigned k = 1; k < sidePoints; k++) {
                k1 = k - 1;

                this->addCell(i1 + j1 + k1, i2 + j1 + k1, i2 + j2 + k1, i1 + j2 + k1,
                              i1 + j1 + k, i2 + j1 + k, i2 + j2 + k, i1 + j2 + k);

                if(i < edgePoints - 3) {
                    this->addFace(i2 + j1 + k1, i2 + j1 + k, i2 + j2 + k, i2 + j2 + k1);
                    this->addOwner(this->numberOfCells);
                    this->addNeighbor(this->numberOfCells + (edgePoints - 3)*sidePoints);
                }

                if(j < edgePoints - 3) {
                    this->addFace(i1 + j2 + k1, i2 + j2 + k1, i2 + j2 + k, i1 + j2 + k);
                    this->addOwner(this->numberOfCells);
                    this->addNeighbor(this->numberOfCells + sidePoints);
                }

                this->addFace(i1 + j1 + k, i1 + j2 + k, i2 + j2 + k, i2 + j1 + k);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(numberOfCells + 1);
            }

            //connection with cubic
            j1 = j*sidePoints - 1;
            j2 = j1 + sidePoints;
            k1 = outerPoints + j*edgePoints + i*layerC;
            k2 = k1 + layerC;
            k3 = outerCells + i*layerCells + j*edgeCells + 1;

            this->addCell(i1 + j1, i2 + j1, i2 + j2, i1 + j2,
                          k1, k2, k2 + edgePoints, k1 + edgePoints);

            if(i < edgePoints - 3) {
                this->addFace(i2 + j1, k2, k2 + edgePoints, i2 + j2);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(this->numberOfCells + (edgePoints - 3)*sidePoints);
            }

            if(j < edgePoints - 3) {
                this->addFace(i1 + j2, i2 + j2, k2 + edgePoints, k1 + edgePoints);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(this->numberOfCells + sidePoints);
            }

            this->addFace(k1, k2, k2 + edgePoints, k1 + edgePoints);
            this->addOwner(this->numberOfCells);
            this->addNeighbor(k3);
        }
    }
}

void Mesh::rearPartCells() {
    unsigned sidePoints = NODE(0)/8;
    unsigned edgeCells = NODE(0)/4;
    unsigned edgePoints = edgeCells + 1;
    unsigned layer = sidePoints*edgePoints;
    unsigned layerC = edgePoints*edgePoints;
    unsigned layerCells = edgeCells*edgeCells;
    unsigned base = NODE(0)*layer + (edgePoints - 2)*(edgePoints - 2)*sidePoints;
    unsigned outerPoints= base + (edgePoints - 2)*(edgePoints - 2)*sidePoints;
    unsigned frontC = (edgeCells - 2)*(edgeCells - 2)*sidePoints + 4*(edgeCells - 1)*sidePoints;
    unsigned baseC  = sidePoints*edgeCells*NODE(0);
    unsigned outerCells = baseC + 2*frontC;
    unsigned i1, i2, j1, j2, k1, k2, k3;


    this->sphericRearConnectivity();

    for(unsigned i = 1; i < edgePoints - 2; i++) {
        i1 = base + (i - 1)*(edgePoints - 2)*sidePoints;
        i2 = i1 + (edgePoints - 2)*sidePoints;
        for(unsigned j = 1; j < edgePoints - 2; j++) {
            j1 = (j - 1)*sidePoints;
            j2 = j1 + sidePoints;

            for(unsigned k = 1; k < sidePoints; k++) {
                k1 = k - 1;

                this->addCell(i1 + j1 + k1, i2 + j1 + k1, i2 + j2 + k1, i1 + j2 + k1,
                              i1 + j1 + k, i2 + j1 + k, i2 + j2 + k, i1 + j2 + k);

                if(i < edgePoints - 3) {
                    this->addFace(i2 + j1 + k1, i2 + j1 + k, i2 + j2 + k, i2 + j2 + k1);
                    this->addOwner(this->numberOfCells);
                    this->addNeighbor(this->numberOfCells + (edgePoints - 3)*sidePoints);
                }

                if(j < edgePoints - 3) {
                    this->addFace(i1 + j2 + k1, i2 + j2 + k1, i2 + j2 + k, i1 + j2 + k);
                    this->addOwner(this->numberOfCells);
                    this->addNeighbor(this->numberOfCells + sidePoints);
                }

                this->addFace(i1 + j1 + k, i1 + j2 + k, i2 + j2 + k, i2 + j1 + k);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(numberOfCells + 1);
            }

            //connection with cubic
            j1 = j*sidePoints - 1;
            j2 = j1 + sidePoints;
            k1 = outerPoints + j*layerC + (i + 1)*edgePoints - 1;
            k2 = k1 + layerC;
            k3 = outerCells + j*layerCells + (i + 1)*edgeCells;

            this->addCell(i1 + j1, i2 + j1, i2 + j2, i1 + j2,
                          k1, k1 + edgePoints, k2 + edgePoints, k2);

            if(i < edgePoints - 3) {
                this->addFace(i2 + j1, k1 + edgePoints, k1 + edgePoints, i2 + j2);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(this->numberOfCells + (edgePoints - 3)*sidePoints);
            }

            if(j < edgePoints - 3) {
                this->addFace(i1 + j2, i2 + j2, k2 + edgePoints, k2);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(this->numberOfCells + sidePoints);
            }

            this->addFace(k1, k2, k2 + edgePoints, k1 + edgePoints);
            this->addOwner(this->numberOfCells);
            this->addNeighbor(k3);
        }
    }
}

void Mesh::cubicPartCells() {
    unsigned sidePoints = NODE(0)/8;
    unsigned edgeCells = NODE(0)/4;
    unsigned edgePoints = edgeCells + 1;
    unsigned layer = sidePoints*edgePoints;
    unsigned layerC= edgePoints*edgePoints;
    unsigned layerCells = edgeCells*edgeCells;
    unsigned outerPoints= NODE(0)*layer + 2*(edgePoints - 2)*(edgePoints - 2)*sidePoints;
    unsigned i1, i2, j1, k1, k2;

    containerPoints pointsList;

    for(unsigned k = 1; k < edgePoints; k++) {
        k1 = outerPoints + (k - 1)*layerC;
        k2 = k1 + layerC;
        for(unsigned i = 1; i < edgePoints; i++) {
            i1 = (i - 1)*edgePoints;
            i2 = i1 + edgePoints;
            for(unsigned j = 1; j < edgePoints; j++) {
                j1 = j - 1;

                this->addCell(i1 + j1 + k1, i2 + j1 + k1, i2 + j + k1, i1 + j + k1,
                          i1 + j1 + k2, i2 + j1 + k2, i2 + j + k2, i1 + j + k2);

                if(i < edgeCells) {
                    this->addFace(k1 + j1 + i2, k2 + j1 + i2, k2 + j + i2, k1 + j + i2);
                    this->addOwner(this->numberOfCells);
                    this->addNeighbor(this->numberOfCells + edgeCells);
                }

                if(j < edgeCells) {
                    this->addFace(k1 + j + i1, k1 + j + i2, k2 + j + i2, k2 + j + i1);
                    this->addOwner(this->numberOfCells);
                    this->addNeighbor(this->numberOfCells + 1);
                }

                if(k < edgeCells) {
                    this->addFace(k2 + j1 + i1, k2 + j + i1, k2 + j + i2, k2 + j1 + i2);
                    this->addOwner(this->numberOfCells);
                    this->addNeighbor(this->numberOfCells + layerCells);
                }
            }
        }
    }
}
