#include "../../include/Mesh.h"

void Mesh::cubicGenerator() {

    this->cubicPoints();
    this->cubicInternalFacesandCells();
    this->cubicBoundaries();
}

void Mesh::cubicBoundaries() {

    this->meshInfo.numberOfBoundaries = 6;
    this->cubicBoundaryLeft();
    this->cubicBoundaryRight();
    this->cubicBoundaryFront();
    this->cubicBoundaryRear();
    this->cubicBoundaryBot();
    this->cubicBoundaryTop();
}

