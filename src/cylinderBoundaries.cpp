//#include "../include/Mesh.h"
//
//void Mesh::cylinderBoundaryBot(){
//    unsigned sidePoints = NODE(0)/8;
//    unsigned edgePoints = NODE(0)/4 + 1;
//    unsigned outerPoints = NODE(0)*sidePoints;
//    unsigned baseC = outerPoints + pow(edgePoints - 1,2);
//
//    containerIDs pointCells;
//
//    for(unsigned i = 0; i < baseC; i++) {
//
//        pointCells = this->cells[i].getPointsIDList();
//        this->addFace( pointCells[3] - 1, pointCells[2] - 1, pointCells[1] - 1, pointCells[0] - 1);
//        this->addOwner(i + 1);
//
//    }
//
//    this->boundaries.push_back(baseC);
//}
//
//
//void Mesh::cylinderBoundaryTop(){
//    unsigned sidePoints = NODE(0)/8;
//    unsigned edgePoints = NODE(0)/4 + 1;
//    unsigned outerPoints = NODE(0)*sidePoints;
//    unsigned baseC = outerPoints + pow(edgePoints - 1,2);
//
//    containerIDs pointCells;
//
//    for(unsigned i = this->meshInfo.numberOfCells - baseC; i < this->meshInfo.numberOfCells; i++) {
//
//        pointCells = this->cells[i].getPointsIDList();
//        this->addFace( pointCells[4] - 1, pointCells[5] - 1, pointCells[6] - 1, pointCells[7] - 1);
//        this->addOwner(i + 1);
//
//    }
//
//    this->boundaries.push_back(baseC);
//}
//
//
//void Mesh::cylinderBoundariesAround()
//{
//    unsigned sidePoints = NODE(0)/8;
//    unsigned edgePoints = NODE(0)/4 + 1;
//    unsigned outerPoints = NODE(0)*sidePoints;
//    unsigned base = NODE(0)*sidePoints + pow(edgePoints,2);
//    unsigned baseC = outerPoints + pow(edgePoints - 1,2);
//    unsigned j1, j2, k1, k2, k3;
//
//
//    // left boundary
//    for(unsigned k = 1; k <= NODE(1); k++){
//        k1 = (k - 1)*base;
//        k2 = k*base;
//        k3 = (k - 1)*baseC;
//        for(unsigned j = 1; j <= NODE(0)/2; j++){
//            j1 = (j - 1)*sidePoints;
//            j2 = j*sidePoints;
//            if(j == NODE(0))j2 = 0;
//
//            this->addFace(k1 + j1, k2 + j1, k2 + j2, k1 + j2);
//            this->addOwner(k3 + j1 + 1);
//        }
//    }
//    this->boundaries.push_back(NODE(0)*NODE(1)/2);
//
//
//    // right boundary
//    for(unsigned k = NODE(0)/2 + 1; k <= NODE(1); k++){
//        k1 = (k - 1)*base;
//        k2 = k*base;
//        k3 = (k - 1)*baseC;
//        for(unsigned j = 1; j <= NODE(0); j++){
//            j1 = (j - 1)*sidePoints;
//            j2 = j*sidePoints;
//            if(j == NODE(0))j2 = 0;
//
//            this->addFace(k1 + j1, k2 + j1, k2 + j2, k1 + j2);
//            this->addOwner(k3 + j1 + 1);
//        }
//    }
//    this->boundaries.push_back(NODE(0)*NODE(1)/2);
//}
