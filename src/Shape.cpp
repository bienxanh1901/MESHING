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

    this->clear();
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

unsigned Shape::getNumberOfLayers() {

    return this->numberOfLayers;

}

void Shape::clear() {

    this->type = INVALID__SHAPE;
    this->numberOfDims = 0;
    this->numberOfLayers = 0;
    this->dim.clear();
    this->cellNumbers.clear();
    this->cellSizes.clear();

}

arrDouble& Shape::getSizesOfLayer(unsigned layer) {

    assert(layer <= this->numberOfLayers);
    return this->cellSizes[layer - 1];
}

arrDouble& Shape::getDimsOfLayer(unsigned layer) {

    assert(layer <= this->numberOfLayers);
    return this->dim[layer - 1];
}

arrUnsgn& Shape::getCellNumbersOfLayer(unsigned layer) {

    assert(layer <= this->numberOfLayers);
    return this->cellNumbers[layer - 1];
}

void Shape::setNumberOfDims(){
    switch(this->type)
    {
        case SPHERIC:
            this->numberOfDims = 1;
            break;
        case CYLINDER:
            this->numberOfDims = 2;
            break;
        case CUBOID:
        case OVAL:
            this->numberOfDims = 3;
            break;
        case TRAPEZIOD:
            this->numberOfDims = 5;
            break;
        default:
            this->numberOfDims = 0;
    }
}

