#include "../include/Mesh.h"

void Mesh::cubicGenerator() {

    this->cubicPoints();
    this->cubicInternalFacesandCells();
    this->cubicBoundaries();
}

void Mesh::cubicBoundaries() {

    this->numberOfBoundaries = 6;
    this->cubicBoundariesLeftRight();
    this->cubicBoundariesFrontRear();
    this->cubicBoundariesTopBot();
}

