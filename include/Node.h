#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <fstream>
#include "Point.h"
using namespace std;

class Node : public Point
{
    public:
        explicit
        Node(unsigned n=0, const double x= 0.0, const double y= 0.0, const double z= 0.0) : Point(x,y,z)
        { this->ID = n;}

        Node(const Node& p) : Point(p) {this->ID = p.ID;}

        explicit
        Node(const Point& p, unsigned n= 0) : Point(p)
        { this->ID = n;}

        virtual ~Node() {}

        Node& operator=(const Point&);

        unsigned getID();
        void setID(unsigned);
    protected:
    private:
        unsigned ID;
};

#endif // NODE_H
