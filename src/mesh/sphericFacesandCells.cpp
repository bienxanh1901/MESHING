#include "../../include/Mesh.h"

void Mesh::leftRightBotTopPartsCells() {

    arrUnsgn cellNums(CELL(1));
    unsigned sideP = cellNums[0]/8,
             edgeC = cellNums[0]/4,
             edgeP = edgeC + 1,
             layerP = sideP*edgeP,
             layerC = sideP*edgeC,
             frontC = (edgeC - 2)*(edgeC - 2)*sideP + 4*(edgeC - 1)*sideP,
             baseC  = layerC*cellNums[0],
             baseC2  = baseC + frontC ,
             i3 = baseC,
             i4 = baseC2 + 4*(edgeC - 1)*sideP;

    for(unsigned i = 0; i < cellNums[0]; i++) {

        unsigned i1 = i*layerP, i2 = (i == (cellNums[0] - 1)?0:i1 + layerP);

        // for cells connection with front
        if(i%edgeC != 0) i3+= sideP;
        if(i == cellNums[0] - 1) i3 = baseC;

        // for cells connection with rear
        if(i == 1) i4 += 4*(edgeC - 1)*sideP;
        if(i%edgeC != 0) i4-= sideP;
        if(i == 0) i4 = baseC2;

        for(unsigned j = 0; j < edgeP - 1; j++) {

            unsigned j1 = j*sideP, j2 = j1 + sideP;

            for(unsigned k = 1, k1 = 0; k < sideP; k++, k1++) {


                this->addCell(i1 + j1 + k1, i2 + j1 + k1, i2 + j2 + k1, i1 + j2 + k1,
                              i1 + j1 + k, i2 + j1 + k, i2 + j2 + k, i1 + j2 + k);

                this->mark.push_back(1);

                if(i == 0) {

                    this->addFace(i1 + j1 + k1, i1 + j2 + k1, i1 + j2 + k, i1 + j1 + k);
                    this->addOwner(this->meshInfo.numberOfCells);
                    this->addNeighbor(baseC - layerC + j1 + k);

                }

                if(i < cellNums[0] - 1) {

                    this->addFace(i2 + j1 + k1, i2 + j1 + k, i2 + j2 + k, i2 + j2 + k1);
                    this->addOwner(this->meshInfo.numberOfCells);
                    this->addNeighbor(this->meshInfo.numberOfCells + layerC);

                }

                if(j == 0) {

                    this->addFace(i1 + j1 + k1, i1 + j1 + k, i2 + j1 + k, i2 + j1 + k1);
                    this->addOwner(this->meshInfo.numberOfCells);
                    this->addNeighbor(i3 + k);

                }

                this->addFace(i1 + j2 + k1, i2 + j2 + k1, i2 + j2 + k, i1 + j2 + k);
                this->addOwner(this->meshInfo.numberOfCells);
                if(j == edgeP - 2) this->addNeighbor(i4 + k);
                else this->addNeighbor(this->meshInfo.numberOfCells + sideP);

                this->addFace(i1 + j1 + k, i1 + j2 + k, i2 + j2 + k, i2 + j1 + k);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(this->meshInfo.numberOfCells + 1);
            }

            //connection with cubic
            j1 = (j + 1)*sideP - 1;
            j2 = j1 + sideP;

            unsigned k1, k2, k3;
            this->findPointsconnected3D(i, j, k1, k2, k3);

            this->addCell(i1 + j1, i2 + j1, i2 + j2, i1 + j2,
                          k1, k2, k2 + 1, k1 + 1);

            this->mark.push_back(1);

            if(i == 0) {

                this->addFace(i1 + j1, i1 + j2, k1 + 1, k1);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(baseC - layerC + j1 + 1);

            }

            if(i < cellNums[0] - 1) {

                this->addFace(i2 + j1, k2, k2 + 1, i2 + j2);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(this->meshInfo.numberOfCells + layerC);

            }

            if(j == 0) {

                this->addFace(i1 + j1, k1, k2, i2 + j1);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(i3 + sideP);

            }

            this->addFace(i1 + j2, i2 + j2, k2 + 1, k1 + 1);
            this->addOwner(this->meshInfo.numberOfCells);

            if(j == edgeP - 2) this->addNeighbor(i4 + sideP);
            else this->addNeighbor(this->meshInfo.numberOfCells + sideP);

            this->addFace(k1, k1 + 1, k2 + 1, k2);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(k3);
        }
    }
}


