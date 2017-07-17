#include "../../include/Mesh.h"

void Mesh::sphericFrontConnectivity() {

    arrUnsgn cellNums(CELL(1));
    unsigned sideP = cellNums[0]/8,
             edgeC = cellNums[0]/4,
             edgeP = edgeC + 1,
             layerP = sideP*edgeP,
             layerP2 = edgeP*edgeP,
             layerC = edgeC*edgeC,
             baseP = cellNums[0]*layerP,
             outerP = baseP + 2*(edgeP - 2)*(edgeP - 2)*sideP,
             frontC = (edgeC - 2)*(edgeC - 2)*sideP + 4*(edgeC - 1)*sideP,
             baseC  = sideP*edgeC*cellNums[0],
             outerC = baseC + 2*frontC,
             innerC = edgeC*edgeC*edgeC;

    // front - top
    for(unsigned j = 1; j < edgeP; j++) {

        unsigned j1 = (j - 1)*layerP, j2 = j1 + layerP,
                 i1, i2, i3;

        if(j == 1) {

            i1 = baseP - layerP;
            i2 = baseP + j - 1;
            i3 = baseC + 4*(edgeC - 1)*sideP - sideP + 1;

        } else if(j == edgeP - 1) {

            i1 = baseP + (j - 2)*sideP;
            i2 = j2 + layerP;
            i3 = baseC + edgeC*sideP + 1;

        } else{

            i1 = baseP + (j - 2)*sideP;
            i2 = i1 + sideP;
            i3 = baseC + 4*(edgeC - 1)*sideP + (j - 2)*sideP + 1;
        }

        for(unsigned k = 1, k1 = 0; k < sideP; k++, k1++) {

            this->addCell(j1 + k1, i1 + k1, i2 + k1, j2 + k1,
                          j1 + k, i1 + k, i2 + k, j2 + k);

            this->mark.push_back(1);

            this->addFace(i1 + k1, i1 + k, i2 + k, i2 + k1);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(i3);

            if(j < edgeC) {

                this->addFace(j2 + k1, i2 + k1, i2 + k, j2 + k);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(this->meshInfo.numberOfCells + sideP);

            }

            this->addFace(j1 + k, j2 + k, i2 + k, i1 + k);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(this->meshInfo.numberOfCells + 1);

        }

        //connection with cubic
        j1 = j1 + sideP - 1;
        j2 = j2 + sideP - 1;
        i1 = i1 + sideP - 1;
        i2 = i2 + sideP - 1;
        i3 = i3 + sideP - 1;
        unsigned k1 = outerP + (j - 1)*edgeP,
                 k2 = k1 + layerP2,
                 k3 = outerC + (j - 1)*edgeC + 1;

        this->addCell(j1, i1, i2, j2,
                      k1, k2, k2 + edgeP, k1 + edgeP);

        this->mark.push_back(1);

        this->addFace(i1, k2, k2 + edgeP, i2);
        this->addOwner(this->meshInfo.numberOfCells);
        this->addNeighbor(i3);

        if(j < edgeC) {

            this->addFace(j2, i2, k2 + edgeP, k1 + edgeP);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(this->meshInfo.numberOfCells + sideP);

        }

        this->addFace(k1, k1 + edgeP, k2 + edgeP, k2);
        this->addOwner(this->meshInfo.numberOfCells);
        this->addNeighbor(k3);
    }

    // front - right
    unsigned base1 = edgeP + edgeP - 2;

    for(unsigned j = edgeP + 1; j <= base1; j++) {

        unsigned j1 = (j - 1)*layerP, j2 = j1 + layerP,
                 i1, i2, i3;

        if(j == base1) {

            i1 = baseP + (j%edgeP)*(edgeP - 2)*sideP - sideP;
            i2 = j2 + layerP;
            i3 = baseC + 2*edgeC*sideP -sideP + 1;

        } else {

            i1 = baseP + (j%edgeP)*(edgeP - 2)*sideP - sideP;
            i2 = i1 + (edgeP - 2)*sideP;
            i3 = baseC + 4*(edgeC - 1)*sideP + (j%edgeP)*(edgeC - 2)*sideP -sideP + 1;

        }

        for(unsigned k = 1, k1 = 0; k < sideP; k++, k1++) {

            this->addCell(j1 + k1, i1 + k1, i2 + k1, j2 + k1,
                          j1 + k, i1 + k, i2 + k, j2 + k);

            this->mark.push_back(1);

            this->addFace(i1 + k1, i1 + k, i2 + k, i2 + k1);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(i3);

            if(j < base1) {

                this->addFace(j2 + k1, j2 + k, i2 + k, i2 + k1);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(this->meshInfo.numberOfCells + sideP);
            }

            this->addFace(j1 + k, i1 + k, i2 + k, j2 + k);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(this->meshInfo.numberOfCells + 1);
        }

        //connection with cubic
        j1 = j1 + sideP - 1;
        j2 = j2 + sideP - 1;
        i1 = i1 + sideP - 1;
        i2 = i2 + sideP - 1;
        i3 = i3 + sideP - 1;
        unsigned k1 = outerP + (j%edgeP + 1)*layerP2 - edgeP,
                 k2 = k1 + layerP2,
                 k3 = outerC + (j%edgeP + 1)*layerC - edgeC + 1;

        this->addCell(j1, i1, i2, j2,
                      k1, k1 - edgeP, k2 - edgeP, k2);

        this->mark.push_back(1);

        this->addFace(i1, k1 - edgeP, k2 - edgeP, i2);
        this->addOwner(this->meshInfo.numberOfCells);
        this->addNeighbor(i3);

        if(j < base1) {

            this->addFace(j2, i2, k2 - edgeP, k2);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(this->meshInfo.numberOfCells + sideP);

        }

        this->addFace(k1, k2, k2 - edgeP, k1 - edgeP);
        this->addOwner(this->meshInfo.numberOfCells);
        this->addNeighbor(k3);
    }


    // front - bot
    unsigned base2 = base1 + edgeP - 1;

    for(unsigned j = base1 + 2; j <= base2; j++) {

        unsigned j1 = (j - 1)*layerP, j2 = j1 + layerP,
                 i1, i2, i3;

        if(j == base2) {

            i1 = baseP + (edgeP - 2)*(edgeP - 2)*sideP - (j + 1)%edgeP*sideP;
            i2 = j2 + layerP;
            i3 = baseC + 3*edgeC*sideP - 2*sideP + 1;

        } else{

            i1 = baseP + (edgeP - 2)*(edgeP - 2)*sideP - (j + 1)%edgeP*sideP;
            i2 = i1 - sideP;
            i3 = baseC + frontC - (j + 1)%edgeP*sideP + 1;

        }

        for(unsigned k = 1, k1 = 0; k < sideP; k++, k1++) {

            this->addCell(j1 + k1, i1 + k1, i2 + k1, j2 + k1,
                          j1 + k, i1 + k, i2 + k, j2 + k);

            this->mark.push_back(1);

            this->addFace(i1 + k1, i2 + k1, i2 + k, i1 + k);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(i3);

            if(j < base2) {

                this->addFace(j2 + k1, i2 + k1, i2 + k, j2 + k);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(this->meshInfo.numberOfCells + sideP);

            }

            this->addFace(j1 + k, j2 + k, i2 + k, i1 + k);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(this->meshInfo.numberOfCells + 1);
        }

        //connection with cubic
        j1 = j1 + sideP - 1;
        j2 = j2 + sideP - 1;
        i1 = i1 + sideP - 1;
        i2 = i2 + sideP - 1;
        i3 = i3 + sideP - 1;
        unsigned k1 = outerP + layerP2*edgeP - ((j + 2)%edgeP)*edgeP,
                 k2 = k1 - layerP2,
                 k3 = outerC + innerC - ((j + 1)%edgeP)*edgeC + 1;

        this->addCell(j1, i1, i2, j2,
                      k1, k2, k2 - edgeP, k1 - edgeP);

        this->mark.push_back(1);

        this->addFace(i1, i2, k2 - edgeP, k2);
        this->addOwner(this->meshInfo.numberOfCells);
        this->addNeighbor(i3);

        if(j < base2) {

            this->addFace(j2, i2, k2 - edgeP, k1 - edgeP);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(this->meshInfo.numberOfCells + sideP);

        }

        this->addFace(k1, k1 - edgeP, k2 - edgeP, k2);
        this->addOwner(this->meshInfo.numberOfCells);
        this->addNeighbor(k3);
    }

    // front - left
    unsigned base3 = cellNums[0] - 1;

    for(unsigned j = base2 + 2; j <= base3; j++) {

        unsigned j1 = (j - 1)*layerP, j2 = j1 + layerP;

        unsigned i1 = baseP + (cellNums[0] - j)*(edgeP - 2)*sideP,
                 i2 = i1 - (edgeP - 2)*sideP,
                 i3 = baseC + 4*(edgeC - 1)*sideP + (cellNums[0] - j - 1)*(edgeC - 2)*sideP + 1;

        for(unsigned k = 1, k1 = 0; k < sideP; k++, k1++) {

            this->addCell(j1 + k1, i1 + k1, i2 + k1, j2 + k1,
                          j1 + k, i1 + k, i2 + k, j2 + k);

            this->mark.push_back(1);

            this->addFace(i1 + k1, i1 + k, i2 + k, i2 + k1);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(i3);

            if(j < base3) {

                this->addFace(j2 + k1, i2 + k1, i2 + k, j2 + k);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(this->meshInfo.numberOfCells + sideP);
            }

            this->addFace(j1 + k, j2 + k, i2 + k, i1 + k);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(this->meshInfo.numberOfCells + 1);
        }

        //connection with cubic
        j1 = j1 + sideP - 1;
        j2 = j2 + sideP - 1;
        i1 = i1 + sideP - 1;
        i2 = i2 + sideP - 1;
        i3 = i3 + sideP - 1;
        unsigned k1 = outerP + (cellNums[0] - j + 1)*layerP2,
                 k2 = k1 - layerP2,
                 k3 = outerC + (cellNums[0] - j)*layerC + 1;

        this->addCell(j1, i1, i2, j2,
                      k1, k1 + edgeP, k2 + edgeP, k2);

        this->mark.push_back(1);

        this->addFace(i1, k1 + edgeP, k2 + edgeP, i2);
        this->addOwner(this->meshInfo.numberOfCells);
        this->addNeighbor(i3);

        if(j < base2) {

            this->addFace(j2, i2, k2 + edgeP, k2);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(this->meshInfo.numberOfCells + sideP);

        }

        this->addFace(k1, k2, k2 + edgeP, k1 + edgeP);
        this->addOwner(this->meshInfo.numberOfCells);
        this->addNeighbor(k3);
    }
}


