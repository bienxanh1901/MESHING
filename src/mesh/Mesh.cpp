#include "../../include/Mesh.h"

Mesh::Mesh() {}

Mesh::~Mesh() {
    this->clear();
    this->shape.clear();
}

Mesh::Mesh(const Mesh& mesh) {
    this->shape = mesh.shape;
    this->meshInfo = mesh.meshInfo;
    this->points = mesh.points;
    this->cells = mesh.cells;
    this->faces = mesh.faces;
    this->neighbor = mesh.neighbor;
    this->owner = mesh.owner;
    this->boundaries = mesh.boundaries;
}

Mesh::Mesh(Shape& meshShape) : shape(meshShape) {

}


Mesh& Mesh::operator=(const Mesh& mesh) {

    if (this == &mesh) return *this;
    this->shape = mesh.shape;
    this->meshInfo = mesh.meshInfo;
    this->points = mesh.points;
    this->cells = mesh.cells;
    this->faces = mesh.faces;
    this->neighbor = mesh.neighbor;
    this->owner = mesh.owner;
    this->boundaries = mesh.boundaries;
    return *this;
}

void Mesh::clear() {

    this->meshInfo.clear();
    this->points.clear();
    this->cells.clear();
    this->faces.clear();
    this->neighbor.clear();
    this->owner.clear();
    this->boundaries.clear();
}

void Mesh::reMesh() {

    this->clear();
    this->meshGeneration();
}

void Mesh::meshGeneration()
{
    switch(shape.getShape())
    {
        case CUBOID:
        case TRAPEZIOD:
            cubicGenerator();
            break;
        case CYLINDER:
        case OVAL:
            cylinderGenerator();
            break;
        case SPHERIC:
            sphericGenerator();
            break;
        case INVALID__SHAPE:
        default:
            cout << "can't recognize the type of SHAPE!!!\n";

    }
}
