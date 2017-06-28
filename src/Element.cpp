#include "../include/Element.h"

Element::Element() {
    this->ID = 0;
    this->numberOfPoints = 0;
    this->elementType = INVALID_ELEM;
}

Element::~Element(){
    this->points.clear();
}

Element::Element(const Element& other) {
    this->ID = other.ID;
    this->numberOfPoints = other.numberOfPoints;
    this->elementType = other.elementType;
    this->center = other.center;
    this->centroid = other.centroid;
    this->points = other.points;
}

Element::Element(Point * pointArr, elemType type, unsigned nPoints, unsigned elemID) {
    this->elementType = type;
    this->ID = elemID;
    this->numberOfPoints = nPoints;
    for(unsigned i=0; i<nPoints; i++)
    {
        (this->points).push_back(*(pointArr+i));
    }
}

Element::Element(const containerPoints& cPoints, elemType type, unsigned elemID) {
    this->elementType = type;
    this->ID = elemID;
    this->numberOfPoints = cPoints.size();
    this->points = cPoints;
}

Element& Element::operator=(const Element& other) {
    this->ID = other.ID;
    this->numberOfPoints = other.numberOfPoints;
    this->elementType = other.elementType;
    this->center = other.center;
    this->centroid = other.centroid;
    this->points = other.points;
    return *this;
}

void Element::clear() {
    this->ID = 0;
    this->numberOfPoints = 0;
    this->elementType = INVALID_ELEM;
    this->points.clear();
    this->center = Point();
    this->centroid = Point();
}

void Element::setID(unsigned ID) {
    this->ID = ID;
}

unsigned Element::getID() {
    return this->ID;
}

unsigned Element::getNumberOfPoints() {
    return this->numberOfPoints;
}

Point& Element::getPoint(unsigned ith) {
    return this->points[ith];
}

containerPoints Element::getPointsList() {
    return this->points;
}

elemType Element::getType() {
    return this->elementType;
}

Point Element::getCenter(){
    return this->center;
}

Point Element::getCentroid(){
    return this->centroid;
}

void Element::calcCenter() {
    for(containerPoints::iterator it = this->points.begin(); it != this->points.end(); it++) {
        this->center+= *it;
    }
    this->center/=(double)this->numberOfPoints;
}

bool Element::operator ==(Element elem) {
    if(this->elementType != elem.elementType) return false;
    unsigned cnt = 0;
    containerPoints other = elem.getPointsList();
    for(containerPoints::iterator it = this->points.begin(); it != this->points.end(); it++) {
        for(containerPoints::iterator it2 = other.begin(); it2 != other.end(); it2++) {
            if(*it == *it2) cnt++;
        }
    }
    if(cnt == this->numberOfPoints) return true;
    return false;
}

ostream& Element::print(ostream& out) {
    for(containerPoints::iterator it = this->points.begin(); it != this->points.end(); it++) {
        out << it->getID() << " ";
    }
    return out;
}

ostream& Element::printPointsIDParaview(ostream& out){
    for(containerPoints::iterator it = this->points.begin(); it != this->points.end(); it++) {
        out << it->getID() - 1 << " ";
    }
    return out;
}