void Mesh::sphericRearConnectivity() {
    arrUnsgn cellNums(CELL(1));
    unsigned sideP = cellNums[0]/8,
             edgeC = cellNums[0]/4,
             edgeP = edgeC + 1,
             layerP = sideP*edgeP,
             layerP2 = edgeP*edgeP,
             layerC = edgeC*edgeC,
             baseP = cellNums[0]*layerP,
             frontP =  (edgeP - 2)*(edgeP - 2)*sideP,
             outerP = baseP + 2*frontP,
             innerP = edgeP*layerP2,
             frontC = (edgeC - 2)*(edgeC - 2)*sideP + 4*(edgeC - 1)*sideP,
             baseC  = sideP*edgeC*cellNums[0],
             baseC2 = baseC + frontC,
             outerC = baseC + 2*frontC,
             innerC = edgeC*edgeC*edgeC;

    // rear - top
    for(unsigned j = 1; j < edgeP; j++) {

        unsigned j1 = baseP - (j - 2)*layerP -sideP, j2 = j1 - layerP,
                 i1, i2, i3;

        if(j == 1) {

            j1 = layerP - sideP;
            i1 = 2*layerP - sideP;
            i2 = baseP + frontP;
            i3 = baseC2 + 4*(edgeC - 1)*sideP - sideP + 1;

        } else if(j == edgeP - 1) {

            i1 = baseP + frontP + (j - 2)*sideP;
            i2 = baseP - (edgeP - 1)*layerP  - sideP;
            i3 = baseC2 + edgeC*sideP + 1;

        } else{

            i1 = baseP + frontP + (j - 2)*sideP;
            i2 = i1 + sideP;
            i3 = baseC2 + 4*(edgeC - 1)*sideP + (j - 2)*sideP + 1;

        }

        for(unsigned k = 1, k1 = 0; k < sideP; k++, k1++) {

            this->addCell(j1 + k1, i1 + k1, i2 + k1, j2 + k1,
                          j1 + k, i1 + k, i2 + k, j2 + k);

            this->mark.push_back(1);

            this->addFace(i1 + k1, i1 + k, i2 + k, i2 + k1);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(i3);

            if(j < edgeC) {

                this->addFace(j2 + k1, i2 + k1, i2 + k, j2 + k);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(this->meshInfo.numberOfCells + sideP);

            }

            this->addFace(j1 + k, j2 + k, i2 + k, i1 + k);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(this->meshInfo.numberOfCells + 1);
        }

        //connection with cubic
        j1 = j1 + sideP - 1;
        j2 = j2 + sideP - 1;
        i1 = i1 + sideP - 1;
        i2 = i2 + sideP - 1;
        i3 = i3 + sideP - 1;
        unsigned k1 = outerP + (j - 1)*layerP2 + edgeP - 1,
                 k2 = k1 + layerP2,
                 k3 = outerC + (j - 1)*layerC + edgeC;

        this->addCell(j1, i1, i2, j2,
                      k1, k1 + edgeP, k2 + edgeP, k2);

        this->mark.push_back(1);

        this->addFace(i1, k1 + edgeP, k2 + edgeP, i2);
        this->addOwner(this->meshInfo.numberOfCells);
        this->addNeighbor(i3);

        if(j < edgeC) {

            this->addFace(j2, i2, k2 + edgeP, k2);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(this->meshInfo.numberOfCells + sideP);

        }

        this->addFace(k1, k1 + edgeP, k2 + edgeP, k2);
        this->addOwner(this->meshInfo.numberOfCells);
        this->addNeighbor(k3);
    }


    // rear - right
    unsigned base1 = edgeP + edgeP - 2;

    for(unsigned j = edgeP + 1; j <= base1; j++) {

        unsigned j1 = baseP - (j - 2)*layerP -sideP, j2 = j1 - layerP,
                 i1, i2, i3;

        if(j == base1) {

            i1 = baseP + frontP + (j%edgeP)*(edgeP - 2)*sideP - sideP;
            i2 = j2 - layerP;
            i3 = baseC2 + 2*edgeC*sideP -sideP + 1;

        } else {

            i1 = baseP + frontP + (j%edgeP)*(edgeP - 2)*sideP - sideP;
            i2 = i1 + (edgeP - 2)*sideP;
            i3 = baseC2 + 4*(edgeC - 1)*sideP + (j%edgeP)*(edgeC - 2)*sideP -sideP + 1;

        }

        for(unsigned k = 1, k1 = 0; k < sideP; k++, k1++) {

            this->addCell(j1 + k1, i1 + k1, i2 + k1, j2 + k1,
                          j1 + k, i1 + k, i2 + k, j2 + k);

            this->mark.push_back(1);

            this->addFace(i1 + k1, i1 + k, i2 + k, i2 + k1);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(i3);

            if(j < base1) {

                this->addFace(j2 + k1, i2 + k1, i2 + k, j2 + k);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(this->meshInfo.numberOfCells + sideP);

            }

            this->addFace(j1 + k, j2 + k, i2 + k, i1 + k);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(this->meshInfo.numberOfCells + 1);
        }

        //connection with cubic
        j1 = j1 + sideP - 1;
        j2 = j2 + sideP - 1;
        i1 = i1 + sideP - 1;
        i2 = i2 + sideP - 1;
        i3 = i3 + sideP - 1;
        unsigned k1 = outerP + innerP - (base1 - j + 1)*edgeP - 1,
                 k2 = k1 - layerP2,
                 k3 = outerC + innerC - (base1 - j)*edgeC;

        this->addCell(j1, i1, i2, j2,
                      k1, k2, k2 + edgeP, k1 + edgeP);

        this->mark.push_back(1);

        this->addFace(i1, k2, k2 + edgeP, i2);
        this->addOwner(this->meshInfo.numberOfCells);
        this->addNeighbor(i3);

        if(j < base1) {

            this->addFace(j2, i2, k2 + edgeP, k1 + edgeP);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(this->meshInfo.numberOfCells + sideP);

        }

        this->addFace(k1, k1 + edgeP, k2 + edgeP, k2);
        this->addOwner(this->meshInfo.numberOfCells);
        this->addNeighbor(k3);
    }


    // rear - bot
    unsigned base2 = base1 + edgeP - 1;

    for(unsigned j = base1 + 2; j <= base2; j++) {

        unsigned j1 = baseP - (j - 2)*layerP -sideP, j2 = j1 - layerP,
                 i1, i2, i3;

        if(j == base2) {

            i1 = baseP + 2*frontP - (j + 1)%edgeP*sideP;
            i2 = j2 - layerP;
            i3 = baseC2 + 3*edgeC*sideP - 2*sideP + 1;

        } else{

            i1 = baseP + 2*frontP - (j + 1)%edgeP*sideP;
            i2 = i1 - sideP;
            i3 = baseC2 + frontC - (j + 1)%edgeP*sideP + 1;

        }

        for(unsigned k = 1, k1 = 0; k < sideP; k++, k1++) {

            this->addCell(j1 + k1, i1 + k1, i2 + k1, j2 + k1,
                          j1 + k, i1 + k, i2 + k, j2 + k);

            this->mark.push_back(1);

            this->addFace(i1 + k1, i1 + k, i2 + k, i2 + k1);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(i3);

            if(j < base2) {

                this->addFace(j2 + k1, i2 + k1, i2 + k, j2 + k);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(this->meshInfo.numberOfCells + sideP);

            }

            this->addFace(j1 + k, j2 + k, i2 + k, i1 + k);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(this->meshInfo.numberOfCells + 1);
        }

        //connection with cubic
        j1 = j1 + sideP - 1;
        j2 = j2 + sideP - 1;
        i1 = i1 + sideP - 1;
        i2 = i2 + sideP - 1;
        i3 = i3 + sideP - 1;
        unsigned k1 = outerP + innerP - (j + 1)%edgeP*layerP2 - 1,
                 k2 = k1 - layerP2,
                 k3 = outerC + innerC - (j + 1)%edgeP*layerC;

        this->addCell(j1, i1, i2, j2,
                      k1, k1 - edgeP, k2 - edgeP, k2);

        this->mark.push_back(1);

        this->addFace(i1, k1 - edgeP, k2 - edgeP, i2);
        this->addOwner(this->meshInfo.numberOfCells);
        this->addNeighbor(i3);

        if(j < base2) {

            this->addFace(j2, i2, k2 - edgeP, k2);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(this->meshInfo.numberOfCells + sideP);
        }

        this->addFace(k1, k2, k2 - edgeP, k1 - edgeP);
        this->addOwner(this->meshInfo.numberOfCells);
        this->addNeighbor(k3);
    }


    // rear - left
    unsigned base3 = cellNums[0] - 1;

    for(unsigned j = base2 + 2; j <= base3; j++) {

        unsigned j1 = baseP - (j - 2)*layerP -sideP, j2 = j1 - layerP,
                 i1 = baseP + frontP + (cellNums[0] - j)*(edgeP - 2)*sideP,
                 i2 = i1 - (edgeP - 2)*sideP,
                 i3 = baseC2 + frontC - (j + 2)%edgeP*(edgeC -2)*sideP + 1;

        for(unsigned k = 1, k1 = 0; k < sideP; k++, k1++) {

            this->addCell(j1 + k1, i1 + k1, i2 + k1, j2 + k1,
                          j1 + k, i1 + k, i2 + k, j2 + k);

            this->mark.push_back(1);

            this->addFace(i1 + k1, i1 + k, i2 + k, i2 + k1);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(i3);

            if(j < base3) {

                this->addFace(j2 + k1, i2 + k1, i2 + k, j2 + k);
                this->addOwner(this->meshInfo.numberOfCells);
                this->addNeighbor(this->meshInfo.numberOfCells + sideP);

            }

            this->addFace(j1 + k, j2 + k, i2 + k, i1 + k);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(this->meshInfo.numberOfCells + 1);
        }

        //connection with cubic
        j1 = j1 + sideP - 1;
        j2 = j2 + sideP - 1;
        i1 = i1 + sideP - 1;
        i2 = i2 + sideP - 1;
        i3 = i3 + sideP - 1;
        unsigned k1 = outerP + layerP2 - (j + 2)%edgeP*edgeP - 1,
                 k2 = k1 + layerP2,
                 k3 = outerC + layerC - (j + 2)%edgeP*edgeC;

        this->addCell(j1, i1, i2, j2,
                      k1, k2, k2 - edgeP, k1 - edgeP);

        this->mark.push_back(1);

        this->addFace(i1, k2, k2 - edgeP, i2);
        this->addOwner(this->meshInfo.numberOfCells);
        this->addNeighbor(i3);

        if(j < base2) {

            this->addFace(j2, i2, k2 - edgeP, k1 - edgeP);
            this->addOwner(this->meshInfo.numberOfCells);
            this->addNeighbor(this->meshInfo.numberOfCells + sideP);

        }

        this->addFace(k1, k1 - edgeP, k2 - edgeP, k2);
        this->addOwner(this->meshInfo.numberOfCells);
        this->addNeighbor(k3);
    }
}


