#include "../../include/Mesh.h"

void Mesh::addPoint(double x, double y, double z) {

    this->points.push_back(Point(x, y, z, ++this->meshInfo.numberOfPoints));

}

void Mesh::addPoint(TypeVector<double> p) {

    this->points.push_back(Point(p, ++this->meshInfo.numberOfPoints));

}

void Mesh::addFace(ContainerPoints& p) {

    this->faces.push_back(Face(p, QUAD4, ++this->meshInfo.numberOfFaces));
    p.clear();

}

void Mesh::addFace(unsigned p1, unsigned p2, unsigned p3, unsigned p4) {

<<<<<<< HEAD
    ContainerPoints pointsList;
    pointsList.push_back(this->points[p1]);
    pointsList.push_back(this->points[p2]);
    pointsList.push_back(this->points[p3]);
    pointsList.push_back(this->points[p4]);
=======
    ContainerPoints pointsList {this->points[p1], this->points[p2], this->points[p3], this->points[p4]};
>>>>>>> meshgrading
    this->faces.push_back(Face(pointsList, QUAD4, ++this->meshInfo.numberOfFaces));
    pointsList.clear();

}

void Mesh::addCell(ContainerPoints& p) {

    this->cells.push_back(Cell(p, HEX8, ++this->meshInfo.numberOfCells));
    p.clear();

}

void Mesh::addCell(unsigned p1, unsigned p2, unsigned p3, unsigned p4,
                   unsigned p5, unsigned p6, unsigned p7, unsigned p8) {

<<<<<<< HEAD
    ContainerPoints pointsList;
    pointsList.push_back(this->points[p1]);
    pointsList.push_back(this->points[p2]);
    pointsList.push_back(this->points[p3]);
    pointsList.push_back(this->points[p4]);
    pointsList.push_back(this->points[p5]);
    pointsList.push_back(this->points[p6]);
    pointsList.push_back(this->points[p7]);
    pointsList.push_back(this->points[p8]);
=======
    ContainerPoints pointsList {this->points[p1], this->points[p2], this->points[p3], this->points[p4],
                                this->points[p5], this->points[p6], this->points[p7], this->points[p8]};
>>>>>>> meshgrading
    this->cells.push_back(Cell(pointsList, HEX8, ++this->meshInfo.numberOfCells));
    pointsList.clear();
}

void Mesh::addOwner(unsigned CellOwner) {

    this->owner.push_back(CellOwner);

}

void Mesh::addNeighbor(unsigned CellNeighbor) {

    this->neighbor.push_back(CellNeighbor);

}

TypeVector<double> Mesh::cubic2Spheric(double x, double y, double z) {

    double xx = x*x;
    double yy = y*y;
    double zz = z*z;
    return TypeVector<double>(x*sqrt(1.0 - yy/2.0 - zz/2.0 + yy*zz/3.0),
                              y*sqrt(1.0 - xx/2.0 - zz/2.0 + xx*zz/3.0),
                              z*sqrt(1.0 - xx/2.0 - yy/2.0 + xx*yy/3.0));

}
