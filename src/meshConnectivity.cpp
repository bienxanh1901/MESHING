#include "../include/Mesh.h"

void Mesh::sphericFrontConnectivity() {
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned layer = sidePoints*edgePoints;
    unsigned layerC = edgePoints*edgePoints;
    unsigned base = NODE(0)*layer;
    unsigned outerPoints= base + 2*(edgePoints - 2)*(edgePoints - 2)*sidePoints;
    unsigned i1, i2, j1, j2, k1, k2;

    containerPoints pointsList;

    // front - top
    for(unsigned j = 1; j < edgePoints; j++) {
        j1 = (j - 1)*layer;
        j2 = j1 + layer;

        if(j == 1) {
            i1 = base - layer;
            i2 = base + j - 1;
        } else if(j == edgePoints - 1) {
            i1 = base + (j - 2)*sidePoints;
            i2 = j2 + layer;
        } else{
            i1 = base + (j - 2)*sidePoints;
            i2 = i1 + sidePoints;
        }

        for(unsigned k = 1; k < sidePoints; k++) {
                k1 = k - 1;

                this->addCell(j1 + k1, i1 + k1, i2 + k1, j2 + k1,
                              j1 + k, i1 + k, i2 + k, j2 + k);
        }

        //connects with cubic
        j1 = j1 + sidePoints - 1;
        j2 = j2 + sidePoints - 1;
        i1 = i1 + sidePoints - 1;
        i2 = i2 + sidePoints - 1;
        k1 = outerPoints + (j - 1)*edgePoints;
        k2 = k1 + layerC;

        this->addCell(j1, i1, i2, j2,
                      k1, k2, k2 + edgePoints, k1 + edgePoints);
    }

    // front - right
    unsigned base1 = edgePoints + edgePoints - 2;

    for(unsigned j = edgePoints + 1; j <= base1; j++) {
        j1 = (j - 1)*layer;
        j2 = j1 + layer;

        if(j == base1) {
            i1 = base + (j%edgePoints)*(edgePoints - 2)*sidePoints - sidePoints;
            i2 = j2 + layer;
        } else {
            i1 = base + (j%edgePoints)*(edgePoints - 2)*sidePoints - sidePoints;
            i2 = i1 + (edgePoints - 2)*sidePoints;
        }

        for(unsigned k = 1; k < sidePoints; k++) {
            k1 = k - 1;

            this->addCell(j1 + k1, i1 + k1, i2 + k1, j2 + k1,
                          j1 + k, i1 + k, i2 + k, j2 + k);
        }

        //connects with cubic
        j1 = j1 + sidePoints - 1;
        j2 = j2 + sidePoints - 1;
        i1 = i1 + sidePoints - 1;
        i2 = i2 + sidePoints - 1;
        k1 = outerPoints + (j%edgePoints)*layerC + layerC - edgePoints;
        k2 = k1 + layerC;

        this->addCell(j1, i1, i2, j2,
                      k1, k1 - edgePoints, k2 - edgePoints, k2);
    }


    // front - bot
    unsigned base2 = base1 + edgePoints - 1;

    for(unsigned j = base1 + 2; j <= base2; j++) {
        j1 = (j - 1)*layer;
        j2 = j1 + layer;

        if(j == base2) {
            i1 = base + (edgePoints - 2)*(edgePoints - 2)*sidePoints - (j + 1)%edgePoints*sidePoints;
            i2 = j2 + layer;
        } else{
            i1 = base + (edgePoints - 2)*(edgePoints - 2)*sidePoints - (j + 1)%edgePoints*sidePoints;
            i2 = i1 - sidePoints;
        }

        for(unsigned k = 1; k < sidePoints; k++) {
            k1 = k - 1;

            this->addCell(j1 + k1, i1 + k1, i2 + k1, j2 + k1,
                          j1 + k, i1 + k, i2 + k, j2 + k);
        }

        //connects with cubic
        j1 = j1 + sidePoints - 1;
        j2 = j2 + sidePoints - 1;
        i1 = i1 + sidePoints - 1;
        i2 = i2 + sidePoints - 1;
        k1 = outerPoints + layerC*edgePoints - ((j + 2)%edgePoints)*edgePoints;
        k2 = k1 - layerC;

        this->addCell(j1, i1, i2, j2,
                      k1, k2, k2 - edgePoints, k1 - edgePoints);
    }

    // front - left
    unsigned base3 = NODE(0) - 1;

    for(unsigned j = base2 + 2; j <= base3; j++) {
        j1 = (j - 1)*layer;
        j2 = j1 + layer;

        i1 = base + (NODE(0) - j)*(edgePoints - 2)*sidePoints;
        i2 = i1 - (edgePoints - 2)*sidePoints;

        for(unsigned k = 1; k < sidePoints; k++) {
            k1 = k - 1;

            this->addCell(j1 + k1, i1 + k1, i2 + k1, j2 + k1,
                          j1 + k, i1 + k, i2 + k, j2 + k);
        }

        //connects with cubic
        j1 = j1 + sidePoints - 1;
        j2 = j2 + sidePoints - 1;
        i1 = i1 + sidePoints - 1;
        i2 = i2 + sidePoints - 1;
        k1 = outerPoints + (NODE(0) - j + 1)*layerC;
        k2 = k1 - layerC;

        this->addCell(j1, i1, i2, j2,
                      k1, k1 + edgePoints, k2 + edgePoints, k2);
    }
}


