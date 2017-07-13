#ifndef FACE_H
#define FACE_H

#include "Element.h"

using namespace std;

class Face : public Element {
    public:
        Face();
        virtual ~Face();

        Face(const Face& p) : Element(p) {
            this->area = p.area;
            this->normalVector = p.normalVector;
        }

        Face(Point*, elemType, unsigned , unsigned );

        Face(const containerPoints&, elemType, unsigned = 0 );

        Face& operator=(const Face&);

        TypeVector<double> getNormalVector() {
            return this->normalVector;
        }

        double getArea() {
            return this->area;
        }
        ostream& printFaceProperties(ostream&);

    protected:

    private:
        double area;
        TypeVector<double> normalVector;

        void geometryProperties();
        void quadrilateralProperties();
        void triangleProperties();
        void quadrilateralArea();
        void quadrilateralCentroid();
        void quadrilateralNormal();
        void triangleArea();
        void triangleCentroid();
        void triangleNormal();
};

#endif // FACE_H
