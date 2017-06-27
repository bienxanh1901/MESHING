#ifndef ELEMENT_H
#define ELEMENT_H

#include<iostream>
#include<vector>
#include "Point.h"
#include "../common/element_type.h"
#include "../define/define.h"

using namespace std;

class Element{
    public:
        Element();
        Element(const Element& );
        Element(Point*, elemType, unsigned , unsigned );
        Element(const vector<Point>&, elemType, unsigned );
        virtual ~Element();
        Element& operator=(const Element&);

        void clear();
        void setID(unsigned);
        bool operator==(Element);
        unsigned getID();
        ostream& print(ostream&);
        ostream& printPointsIDParaview(ostream&);
        elemType getType();
        Point getCenter();
        Point getCentroid();
        Point& getPoint(unsigned);
        containerPoints getPointList();
        Element* getReference();
    protected:
        Point centroid;
        Point center;
        unsigned numberOfPoints;
        unsigned ID;
        elemType elementType;
        containerPoints points;
        void calcCenter();

        friend ostream& operator<<(ostream& out,Element& e) {
            return e.print(out);
        }
    private:


};

#endif // ELEMENT_H
