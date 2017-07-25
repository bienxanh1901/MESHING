#include "../../include/Cell.h"

Cell::Cell() {
    this->volume = 0.0;
}

Cell::~Cell() {}

Cell::Cell(Point * pointArr, elemType type, unsigned nPoints, unsigned elemID) : Element(pointArr, type, nPoints, elemID) {
    this->geometryProperties();
}

Cell::Cell(const ContainerPoints& cPoints, elemType type, unsigned elemID) : Element(cPoints, type, elemID) {
    this->geometryProperties();
}

Cell& Cell::operator=(const Cell& rhs) {
    Element::operator=(rhs);
    this->volume = rhs.volume;
    return *this;
}

ostream& Cell::printCellProperties(ostream& out) {

    out << this->centroid << "\t" << this->volume;
    return out;
}

void Cell::geometryProperties() {
    this->center = Point();
    this->centroid = Point();
    this->volume = 0.0;

    this->calcCenter();
    if(elementType == HEX8) hexahedralProperties();
    else if (elementType == TET4) tetrahedralProperties();
}

void Cell::calcVolumeCentroid(ContainerFaces& faces) {
    TypeVector<double> vec1;
    double sign;
    double intergal;
    for(ContainerFaces::iterator it = faces.begin(); it != faces.end(); it++)
    {
        vec1 = this->center - it->getCentroid();
        sign = vec1*it->getNormalVector();
        if(sign>0) intergal = -(it->getCentroid()*it->getNormalVector())*it->getArea();
        else intergal = (it->getCentroid()*it->getNormalVector())*it->getArea();
        this->volume += intergal;
        this->centroid += it->getCentroid()*intergal;
    }
    this->volume/=3.0;
    this->centroid/=(4.0*this->volume);
}

ContainerPoints Cell::findFace(unsigned vertice1, unsigned vertice2, unsigned vertice3, unsigned vertice4)
{
    ContainerPoints result {this->points[vertice1], this->points[vertice2], this->points[vertice3]};
    if(this->elementType == HEX8) result.push_back(this->points[vertice4]);
    return result;
}

