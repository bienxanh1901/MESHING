#include "../include/Mesh.h"

void Mesh::cylinderGenerator() {

    this->cylinderPoints();
    this->cylinderInternalFacesandCells();
    this->cylinderBoundaries();


}

void Mesh::cylinderPoints() {

    this->basePoints();
    this->extrudePoints();

}


void Mesh::cylinderInternalFacesandCells() {

    this->baseFacesandCells();
    this->extrudeFaces();
    this->extrudeCells();

}


void Mesh::cylinderBoundaries() {

    this->numberOfBoundaries = 4;
    this->cylinderBoundaryBot();
    this->cylinderBoundaryTop();
    this->cylinderBoundariesAround();
}






