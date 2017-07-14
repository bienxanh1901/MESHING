#include "../include/Mesh.h"

void Mesh::sphericGenerator() {

    this->sphericPoints();
    this->sphericFacesandCells();
//    this->sphericBoundaries();
}


void Mesh::sphericPoints() {

    this->topPartPoints();
    this->leftRightBotPartsPoints();
    this->frontRearPartsPoints();
    this->cubicPartPoints();
}


void Mesh::sphericFacesandCells() {

    this->leftRightBotTopPartsCells();
    this->frontPartCells();
    this->rearPartCells();
    this->cubicPartCells();
    this->meshInfo.numberOfInternalFaces = this->meshInfo.numberOfFaces;
}

void Mesh::sphericBoundaries() {

    this->meshInfo.numberOfBoundaries = 2;
    this->sphericTopBoundary();
    this->sphericBotBoundary();
}



