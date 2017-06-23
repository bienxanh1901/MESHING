#include "../include/Shape.h"

Shape::Shape()
{
    typeOfShape = INVALID__SHAPE;
}

Shape::Shape(ShapeType type, double* dim):typeOfShape(type)
{
    //dim1
    *(this->Dimension) = *dim;

    //dim2
    if(type != SPHERIC) *(this->Dimension+1) = *(dim+1);
    else *(this->Dimension+1) = *(this->Dimension);

    //dim3
    if(type != SPHERIC && type != CYLINDER) *(this->Dimension+2) = *(dim+2);
    else *(this->Dimension+2) = *(this->Dimension);
}

Shape::~Shape()
{
}

Shape::Shape(const Shape& other)
{
    this->typeOfShape = other.typeOfShape;
    for(unsigned i = 0; i<3; i++)*(this->Dimension+i) = *(other.Dimension+i);
}

Shape& Shape::operator=(const Shape& rhs)
{
    if (this == &rhs) return *this;
    this->typeOfShape = rhs.typeOfShape;
    for(unsigned i = 0; i<3; i++) *(this->Dimension+i) = *(rhs.Dimension+i);
    return *this;
}


ShapeType Shape::getShape()
{
    return typeOfShape;
}

double Shape::getDimension(unsigned dim)
{
    if(dim <= 3) return Dimension[dim-1];
    return -1;
}
