#include "../include/Mesh.h"

Mesh::Mesh()
{
    this->numberOfNodes = 0;
    this->numberOfElems = 0;
    this->numberOfBoundaries = 0;
    this->numberOfFaces = 0;
}

Mesh::~Mesh()
{
    this->nodes.clear();
    this->elements.clear();
    this->boundaries.clear();
    this->faces.clear();
}

Mesh::Mesh(const Mesh& other)
{
    this->numberOfNodes = other.numberOfNodes;
    this->numberOfElems = other.numberOfElems;
    this->numberOfBoundaries = other.numberOfBoundaries;
    this->numberOfFaces = other.numberOfFaces;
    this->meshInfo = other.meshInfo;
    this->nodes = other.nodes;
    this->elements = other.elements;
    this->boundaries = other.boundaries;
    this->faces = other.faces;
}

Mesh::Mesh(MeshInfomation& info):meshInfo(info)
{
    this->numberOfNodes = 0;
    this->numberOfElems = 0;
    this->numberOfFaces = 0;
    this->setNumberOfBoundaries();
    meshGeneration();
}


Mesh& Mesh::operator=(const Mesh& rhs)
{
    if (this == &rhs) return *this;

    this->meshInfo = rhs.meshInfo;
    this->numberOfNodes = rhs.numberOfNodes;
    this->numberOfElems = rhs.numberOfElems;
    this->numberOfFaces = rhs.numberOfFaces;
    this->numberOfBoundaries = rhs.numberOfBoundaries;
    this->nodes = rhs.nodes;
    this->elements = rhs.elements;
    this->faces = rhs.faces;
    this->boundaries = rhs.boundaries;

    return *this;
}

void Mesh::setNumberOfBoundaries()
{
    ShapeType shapetype=meshInfo.meshShape.getShape();
    switch(shapetype)
    {
        case RECTANGULAR:
        case TRAPEZE:
            numberOfBoundaries = 6;
            break;
        case CYLINDER:
        case OVAL:
            numberOfBoundaries = 3;
            break;
        case SPHERIC:
            numberOfBoundaries = 1;
            break;
        //default:

    }
}

void Mesh::meshGeneration()
{
    ShapeType shapetype=meshInfo.meshShape.getShape();
    switch(shapetype)
    {
        case RECTANGULAR:
        case TRAPEZE:
            cubicGeneration();
            break;
        case CYLINDER:
        case OVAL:
            cylinderGeneration();
            break;
        case SPHERIC:
            sphericGeneration();
            break;
        //default:

    }
}

