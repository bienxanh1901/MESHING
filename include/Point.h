#ifndef POINT_H
#define POINT_H

#include "typeVector.h"


class Point : public typeVector<double>
{
    public:
        Point(const double x= 0.0, const double y= 0.0, const double z= 0.0) :
        typeVector<double> (x,y,z) {}
        virtual ~Point() {}
        Point(const Point& p) :
        typeVector<double> (p) {}
        Point(const typeVector<double>& p ) :
        typeVector<double> (p) {}
    protected:
        friend class Node;
    private:
};

#endif // POINT_H
