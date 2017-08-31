#include "../../include/Element.h"

Element::Element() {

    this->ID = 0;
    this->numberOfPoints = 0;
    this->elementType = INVALID_ELEM;

}

Element::~Element() {

    this->clear();

}

Element::Element(const Element& other) {

    this->ID = other.ID;
    this->numberOfPoints = other.numberOfPoints;
    this->elementType = other.elementType;
    this->center = other.center;
    this->centroid = other.centroid;
    this->points = other.points;

}


Element::Element(const ContainerPrtPoints& prtPoints, elemType type, unsigned elemID) {

    this->elementType = type;
    this->ID = elemID;
    this->numberOfPoints = prtPoints.size();
    this->points = prtPoints;

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

    return *(this->points[ith]);

}

Point* Element::getPrtPoint(unsigned ith) {

    return this->points[ith];

}

ContainerPrtPoints Element::getPrtPointsList() {

    return this->points;

}

ContainerIDs Element::getPointsIDList() {

    ContainerIDs IDList;
    forAllIter(ContainerPrtPoints, this->points, it) {

        IDList.push_back((*it)->getID());

    }
    return IDList;

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

    forAllIter(ContainerPrtPoints, this->points, it) {

        this->center+= *(*it);

    }
    this->center/=(double)this->numberOfPoints;
}

bool Element::operator ==(Element elem) {

    if(this->elementType != elem.elementType) return false;

    unsigned cnt = 0;

    ContainerPrtPoints other = elem.getPrtPointsList();
    forAllIter(ContainerPrtPoints, this->points, it) {

        forAllIter(ContainerPrtPoints, other, it2) {

            if(*it == *it2) cnt++;

        }

    }

    if(cnt == this->numberOfPoints) return true;
    return false;
}

ostream& Element::print(ostream& out) {

    forAllIter(ContainerPrtPoints, this->points, it) {

        out << (*it)->getID() << " ";

    }

    return out;
}

ostream& Element::printPointsIDParaview(ostream& out){

    forAllIter(ContainerPrtPoints, this->points, it) {

        out << (*it)->getID() - 1 << " ";

    }

    return out;
}
