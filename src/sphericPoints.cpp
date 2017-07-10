#include "../include/Mesh.h"


void Mesh::topPartPoints() {
    double R = DIM(1);
    double p2 = 0.5/sqrt(2.0);
    double corner = 0.5 - p2*(1.0 - tan(PI/6.0))/sqrt(2.0);
    double sizeM = 2.0/(double)(NODE(0)/4);
    double sizeC = 2.0*corner/(double)(NODE(0)/4);
    double sizeM2, norm, R2;
    unsigned sidePoints = NODE(0)/8;

    TypeVector<double> point, unit;

    for (double x = -1.0, x2 = -corner; x <= 1.0 + EPS; x+= sizeM, x2+= sizeC) {

        for (double y = -1.0, y2 = -corner; y <= 1.0 + EPS; y+= sizeM, y2+= sizeC) {
            point = this->cubic2Spheric(x, y, 1.0);
            unit = point;
            point-= TypeVector<double>(x2, y2, corner);
            norm = point.norm();
            sizeM2 = norm/(double)sidePoints;
            R2 = 1.0 - norm + sizeM2;

            for( double step = 1.0; step >= R2 - EPS; step-= sizeM2) {
                this->addPoint(unit*(step*R));
            }
        }
    }
}

void Mesh::leftRightBotPartsPoints() {
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned layer = sidePoints*edgePoints;
    unsigned base = layer*edgePoints;
    double angle;
    TypeVector<double> axis;
    Point point;

    //right part
    angle = PI/2.0;
    axis = TypeVector<double>(0.0, 1.0, 0.0);

    for(unsigned i = layer; i < base; i++) {
        point = this->points[i].rotate(angle, axis);
        this->addPoint(point);
    }

    //bottom part
    angle = PI;

    for(unsigned i = layer; i < base; i++) {
        point = this->points[i].rotate(angle, axis);
        this->addPoint(point);
    }

    //left part
    angle = 3.0*PI/2.0;

    for(unsigned i = layer; i < base - layer; i++) {
        point = this->points[i].rotate(angle, axis);
        this->addPoint(point);
    }
}

void Mesh::frontRearPartsPoints() {
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned layer = sidePoints*edgePoints;
    unsigned base = layer*edgePoints;
    double angle, startp, endp;
    TypeVector<double> axis;
    Point point;

    //front part
    angle = 3.0*PI/2.0;
    axis = TypeVector<double>(0.0, 0.0, 1.0);

    for(unsigned j = 0; j < edgePoints - 2; j++){
        startp = base + j*layer + sidePoints;
        endp = startp + (edgePoints - 2)*sidePoints;
        for(unsigned i = startp; i < endp; i++) {
            point = this->points[i].rotate(angle, axis);
            this->addPoint(point);
        }
    }

    //rear part
    angle = PI/2.0;
    axis = TypeVector<double>(-1.0, 0.0, 0.0);
    for(unsigned j = 0; j < edgePoints - 2; j++) {
        startp = (j + 1)*layer + sidePoints;
        endp = startp + (edgePoints - 2)*sidePoints;
        for(unsigned i = startp; i < endp; i++) {
            point = this->points[i].rotate(angle, axis);
            this->addPoint(point);
        }
    }
}


void Mesh::cubicPartPoints() {
    double R = DIM(1);
    double halfR = 0.5*R;
    double p2 = halfR/sqrt(2.0);
    double corner = halfR - p2*(1.0 - tan(PI/6.0))/sqrt(2.0);
    double sizeC = 2.0*corner/(double)(NODE(0)/4);

    for(double z = corner; z >= -corner - EPS; z-= sizeC) {

        for(double x = -corner; x <= corner + EPS; x+= sizeC) {

            for(double y = -corner; y <= corner + EPS; y+= sizeC) {
                this->addPoint(x, y , z);
            }
        }
    }
}


TypeVector<double> Mesh::cubic2Spheric(double x, double y, double z) {
    double xx = x*x;
    double yy = y*y;
    double zz = z*z;
    return TypeVector<double>(x*sqrt(1.0 - yy/2.0 - zz/2.0 + yy*zz/3.0),
                              y*sqrt(1.0 - xx/2.0 - zz/2.0 + xx*zz/3.0),
                              z*sqrt(1.0 - xx/2.0 - yy/2.0 + xx*yy/3.0));
}
