#include "../include/Mesh.h"

Mesh::Mesh() {
    this->meshInfo.numberOfPoints = 0;
    this->meshInfo.numberOfCells = 0;
    this->meshInfo.numberOfFaces = 0;
    this->meshInfo.numberOfBoundaries = 0;
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
    this->meshInfo.numberOfPoints = other.numberOfPoints;
    this->meshInfo.numberOfCells = other.numberOfCells;
    this->meshInfo.numberOfFaces = other.numberOfFaces;
    this->meshInfo.numberOfBoundaries = other.numberOfBoundaries;
    this->points = other.points;
    this->cells = other.cells;
    this->faces = other.faces;
    this->neighbor = other.neighbor;
    this->owner = other.owner;
    this->boundaries = other.boundaries;
}

Mesh::Mesh(MeshInfomation& info) : meshInfo(info) {
    this->meshInfo.numberOfPoints = 0;
    this->meshInfo.numberOfCells = 0;
    this->meshInfo.numberOfFaces = 0;
    this->meshInfo.numberOfBoundaries = 0;
    meshGeneration();
}


Mesh& Mesh::operator=(const Mesh& other) {
    if (this == &other) return *this;
    this->meshInfo = other.meshInfo;
    this->meshInfo.numberOfPoints = other.numberOfPoints;
    this->meshInfo.numberOfCells = other.numberOfCells;
    this->meshInfo.numberOfFaces = other.numberOfFaces;
    this->meshInfo.numberOfBoundaries = other.numberOfBoundaries;
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
        //default:

    }
}

void Mesh::addPoint(double x, double y, double z) {
    this->points.push_back(Point(x, y, z, ++this->meshInfo.numberOfPoints));
}

void Mesh::addPoint(TypeVector<double> p) {
    this->points.push_back(Point(p, ++this->meshInfo.numberOfPoints));
}

void Mesh::addFace(containerPoints& p) {
    this->faces.push_back(Face(p, QUAD4, ++this->meshInfo.numberOfFaces));
    p.clear();
}

void Mesh::addFace(unsigned p1, unsigned p2, unsigned p3, unsigned p4) {
    containerPoints pointsList;
    pointsList.push_back(this->points[p1]);
    pointsList.push_back(this->points[p2]);
    pointsList.push_back(this->points[p3]);
    pointsList.push_back(this->points[p4]);
    this->faces.push_back(Face(pointsList, QUAD4, ++this->meshInfo.numberOfFaces));
    pointsList.clear();
}

void Mesh::addCell(containerPoints& p) {

    this->cells.push_back(Cell(p, HEX8, ++this->meshInfo.numberOfCells));
    p.clear();
}

void Mesh::addCell(unsigned p1, unsigned p2, unsigned p3, unsigned p4,
                          unsigned p5, unsigned p6, unsigned p7, unsigned p8) {
    containerPoints pointsList;
    pointsList.push_back(this->points[p1]);
    pointsList.push_back(this->points[p2]);
    pointsList.push_back(this->points[p3]);
    pointsList.push_back(this->points[p4]);
    pointsList.push_back(this->points[p5]);
    pointsList.push_back(this->points[p6]);
    pointsList.push_back(this->points[p7]);
    pointsList.push_back(this->points[p8]);
    this->cells.push_back(Cell(pointsList, HEX8, ++this->meshInfo.numberOfCells));
    pointsList.clear();
}

void Mesh::addOwner(unsigned CellOwner) {
    this->owner.push_back(CellOwner);
}

void Mesh::addNeighbor(unsigned CellNeighbor) {
    this->neighbor.push_back(CellNeighbor);
}
