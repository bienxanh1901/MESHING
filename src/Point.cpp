#include "../include/Point.h"

Point& Point::operator= (const Point& p)
{
    (*this)(0) = p(0);
    (*this)(1) = p(1);
    (*this)(2) = p(2);
    this->ID = p.ID;
    return *this;
}

void Point::setID(unsigned ID)
{
    this->ID = ID;
}

unsigned Point::getID()
{
    return ID;
}