void Mesh::sphericRearConnectivity() {
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned layer = sidePoints*edgePoints;
    unsigned layerC = edgePoints*edgePoints;
    unsigned base = NODE(0)*layer;
    unsigned frontPoints =  (edgePoints - 2)*(edgePoints - 2)*sidePoints;
    unsigned outerPoints = base + 2*frontPoints;
    unsigned innerPoints = edgePoints*layerC;
    unsigned i1, i2, j1, j2, k1, k2;

    // rear - top
    for(unsigned j = 1; j < edgePoints; j++) {
        j1 = base - (j - 2)*layer -sidePoints ;
        j2 = j1 - layer;

        if(j == 1) {
            j1 = layer - sidePoints;
            i1 = 2*layer - sidePoints;
            i2 = base + frontPoints;
        } else if(j == edgePoints - 1) {
            i1 = base + frontPoints + (j - 2)*sidePoints;
            i2 = base - (edgePoints - 1)*layer  - sidePoints;
        } else{
            i1 = base + frontPoints + (j - 2)*sidePoints;
            i2 = i1 + sidePoints;
        }

        for(unsigned k = 1; k < sidePoints; k++) {
            k1 = k - 1;

            this->addCell(j1 + k1, i1 + k1, i2 + k1, j2 + k1,
                      j1 + k, i1 + k, i2 + k, j2 + k);
        }

        //connects with cubic
        j1 = j1 + sidePoints - 1;
        j2 = j2 + sidePoints - 1;
        i1 = i1 + sidePoints - 1;
        i2 = i2 + sidePoints - 1;
        k1 = outerPoints + (j - 1)*layerC + edgePoints - 1;
        k2 = k1 + layerC;

        this->addCell(j1, i1, i2, j2,
                      k1, k1 + edgePoints, k2 + edgePoints, k2);
    }


    // rear - right
    unsigned base1 = edgePoints + edgePoints - 2;

    for(unsigned j = edgePoints + 1; j <= base1; j++) {
        j1 = base - (j - 2)*layer -sidePoints ;
        j2 = j1 - layer;

        if(j == base1) {
            i1 = base + frontPoints + (j%edgePoints)*(edgePoints - 2)*sidePoints - sidePoints;
            i2 = j2 - layer;
        } else {
            i1 = base + frontPoints + (j%edgePoints)*(edgePoints - 2)*sidePoints - sidePoints;
            i2 = i1 + (edgePoints - 2)*sidePoints;
        }

        for(unsigned k = 1; k < sidePoints; k++) {
            k1 = k - 1;

            this->addCell(j1 + k1, i1 + k1, i2 + k1, j2 + k1,
                          j1 + k, i1 + k, i2 + k, j2 + k);
        }

        //connects with cubic
        j1 = j1 + sidePoints - 1;
        j2 = j2 + sidePoints - 1;
        i1 = i1 + sidePoints - 1;
        i2 = i2 + sidePoints - 1;
        k1 = outerPoints + innerPoints - (base1 - j + 1)*edgePoints - 1;
        k2 = k1 - layerC;

        this->addCell(j1, i1, i2, j2,
                      k1, k2, k2 + edgePoints, k1 + edgePoints);
    }


    // rear - bot
    unsigned base2 = base1 + edgePoints - 1;

    for(unsigned j = base1 + 2; j <= base2; j++) {
        j1 = base - (j - 2)*layer -sidePoints ;
        j2 = j1 - layer;

        if(j == base2) {
            i1 = base + 2*frontPoints - (j + 1)%edgePoints*sidePoints;
            i2 = j2 - layer;
        } else{
            i1 = base + 2*frontPoints - (j + 1)%edgePoints*sidePoints;
            i2 = i1 - sidePoints;
        }

        for(unsigned k = 1; k < sidePoints; k++) {
            k1 = k - 1;

            this->addCell(j1 + k1, i1 + k1, i2 + k1, j2 + k1,
                          j1 + k, i1 + k, i2 + k, j2 + k);
        }

        //connects with cubic
        j1 = j1 + sidePoints - 1;
        j2 = j2 + sidePoints - 1;
        i1 = i1 + sidePoints - 1;
        i2 = i2 + sidePoints - 1;
        k1 = outerPoints + innerPoints - (j + 1)%edgePoints*layerC - 1;
        k2 = k1 - layerC;

        this->addCell(j1, i1, i2, j2,
                      k1, k1 - edgePoints, k2 - edgePoints, k2);
    }


    // rear - left
    unsigned base3 = NODE(0) - 1;

    for(unsigned j = base2 + 2; j <= base3; j++) {
        j1 = base - (j - 2)*layer -sidePoints ;
        j2 = j1 - layer;

        i1 = base + frontPoints + (NODE(0) - j)*(edgePoints - 2)*sidePoints;
        i2 = i1 - (edgePoints - 2)*sidePoints;

        for(unsigned k = 1; k < sidePoints; k++) {
            k1 = k - 1;

            this->addCell(j1 + k1, i1 + k1, i2 + k1, j2 + k1,
                          j1 + k, i1 + k, i2 + k, j2 + k);
        }

        //connects with cubic
        j1 = j1 + sidePoints - 1;
        j2 = j2 + sidePoints - 1;
        i1 = i1 + sidePoints - 1;
        i2 = i2 + sidePoints - 1;
        k1 = outerPoints + layerC - (j + 2)%edgePoints*edgePoints - 1;
        k2 = k1 + layerC;

        this->addCell(j1, i1, i2, j2,
                      k1, k2, k2 - edgePoints, k1 - edgePoints);
    }
}


