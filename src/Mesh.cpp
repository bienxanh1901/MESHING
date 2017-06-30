#include "../include/Mesh.h"

Mesh::Mesh() {
    this->numberOfPoints = 0;
    this->numberOfCells = 0;
    this->numberOfFaces = 0;
    this->numberOfBoundaries = 0;
}

Mesh::~Mesh() {
    this->points.clear();
    this->cells.clear();
    this->faces.clear();
    this->neighbor.clear();
    this->owner.clear();
    this->boundaries.clear();
}

Mesh::Mesh(const Mesh& other) : meshInfo(other.meshInfo) {
    this->numberOfPoints = other.numberOfPoints;
    this->numberOfCells = other.numberOfCells;
    this->numberOfFaces = other.numberOfFaces;
    this->numberOfBoundaries = other.numberOfBoundaries;
    this->points = other.points;
    this->cells = other.cells;
    this->faces = other.faces;
    this->neighbor = other.neighbor;
    this->owner = other.owner;
    this->boundaries = other.boundaries;
}

Mesh::Mesh(MeshInfomation& info) : meshInfo(info) {
    this->numberOfPoints = 0;
    this->numberOfCells = 0;
    this->numberOfFaces = 0;
    this->numberOfBoundaries = 0;
    meshGeneration();
}


Mesh& Mesh::operator=(const Mesh& other) {
    if (this == &other) return *this;
    this->meshInfo = other.meshInfo;
    this->numberOfPoints = other.numberOfPoints;
    this->numberOfCells = other.numberOfCells;
    this->numberOfFaces = other.numberOfFaces;
    this->numberOfBoundaries = other.numberOfBoundaries;
    this->points = other.points;
    this->cells = other.cells;
    this->faces = other.faces;
    this->neighbor = other.neighbor;
    this->owner = other.owner;
    this->boundaries = other.boundaries;
    return *this;
}

void Mesh::meshGeneration()
{
    ShapeType shapetype=meshInfo.meshShape.getShape();
    switch(shapetype)
    {
        case RECTANGULAR:
        case TRAPEZE:
            cubicGeneratior();
            break;
        case CYLINDER:
        case OVAL:
            cylinderGeneratior();
            break;
        case SPHERIC:
            sphericGenerator();
            break;
        //default:

    }
}

