#include "../include/Mesh.h"

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
