#include "../include/Shape.h"

Shape::Shape() {

    this->type = INVALID__SHAPE;
    this->numberOfDims = 0;
    this->numberOfLayers = 0;

}

Shape::Shape(ShapeType typeS) : type(typeS) {

    this->numberOfLayers = 0;
    this->setNumberOfDims();

}


Shape::~Shape() {

    this->dim.clear();
    this->cellNumbers.clear();
    this->cellSizes.clear();
}

Shape::Shape(const Shape& shape) {

    this->type = shape.type;
    this->numberOfDims = shape.numberOfDims;
    this->numberOfLayers = shape.numberOfLayers;
    this->dim = shape.dim;
    this->cellNumbers = shape.cellNumbers;
    this->cellSizes = shape.cellSizes;
}

Shape& Shape::operator=(const Shape& shape) {
    if (this == &shape) return *this;

    this->type = shape.type;
    this->numberOfDims = shape.numberOfDims;
    this->numberOfLayers = shape.numberOfLayers;
    this->dim = shape.dim;
    this->cellNumbers = shape.cellNumbers;
    this->cellSizes = shape.cellSizes;

    return *this;
}

ShapeType Shape::getShape() {

    return this->type;

}

unsigned Shape::getNumberOfDims() {

    return this->numberOfDims;

}

arrDouble Shape::getDimOfLayers(unsigned layer) {

    assert(layer <= this->numberOfLayers)
    return this->dim[layer - 1];
}

void Shape::setNumberOfDims(){
    switch(this->)
    {
        case SPHERIC:
            this->numberOfDims = 1;
            break;
        case CYLINDER:
            this->numberOfDims = 2;
            break;
        case CUBOID:
        case OVAL:
            this->numberOfDimss = 3;
            break;
        case TRAPEZIOD:
            this->numberOfDimss = 5;
            break;
        default:
            this->numberOfDimss = 0;
    }
}

