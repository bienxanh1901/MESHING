#include "../include/Shape.h"

Shape::Shape() {
    typeOfShape = INVALID__SHAPE;
}

Shape::Shape(ShapeType type, double* dim) : typeOfShape(type) {

    this->setNumberOfDimension();

    //dim1
    *(this->dimension) = *dim;
    //dim2
    if(type != SPHERIC) *(this->dimension+1) = *(dim+1);
    else *(this->dimension+1) = *(this->dimension);
    //dim3
    if(type != SPHERIC && type != CYLINDER) *(this->dimension+2) = *(dim+2);
    else *(this->dimension + 2) = *(this->dimension);
    //dim4 & dim5
    if(type == TRAPEZE) {
        *(this->dimension + 3) = *(dim + 3);
        *(this->dimension + 4) = *(dim + 4);
    }
}

Shape::~Shape() {}

Shape::Shape(const Shape& other) {
    this->typeOfShape = other.typeOfShape;
    this->numberOfDimension = other.numberOfDimension;

    for(unsigned i = 0; i < numberOfDimension; i++)
        *(this->dimension+i) = *(other.dimension+i);
}

Shape& Shape::operator=(const Shape& other) {
    if (this == &other) return *this;

    this->typeOfShape = other.typeOfShape;
    this->numberOfDimension = other.numberOfDimension;

    for(unsigned i = 0; i < numberOfDimension; i++)
        *(this->dimension+i) = *(other.dimension+i);

    return *this;
}

ShapeType Shape::getShape(){ return this->typeOfShape;}

unsigned Shape::getNumberOfDimension(){ return this->numberOfDimension;}

double Shape::getDimension(unsigned dim) {
    if(dim <= this->numberOfDimension) return this->dimension[dim-1];
    return -1;
}

void Shape::setNumberOfDimension(){
    switch(typeOfShape)
    {
        case SPHERIC:
        case CYLINDER:
        case RECTANGULAR:
        case OVAL:
            numberOfDimension = 3;
            break;
        case TRAPEZE: numberOfDimension = 5; break;
        default:
            numberOfDimension = 0;
    }
}
