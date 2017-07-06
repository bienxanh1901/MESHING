#include "../include/Mesh.h"

void Mesh::cubicGeneratior() {

    this->cubicPoints();
    this->cubicInternalFacesandCells();
    this->numberOfBoundaries = 6;
    this->cubicBoundariesLeftRight();
    this->cubicBoundariesFrontRear();
    this->cubicBoundariesTopBot();
}

void Mesh::cubicPoints() {

    double ratioX, ratioY;
    double dimX, dimY;
    double sizeX, sizeY;
    double startX, startY;

    dimX = DIM(1);
    dimY = DIM(2);
    sizeX = SIZE(0);
    sizeY = SIZE(1);
    startX = 0.0;
    startY = 0.0;

    if(this->meshInfo.meshShape.getShape()==TRAPEZE){
        ratioX = SIZE(2)*(DIM(1) - DIM(4))/DIM(3);
        ratioY = SIZE(2)*(DIM(2) - DIM(5))/DIM(3);
    }

    for(double stepZ = 0; stepZ <= DIM(3) + EPS; stepZ+= SIZE(2)) {

        for(double stepY = 0; stepY <= dimY + EPS; stepY+= sizeY) {

            for(double stepX = 0; stepX <= dimX + EPS; stepX+= sizeX) {

                this->addPoint(stepX + startX, stepY + startY, stepZ);
            }
        }

        if(this->meshInfo.meshShape.getShape() == TRAPEZE){
            dimX-= ratioX;
            dimY-= ratioY;
            sizeX = dimX/(double)NODE(0);
            sizeY = dimY/(double)NODE(1);
            startX = (DIM(1) - dimX)/2.0;
            startY = (DIM(2) - dimY)/2.0;
        }
    }
}

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

void Mesh::cubicBoundariesLeftRight(){

    unsigned lengthPoints = NODE(0) + 1;
    unsigned widthPoints = NODE(1) + 1;
    unsigned layerPoints = lengthPoints*widthPoints;
    unsigned layerCells = NODE(0)*NODE(1);
    unsigned j1, j2, j3, k1, k2, k3, i1;

    i1 = lengthPoints - 1;
    for(unsigned k = 1; k <= NODE(2); k++){
        k1 = (k - 1)*layerPoints;
        k2 = k*layerPoints;
        k3 = (k - 1)*layerCells;

        for(unsigned j = 1; j <= NODE(1); j++){
            j1 = (j - 1)*lengthPoints;
            j2 = j*lengthPoints;
            j3 = (j - 1)*NODE(1);

            this->addFace(k1 + j1, k2 + j1, k2 + j2, k1 + j2);
            this->addOwner(k3 + j3 + 1);
        }
    }
    this->boundaries.push_back(NODE(2)*NODE(1));

    for(unsigned k = 1; k <= NODE(2); k++){
        k1 = i1 + (k - 1)*layerPoints;
        k2 = i1 + k*layerPoints;
        k3 = i1 + (k - 1)*layerCells;

        for(unsigned j = 1; j <= NODE(1); j++){
            j1 = (j - 1)*lengthPoints;
            j2 = j*lengthPoints;
            j3 = (j - 1)*NODE(1);

            this->addFace(k1 + j1, k1 + j2, k2 + j2, k2 + j1);
            this->addOwner(k3 + j3);
        }
    }
    this->boundaries.push_back(NODE(2)*NODE(1));
}

void Mesh::cubicBoundariesFrontRear(){

    unsigned lengthPoints = NODE(0) + 1;
    unsigned widthPoints = NODE(1) + 1;
    unsigned layerPoints = lengthPoints*widthPoints;
    unsigned layerCells = NODE(0)*NODE(1);
    unsigned i1, k1, k2, k3, j1, j2;

    j1 = NODE(1)*lengthPoints;
    j2 = (NODE(1) - 1)*NODE(0);
    for(unsigned k = 1; k <= NODE(2); k++){

        k1 = (k - 1)*layerPoints;
        k2 = k*layerPoints;
        k3 = (k - 1)*layerCells;

        for(unsigned i = 1; i <= NODE(0); i++){
            i1 = i - 1;

            this->addFace(k1 + i1, k1 + i, k2 + i, k2 + i1);
            this->addOwner(k3 + i);
        }
    }
    this->boundaries.push_back(NODE(2)*NODE(0));

    for(unsigned k = 1; k <= NODE(2); k++){

        k1 = j1 + (k - 1)*layerPoints;
        k2 = j1 + k*layerPoints;
        k3 = j2 + (k - 1)*layerCells;
        for(unsigned i = 1; i <= NODE(0); i++){
            i1 = i - 1;

            this->addFace(k1 + i1, k2 + i1, k2 + i, k1 + i);
            this->addOwner(k3 + i);
        }
    }
    this->boundaries.push_back(NODE(2)*NODE(0));
}

void Mesh::cubicBoundariesTopBot(){

    unsigned lengthPoints = NODE(0) + 1;
    unsigned widthPoints = NODE(1) + 1;
    unsigned layerPoints = lengthPoints*widthPoints;
    unsigned layerCells = NODE(0)*NODE(1);
    unsigned i1, j1, j2, j3, k1, k2;

    k1 = layerPoints*NODE(2);
    k2 = layerCells*(NODE(2) - 1);

    for(unsigned j = 1; j <= NODE(1); j++){
        j1 = (j - 1)*lengthPoints;
        j2 = j*lengthPoints;
        j3 = (j - 1)*NODE(1);

        for(unsigned i = 1; i <= NODE(0); i++){
            i1 = i - 1;

            this->addFace(j1 + i1, j2 + i1, j2 + i, j1 + i);
            this->addOwner(j3 + i);
        }
    }
    this->boundaries.push_back(NODE(1)*NODE(0));

    for(unsigned j = 1; j <= NODE(1); j++){
        j1 = k1 + (j - 1)*lengthPoints;
        j2 = k1 + j*lengthPoints;
        j3 = k2 + (j - 1)*NODE(1);

        for(unsigned i = 1; i <= NODE(0); i++){
            i1 = i - 1;

            this->addFace(j1 + i1, j1 + i, j2 + i, j2 + i1);
            this->addOwner(j3 + i);
        }
    }
    this->boundaries.push_back(NODE(1)*NODE(0));

}
