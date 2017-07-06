#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include "../common/ShapeType.h"


using namespace std;

class Shape {
    public:
        Shape();
        Shape(ShapeType, double*);
        virtual ~Shape();
        Shape(const Shape&);
        Shape& operator=(const Shape&);
        ShapeType getShape();
        unsigned getNumberOfDimension();
        double getDimension(unsigned);
    protected:
    private:
        ShapeType typeOfShape;
        unsigned numberOfDimension;
        double dimension[5];

        void setNumberOfDimension();
};

#endif // SHAPE_H
