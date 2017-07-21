#include "../../include/MeshInfomation.h"

MeshInfomation::MeshInfomation() {

    this->numberOfPoints = 0;
    this->numberOfFaces = 0;
    this->numberOfInternalFaces = 0;
    this->numberOfCells = 0;
    this->numberOfBoundaries = 0;
}

MeshInfomation::MeshInfomation(const MeshInfomation& info) {

    this->numberOfPoints = info.numberOfPoints;
    this->numberOfFaces = info.numberOfFaces;
    this->numberOfInternalFaces = info.numberOfInternalFaces;
    this->numberOfCells = info.numberOfCells;
    this->numberOfBoundaries = info.numberOfBoundaries;
}


MeshInfomation::~MeshInfomation() { }

MeshInfomation& MeshInfomation::operator=(const MeshInfomation& info) {

    if(*this == info) return *this;

    this->numberOfPoints = info.numberOfPoints;
    this->numberOfFaces = info.numberOfFaces;
    this->numberOfInternalFaces = info.numberOfInternalFaces;
    this->numberOfCells = info.numberOfCells;
    this->numberOfBoundaries = info.numberOfBoundaries;

    return *this;
}

bool MeshInfomation::operator==(const MeshInfomation& info) {


    if(this->numberOfPoints != info.numberOfPoints) return false;
    if(this->numberOfFaces != info.numberOfFaces) return false;
    if(this->numberOfInternalFaces != info.numberOfInternalFaces) return false;
    if(this->numberOfCells != info.numberOfCells) return false;
    if(this->numberOfBoundaries != info.numberOfBoundaries) return false;

    return true;
}


void MeshInfomation::clear() {

    this->numberOfPoints = 0;
    this->numberOfFaces = 0;
    this->numberOfInternalFaces = 0;
    this->numberOfCells = 0;
    this->numberOfBoundaries = 0;
}

ostream& MeshInfomation::print(ostream& out) {

    out << "Number of points:\t\t\t\t" << this->numberOfPoints << endl;
    out << "Number of cell:\t\t\t\t\t" << this->numberOfCells << endl;
    out << "Number of internal faces:\t\t" << this->numberOfInternalFaces << endl;
    out << "Number of boundary faces:\t\t" << this->numberOfFaces - this->numberOfInternalFaces << endl;
    out << "Number of boundaries:\t\t\t" << this->numberOfBoundaries << endl;

    return out;
}