void Mesh::findPointsconnected2D(unsigned& position, unsigned& p1, unsigned& p2) {
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned outerPoints = NODE(0)*sidePoints;
    unsigned tmp, tmp2;

    tmp = position/(edgePoints -1);
    tmp2 = position%(edgePoints - 1);
    switch(tmp){
        case 0: p1 = outerPoints + position; p2 = p1 + 1; break;
        case 1: p1 = outerPoints + edgePoints + tmp2*edgePoints - 1; p2 = p1 + edgePoints; break;
        case 2: p1 = outerPoints + edgePoints*edgePoints - tmp2 - 1; p2 = p1 - 1; break;
        case 3: p1 = outerPoints + (edgePoints - tmp2 - 1)*edgePoints; p2 = p1 - edgePoints; break;
    }
}

void Mesh::findPointsconnected3D(unsigned& position, unsigned& position2, unsigned& p1, unsigned& p2) {
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned layer = sidePoints*edgePoints;
    unsigned layerC= edgePoints*edgePoints;
    unsigned base = NODE(0)*layer;
    unsigned outerPoints= base + 2*(edgePoints - 2)*(edgePoints - 2)*sidePoints;
    unsigned innerPoints= edgePoints*layerC;
    unsigned tmp, tmp2;

    tmp = position/(edgePoints -1);
    tmp2 = position%(edgePoints - 1);
    switch(tmp){
        case 0:
            p1 = outerPoints + position*edgePoints + position2;
            p2 = p1 + edgePoints;
            break;
        case 1:
            p1 = outerPoints + position*edgePoints + tmp2*(layerC - edgePoints)  + position2;
            p2 = p1 + layerC;
            break;
        case 2:
            p1 = outerPoints + innerPoints - tmp2*edgePoints - edgePoints + position2;
            p2 = p1 - edgePoints;
            break;
        case 3:
            p1 = outerPoints + (edgePoints - tmp2 - 1)*layerC + position2;
            p2 = p1 - layerC;
            break;
    }
}
