#include "Node.h"

Node::Node()
{
    // default ctor
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

Node::Node(double xcoor, double ycoor, double zcoor)
{
    //ctor
    x = xcoor;
    y = ycoor;
    z = zcoor;
}

Node::Node(const Node& P)
{
    //copy ctor
    x = P.x;
    y = P.y;
    z = P.z;
}

Node::~Node()
{
    //dtor
}

Node& Node::operator=(const Node & P)
{
    //assign operator
    x = P.x;
    y = P.y;
    z = P.z;
    return *this;
}

Node& Node::operator+(const Node& P)
{
    //Plus operator
    x = x + P.x;
    y = y + P.y;
    z = z + P.z;
    return *this;
}

Node& Node::operator-(const Node& P)
{
    //Plus operator
    x = x - P.x;
    y = y - P.y;
    z = z - P.z;
    return *this;
}
