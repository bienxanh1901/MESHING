#ifndef ELEMENT_H
#define ELEMENT_H

#include<iostream>
#include<vector>
#include "Node.h"
#include "Point.h"
#include "../common/element_type.h"
#include "../define/define.h"

using namespace std;

class Element{
    public:
        Element();
        Element(const Element& );
        Element(Node*, elemType, unsigned , unsigned );
        Element(const vector<Node>&, elemType, unsigned );
        virtual ~Element();
        Element& operator=(const Element&);

        void clear();
        void setID(unsigned);
        bool operator==(Element);

        unsigned getID();
        ostream& print(ostream&);
        ostream& printFace(ostream&);
        ostream& printNode(ostream&);
        elemType getType();
        double getVolume();
        double getArea();
        Point getCenter();
        Point getCentroid();
        Node& getNode(unsigned);
        Element& getFace(unsigned);
        Element* getReference();
        typeVector<double> getNormalVector();
        void addNeighbor(unsigned);
        vector<unsigned> getNeighbor();
        virtual void geometryProperties();
    protected:
        friend ostream& operator<<(ostream& out,Element& e){
            return e.print(out);
        }
    private:
        typedef vector<Node> containerNodes;
        typedef vector<Element> containerElements;
        typedef vector<unsigned> containerIDs;
        unsigned numberOfFaces;
        unsigned numberOfNodes;
        unsigned ID;
        elemType elementType;
        containerNodes nodes;
        containerElements faces;
        containerIDs neighbors;
        double area;
        double volume;
        Point centroid;
        Point center;
        typeVector<double> norm;

        // internal Function
        void faceProperties();
        void cellProperties();
        void triangleProperties();
        void quadrilateralProperties();
        void tetrahedralProperties();
        void hexahedralProperties();

        void quadrilateralArea();
        void triangleArea();

        void quadrilateralCentroid();
        void triangleCentroid();

        void triangleNormal();
        void quadrilateralNormal();

        void setFaceOfHexahedral();
        void setFaceOfTetrahedral();
        void calcCenter();
        vector<Node> findFace(unsigned, unsigned, unsigned, unsigned = 0);
        void calcVolumeCentroid();
};

#endif // ELEMENT_H
