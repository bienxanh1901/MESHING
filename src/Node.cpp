#include "../include/Node.h"

Node& Node::operator= (const Point& p)
{
    (*this)(0) = p(0);
    (*this)(1) = p(1);
    (*this)(2) = p(2);
    return *this;
}

void Node::setID(unsigned ID)
{
    this->ID = ID;
}

unsigned Node::getID()
{
    return ID;
}
