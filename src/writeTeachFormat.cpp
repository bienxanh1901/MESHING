#include "../include/Mesh.h"

void Mesh::writeTEACHMesh() {
    writeMeshInfomation();
    writeTEACHPoints();
    writeTEACHCells();
    writeTEACHFaces();
    writeTEACHNeighbor();
    writeTEACHOwner();
    writeTEACHBoundaries();

}
void Mesh::writeMeshInfomation() {
    ofstream _out;
    _out.open("meshInfo.teach", std::ofstream::out);

    if(_out.is_open()) {
        _out << meshInfo;
        _out.close();
    }
}
void Mesh::writeTEACHPoints() {

    ofstream _out;
    _out.open("points.teach", std::ofstream::out);

    if(_out.is_open()) {
        _out << "Points data" << "\t" << this->numberOfPoints << "\n";
        for(containerPoints::iterator i = this->points.begin(); i != this->points.end(); i++) {
            _out << *(i) << "\n";
        }
        _out.close();
    }
}

void Mesh::writeTEACHCells() {
    ofstream _out;
    _out.open("cells.teach", std::ofstream::out);

    if(_out.is_open()) {
        _out << "Cells data" << "\t" << this->numberOfCells << "\n";
        for(containerCells::iterator it = this->cells.begin(); it != this->cells.end(); it++) {
            _out << *(it) << "\t";
            it->printCellProperties(_out) << "\n";
        }
        _out.close();
    }
}

void Mesh::writeTEACHFaces() {
    ofstream _out;
    _out.open("faces.teach", std::ofstream::out);
    if(_out.is_open()) {
        //Elements
        _out << "Faces data" << "\t" << this->numberOfFaces << "\n";
        for(containerFaces::iterator it = this->faces.begin(); it != this->faces.end(); it++) {
            _out << *(it) << "\t";
            it->printFaceProperties(_out) << "\n";
        }
         _out.close();
    }
}

void Mesh::writeTEACHBoundaries() {
    ofstream _out;
    _out.open("boundaries.teach", std::ofstream::out);

    unsigned start = numberOfInternalFaces + 1;
    unsigned i = 0;
    if(_out.is_open()){
        _out << "Boundaries data" << "\t" << this->numberOfBoundaries << "\n";
        for(containerIDs::iterator it = this->boundaries.begin(); it != this->boundaries.end(); it++) {
            _out << "Boundary_" << ++i << ":\n";
            _out << "start face:\t" << start << "\n";
            _out << "number of faces:\t" << *it << "\n";
            start+= *it;
        }
        _out.close();
    }
}

void Mesh::writeTEACHNeighbor() {
    ofstream _out;
    _out.open("neighbor.teach", std::ofstream::out);

    if(_out.is_open()) {
        _out << "Neighbour data" << "\t" << this->numberOfInternalFaces << "\n";
        for(containerIDs::iterator it = this->neighbor.begin(); it != this->neighbor.end(); it++) {
                _out << *it << "\n";
        }
        _out.close();
    }
}

void Mesh::writeTEACHOwner() {
    ofstream _out;
    _out.open("owner.teach", std::ofstream::out);

    if(_out.is_open()) {
        _out << "Owner data" << "\t" << this->numberOfFaces << "\n";
        for(containerIDs::iterator it = this->owner.begin(); it != this->owner.end(); it++) {
                _out << *it << "\n";
        }
        _out.close();
    }
}
