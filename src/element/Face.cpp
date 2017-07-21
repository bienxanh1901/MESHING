#include "../../include/Face.h"

Face::Face() {
    this->area = 0.0;
    this->normalVector = TypeVector<double>();
}

Face::~Face() {}

Face::Face(Point * pointArr, elemType type, unsigned nPoints, unsigned elemID) : Element(pointArr, type, nPoints, elemID) {
    this->geometryProperties();
}

Face::Face(const ContainerPoints& cPoints, elemType type, unsigned elemID) : Element(cPoints, type, elemID) {
    this->geometryProperties();
}

Face& Face::operator=(const Face& rhs)
{
    Element::operator=(rhs);
    this->area = rhs.area;
    this->normalVector = rhs.normalVector;
    return *this;
}

ostream& Face::printFaceProperties(ostream& out) {
    out << this->area << "\t" << this->centroid << "\t" << this->normalVector;
    return out;
}

void Face::geometryProperties() {
    this->center = Point();
    this->centroid = Point();
    this->normalVector = TypeVector<double>();
    this->area = 0.0;

    this->calcCenter();
    if(this->elementType == QUAD4) this->quadrilateralProperties();
    else if (this->elementType == TRI3) this->triangleProperties();
}