void Mesh::meshConnected2D(unsigned& layer,unsigned& position, unsigned& p1, unsigned& p2) {
    arrUnsgn cellNums(CELL(layer));
    unsigned edgeP = cellNums[0]/4 + 1,
            outerP = cellNums[0]*cellNums[0]/8,
            tmp = position/(edgeP -1),
            tmp2 = position%(edgeP - 1);

    switch(tmp){
        case 0: p1 = outerP + position; p2 = p1 + 1; break;
        case 1: p1 = outerP + edgeP + tmp2*edgeP - 1; p2 = p1 + edgeP; break;
        case 2: p1 = outerP + edgeP*edgeP - tmp2 - 1; p2 = p1 - 1; break;
        case 3: p1 = outerP + (edgeP - tmp2 - 1)*edgeP; p2 = p1 - edgeP; break;
    }
}


void Mesh::findPointsconnected3D(unsigned& position, unsigned& position2, unsigned& p1, unsigned& p2, unsigned& p3) {

    arrUnsgn cellNums(CELL(1));
    unsigned sideP = cellNums[0]/8,
             edgeC = cellNums[0]/4,
             edgeP = edgeC + 1,
             layerP = edgeP*edgeP,
             outerP = cellNums[0]*sideP*edgeP + 2*(edgeP - 2)*(edgeP - 2)*sideP,
             outerC = sideP*edgeC*cellNums[0] + 2*((edgeC - 2)*(edgeC - 2)*sideP + 4*(edgeC - 1)*sideP),
             innerC = edgeC* edgeC*edgeC,
             tmp = position/(edgeP -1),
             tmp2 = position%(edgeP - 1);

    switch(tmp){
        case 0:
            p1 = outerP + position*edgeP + position2;
            p2 = p1 + edgeP;
            p3 = outerC + position*edgeC + position2 + 1;
            break;
        case 1:
            p1 = outerP + (tmp2 + 1)*layerP - edgeP  + position2;
            p2 = p1 + layerP;
            p3 = outerC + (tmp2 + 1)*(edgeC*edgeC) - edgeC + position2 + 1;
            break;
        case 2:
            p1 = this->meshInfo.numberOfPoints - (tmp2 + 1)*edgeP + position2;
            p2 = p1 - edgeP;
            p3 = outerC + innerC - (tmp2 + 1)*edgeC + position2 + 1;
            break;
        case 3:
            p1 = this->meshInfo.numberOfPoints - (tmp2 + 1)*layerP + position2;
            p2 = p1 - layerP;
            p3 = outerC + innerC - (tmp2 + 1)*edgeC*edgeC + position2 + 1;
            break;
    }
}