void Mesh::frontPartCells() {

    arrUnsgn cellNums(CELL(1));
    unsigned sideP = cellNums[0]/8,
             edgeC = cellNums[0]/4,
             edgeP = edgeC + 1,
             layerP = edgeP*edgeP,
             layerC = sideP*edgeC,
             baseP = cellNums[0]*sideP*edgeP,
             outerP= baseP + 2*(edgeP - 2)*(edgeP - 2)*sideP,
             outerC = layerC*cellNums[0] + 2*((edgeC - 2)*(edgeC - 2)*sideP + 4*(edgeC - 1)*sideP);


    this->sphericFrontConnectivity();

    for(unsigned i = 1; i < edgeP - 2; i++) {

        unsigned i1 = baseP + (i - 1)*(edgeP - 2)*sideP, i2 = i1 + (edgeP - 2)*sideP;

        for(unsigned j = 1; j < edgeP - 2; j++) {

            unsigned j1 = (j - 1)*sideP, j2 = j1 + sideP;

            for(unsigned k = 1, k1 = 0; k < sideP; k++, k1++) {

                this->addCell(i1 + j1 + k1, i2 + j1 + k1, i2 + j2 + k1, i1 + j2 + k1,
                              i1 + j1 + k, i2 + j1 + k, i2 + j2 + k, i1 + j2 + k);

                this->mark.push_back(1);

                if(i < edgeP - 3) {

                    this->addFace(i2 + j1 + k1, i2 + j1 + k, i2 + j2 + k, i2 + j2 + k1);
                    this->addOwner(this->meshInfo.numberOfCells);
                    this->addNeighbor(this->meshInfo.numberOfCells + (edgeP - 3)*sideP);

                }

                if(j < edgeP - 3) {

                    this->addFace(i1 + j2 + k1, i2 + j2 + k1, i2 + j2 + k, i1 + j2 + k);
                    this->addOwner(this->meshInfo.numberOfCells);
                    this->addNeighbor(this->meshInfo.numberOfCells + sideP);

                }

                this->addFace(i1 + j1 + k, i1 + j2 + k, i2 + j2 + k, i2 + j1 + k);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(this->meshInfo.numberOfCells + 1);
            }

            //connection with cubic
            j1 = j*sideP - 1;
            j2 = j1 + sideP;
            unsigned k1 = outerP + j*edgeP + i*layerP,
                     k2 = k1 + layerP,
                     k3 = outerC + i*layerC + j*edgeC + 1;

            this->addCell(i1 + j1, i2 + j1, i2 + j2, i1 + j2,
                          k1, k2, k2 + edgeP, k1 + edgeP);

            this->mark.push_back(1);

            if(i < edgeP - 3) {

                this->addFace(i2 + j1, k2, k2 + edgeP, i2 + j2);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(this->meshInfo.numberOfCells + (edgeP - 3)*sideP);

            }

            if(j < edgeP - 3) {

                this->addFace(i1 + j2, i2 + j2, k2 + edgeP, k1 + edgeP);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(this->meshInfo.numberOfCells + sideP);

            }

            this->addFace(k1, k2, k2 + edgeP, k1 + edgeP);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(k3);
        }
    }
}

