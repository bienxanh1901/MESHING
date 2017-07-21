#ifndef POINT_H
#define POINT_H

#include "typeVector.h"


class Point : public TypeVector<double>
{
    public:
        Point(const double x= 0.0, const double y= 0.0, const double z= 0.0, unsigned n = 0) : TypeVector<double> (x,y,z) {
            this->ID = n;
        }

        virtual ~Point() {}

        Point(const Point& p) : TypeVector<double> (p) {
            this->ID = p.ID;
        }

        Point(const TypeVector<double>& p, unsigned n = 0) : TypeVector<double> (p) {
            this->ID = n;
        }

        Point& operator=(const Point&);

        unsigned getID();

        void setID(unsigned);

    protected:

    private:
        unsigned ID;
};

#endif // POINT_H
