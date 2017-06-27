#include "../include/MeshInfomation.h"

MeshInfomation::MeshInfomation() {
    for(int i=0; i<3; i++) {
        *(meshSize+i) = 0.0;
        *(meshNode+i) = 0;
    }
}

MeshInfomation::~MeshInfomation() {}

MeshInfomation::MeshInfomation(Shape& shape, double* ptrsize) : meshShape(shape) {
    ShapeType type = shape.getShape();

    //dim1
    *(this->meshSize) = *ptrsize;

    //dim2
    if(type != SPHERIC) *(this->meshSize+1) = *(ptrsize+1);
    else *(this->meshSize+1) = *(this->meshSize);

    //dim3
    if(type != SPHERIC && type != CYLINDER) *(this->meshSize+2) = *(ptrsize+2);
    else *(this->meshSize+2) = *(this->meshSize);

    calculateNodenumbers();
}

MeshInfomation::MeshInfomation(const MeshInfomation& other) {
    meshShape = other.meshShape;
    for(int i=0; i<3; i++) {
        *(meshSize+i) = *(other.meshSize+i);
        *(meshNode+i) = *(other.meshNode+i);
    }
}

MeshInfomation& MeshInfomation::operator=(const MeshInfomation& rhs) {
    if (this == &rhs) return *this;

    meshShape = rhs.meshShape;
    for(int i=0; i<3; i++) {
        *(meshSize+i) = *(rhs.meshSize+i);
        *(meshNode+i) = *(rhs.meshNode+i);
    }
    return *this;
}

void MeshInfomation::calculateNodenumbers() {
    double dim = this->meshShape.getDimension(1);
    ShapeType shape = meshShape.getShape();
    if(shape==CYLINDER || shape==OVAL || shape==SPHERIC) dim = dim*PI;
    //dim1
    meshNode[0] = (unsigned)ROUNDED( dim / meshSize[0], 0.0);

    // In case CYLINDER or SPHERIC or OVAL, the node must greater than 8
    // and be the multiples of 8
    if(shape==CYLINDER || shape==OVAL || shape==SPHERIC) {
        if(meshNode[0] < 8) meshNode[0] = 8;
        meshNode[0] =(meshNode[0]/8 +1 )*8;
    }

    meshSize[0] = dim/(double)meshNode[0];


    //dim2
    if(shape != SPHERIC) {
        dim = this->meshShape.getDimension(2);
        meshNode[1] = (unsigned)ROUNDED( dim / meshSize[1], 0.0);
        meshSize[1] = dim/(double)meshNode[1];
    } else {
        meshNode[1] = meshNode[0];
        meshSize[1] = meshSize[0];
    }

    //dim3
    if(shape != SPHERIC && shape != CYLINDER && shape != OVAL) {
        dim = this->meshShape.getDimension(3);
        meshNode[2] = (unsigned)ROUNDED( dim / meshSize[2], 0.0);
        meshSize[2] = dim/(double)meshNode[2];
    } else {
        meshNode[2] = meshNode[0];
        meshSize[2] = meshSize[0];
    }
}

ostream& MeshInfomation::print(ostream& out) {
    out << "Shape: " << this->meshShape.getShape() << endl;
    for(unsigned i = 1; i <= this->meshShape.getNumberOfDimension(); i++) {
        out << "Dim_" << i << ":\t" << this->meshShape.getDimension(i) << "(m)" << endl;
    }
    out << endl;
    for(unsigned i = 0; i < 3; i++) {
        out << "points_number_" << i + 1 << ":\t" << this->meshNode[i]  << endl;
        out << "size_" << i + 1 << ":\t" << this->meshSize[i]  << endl;
    }
    return out;
}