void Mesh::rearPartCells() {

    arrUnsgn cellNums(CELL(1));
    unsigned sideP = cellNums[0]/8,
             edgeC = cellNums[0]/4,
             edgeP = edgeC + 1,
             layerP = edgeP*edgeP,
             layerC = sideP*edgeC,
             baseP = cellNums[0]*sideP*edgeP + (edgeP - 2)*(edgeP - 2)*sideP,
             outerP= baseP + (edgeP - 2)*(edgeP - 2)*sideP,
             outerC = layerC*cellNums[0] + 2*((edgeC - 2)*(edgeC - 2)*sideP + 4*(edgeC - 1)*sideP);

    this->sphericRearConnectivity();

    for(unsigned i = 1; i < edgeP - 2; i++) {

        unsigned i1 = baseP + (i - 1)*(edgeP - 2)*sideP, i2 = i1 + (edgeP - 2)*sideP;

        for(unsigned j = 1; j < edgeP - 2; j++) {

            unsigned j1 = (j - 1)*sideP, j2 = j1 + sideP;

            for(unsigned k = 1, k1 = 0; k < sideP; k++, k1++) {

                this->addCell(i1 + j1 + k1, i2 + j1 + k1, i2 + j2 + k1, i1 + j2 + k1,
                              i1 + j1 + k, i2 + j1 + k, i2 + j2 + k, i1 + j2 + k);

                this->mark.push_back(1);

                if(i < edgeP - 3) {

                    this->addFace(i2 + j1 + k1, i2 + j1 + k, i2 + j2 + k, i2 + j2 + k1);
                    this->addOwner(this->meshInfo.numberOfCells);
                    this->addNeighbor(this->meshInfo.numberOfCells + (edgeP - 3)*sideP);
                }

                if(j < edgeP - 3) {
                    this->addFace(i1 + j2 + k1, i2 + j2 + k1, i2 + j2 + k, i1 + j2 + k);
                    this->addOwner(this->meshInfo.numberOfCells);
                    this->addNeighbor(this->meshInfo.numberOfCells + sideP);
                }

                this->addFace(i1 + j1 + k, i1 + j2 + k, i2 + j2 + k, i2 + j1 + k);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(this->meshInfo.numberOfCells + 1);
            }

            //connection with cubic
            j1 = j*sideP - 1;
            j2 = j1 + sideP;
            unsigned k1 = outerP + j*layerP + (i + 1)*edgeP - 1,
                     k2 = k1 + layerP,
                     k3 = outerC + j*layerC + (i + 1)*edgeC;

            this->addCell(i1 + j1, i2 + j1, i2 + j2, i1 + j2,
                          k1, k1 + edgeP, k2 + edgeP, k2);

            this->mark.push_back(1);

            if(i < edgeP - 3) {

                this->addFace(i2 + j1, k1 + edgeP, k1 + edgeP, i2 + j2);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(this->meshInfo.numberOfCells + (edgeP - 3)*sideP);

            }

            if(j < edgeP - 3) {

                this->addFace(i1 + j2, i2 + j2, k2 + edgeP, k2);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(this->meshInfo.numberOfCells + sideP);

            }

            this->addFace(k1, k2, k2 + edgeP, k1 + edgeP);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(k3);
        }
    }
}

void Mesh::cubicPartCells() {

    arrUnsgn cellNums(CELL(1));
    unsigned edgeC = cellNums[0]/4,
             edgeP = edgeC + 1,
             layerP = edgeP*edgeP,
             layerC = edgeC*edgeC,
             outerP = cellNums[0]*cellNums[0]*edgeP/8 + 2*(edgeP - 2)*(edgeP - 2)*cellNums[0]/8;

    for(unsigned k = 1; k < edgeP; k++) {

        unsigned k1 = outerP + (k - 1)*layerP, k2 = k1 + layerP;

        for(unsigned i = 1; i < edgeP; i++) {

            unsigned i1 = (i - 1)*edgeP, i2 = i1 + edgeP;

            for(unsigned j = 1, j1 = 0; j < edgeP; j++, j1++) {

                this->addCell(i1 + j1 + k1, i2 + j1 + k1, i2 + j + k1, i1 + j + k1,
                          i1 + j1 + k2, i2 + j1 + k2, i2 + j + k2, i1 + j + k2);

                this->mark.push_back(1);

                if(i < edgeC) {

                    this->addFace(k1 + j1 + i2, k2 + j1 + i2, k2 + j + i2, k1 + j + i2);
                    this->addOwner(this->meshInfo.numberOfCells);
                    this->addNeighbor(this->meshInfo.numberOfCells + edgeC);

                }

                if(j < edgeC) {

                    this->addFace(k1 + j + i1, k1 + j + i2, k2 + j + i2, k2 + j + i1);
                    this->addOwner(this->meshInfo.numberOfCells);
                    this->addNeighbor(this->meshInfo.numberOfCells + 1);

                }

                if(k < edgeC) {

                    this->addFace(k2 + j1 + i1, k2 + j + i1, k2 + j + i2, k2 + j1 + i2);
                    this->addOwner(this->meshInfo.numberOfCells);
                    this->addNeighbor(this->meshInfo.numberOfCells + layerC);

                }
            }
        }
    }
}
