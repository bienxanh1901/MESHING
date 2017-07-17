#include "../../include/Mesh.h"

void Mesh::writeTEACHMesh() {

    this->writeMeshInfomation();
    this->writeTEACHPoints();
    this->writeTEACHCells();
    this->writeTEACHFaces();
    this->writeTEACHNeighbor();
    this->writeTEACHOwner();
    this->writeTEACHBoundaries();
    this->writeTEACHCellsOfLayer();


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

        _out << "Points data" << "\t" << this->meshInfo.numberOfPoints << "\n";

        forAllIter(containerPoints, this->points, it) {

            _out << *(it) << "\n";

        }
        _out.close();

    }

}

void Mesh::writeTEACHCells() {

    ofstream _out;
    _out.open("cells.teach", std::ofstream::out);

    if(_out.is_open()) {

        _out << "Cells data" << "\t" << this->meshInfo.numberOfCells << "\n";

        forAllIter(containerCells, this->cells, it) {

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

        _out << "Faces data" << "\t" << this->meshInfo.numberOfFaces << "\n";

        forAllIter(containerFaces, this->faces, it) {

            _out << *(it) << "\t";
            it->printFaceProperties(_out) << "\n";

        }
         _out.close();
    }

}

void Mesh::writeTEACHBoundaries() {
    ofstream _out;
    _out.open("boundaries.teach", std::ofstream::out);


    if(_out.is_open()){
        unsigned start = this->meshInfo.numberOfInternalFaces + 1;
        unsigned i = 0;

        _out << "Boundaries data" << "\t" << this->meshInfo.numberOfBoundaries << "\n";

        forAllIter(containerIDs, this->boundaries, it) {

            _out << "Boundary_" << ++i << ":\n";
            _out << "start_face:\t" << start << "\n";
            _out << "nFaces:\t" << *it << "\n";
            start+= *it;

        }
        _out.close();
    }

}


void Mesh::writeTEACHCellsOfLayer() {
    ofstream _out;
    _out.open("layer.teach", std::ofstream::out);


    if(_out.is_open()){

        unsigned start = 1, i = 0;

        _out << "layers data" << "\t" << this->shape.getNumberOfLayers() << "\n";

        forAllIter(containerIDs, this->cellsOfLayer, it) {

            _out << "layer_" << ++i << ":\n";
            _out << "start_cells:\t" << start << "\n";
            _out << "nCells:\t" << *it << "\n";
            start+= *it;

        }
        _out.close();
    }

}


void Mesh::writeTEACHNeighbor() {

    ofstream _out;
    _out.open("neighbor.teach", std::ofstream::out);

    if(_out.is_open()) {

        _out << "Neighbour data" << "\t" << this->meshInfo.numberOfInternalFaces << "\n";

        forAllIter(containerIDs, this->neighbor, it) {

                _out << *it << "\n";

        }
        _out.close();
    }

}

void Mesh::writeTEACHOwner() {

    ofstream _out;
    _out.open("owner.teach", std::ofstream::out);

    if(_out.is_open()) {

        _out << "Owner data" << "\t" << this->meshInfo.numberOfFaces << "\n";

        forAllIter(containerIDs, this->owner, it) {

                _out << *it << "\n";

        }
        _out.close();
    }

}
