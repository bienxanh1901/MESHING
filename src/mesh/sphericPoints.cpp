#include "../../include/Mesh.h"


void Mesh::topPartPoints() {

    arrDouble dim(DIM(1));
    arrUnsgn cellNums(CELL(1));
    double R = dim[0];
    double corner = 1.0*tan(PI/6.0)/2.0;
    double sizeM = 2.0/(double)(cellNums[0]/4);
    double sizeC = 2.0*corner/(double)(cellNums[0]/4);


    for (double x = -1.0, x2 = -corner; x <= 1.0 + EPS; x+= sizeM, x2+= sizeC) {

        for (double y = -1.0, y2 = -corner; y <= 1.0 + EPS; y+= sizeM, y2+= sizeC) {

            TypeVector<double> unit(this->cubic2Spheric(x, y, 1.0));
            TypeVector<double> point(unit - TypeVector<double>(x2, y2, corner));
            double sizeM2 = point.norm()/(double)(cellNums[0]/8);
            double R2 = 1.0 - point.norm() + sizeM2;

            for( double step = 1.0; step >= R2 - EPS; step-= sizeM2) {

                this->addPoint(unit*(step*R));

            }
        }
    }
}

void Mesh::leftRightBotPartsPoints() {

    arrUnsgn cellNums(CELL(1));
    unsigned layerP = cellNums[0]/8*(cellNums[0]/4 + 1);
    unsigned baseP = layerP*(cellNums[0]/4 + 1);

    //right part
    double angle = PI/2.0;
    TypeVector<double> axis = TypeVector<double>(0.0, 1.0, 0.0);

    for(unsigned i = layerP; i < baseP; i++) {

        this->addPoint(this->points[i].rotate(angle, axis));

    }

    //bottom part
    angle = PI;

    for(unsigned i = layerP; i < baseP; i++) {

        this->addPoint(this->points[i].rotate(angle, axis));

    }

    //left part
    angle = 3.0*PI/2.0;

    for(unsigned i = layerP; i < baseP - layerP; i++) {

        this->addPoint(this->points[i].rotate(angle, axis));

    }
}


void Mesh::frontRearPartsPoints() {

    arrUnsgn cellNums(CELL(1));
    unsigned sideP = cellNums[0]/8;
    unsigned edgeP = cellNums[0]/4 + 1;
    unsigned layerP = sideP*edgeP;
    unsigned baseP = layerP*edgeP;

    //front part
    double angle = 3.0*PI/2.0;
    TypeVector<double> axis = TypeVector<double>(0.0, 0.0, 1.0);

    for(unsigned j = 0; j < edgeP - 2; j++){

        double startp = baseP + j*layerP + sideP;
        double endp = startp + (edgeP - 2)*sideP;

        for(unsigned i = startp; i < endp; i++) {

            this->addPoint(this->points[i].rotate(angle, axis));
        }
    }

    //rear part
    angle = PI/2.0;
    axis = TypeVector<double>(-1.0, 0.0, 0.0);

    for(unsigned j = 0; j < edgeP - 2; j++) {

        double startp = (j + 1)*layerP + sideP;
        double endp = startp + (edgeP - 2)*sideP;

        for(unsigned i = startp; i < endp; i++) {

            this->addPoint(this->points[i].rotate(angle, axis));
        }
    }
}


void Mesh::cubicPartPoints() {

    arrDouble dim(DIM(1));
    arrUnsgn cellNums(CELL(1));
    double R = dim[0];
    double corner = R*tan(PI/6.0)/2.0;
    double sizeC = 2.0*corner/(double)(cellNums[0]/4);

    for(double z = corner; z >= -corner - EPS; z-= sizeC) {

        for(double x = -corner; x <= corner + EPS; x+= sizeC) {

            for(double y = -corner; y <= corner + EPS; y+= sizeC) {

                this->addPoint(x, y, z);
            }
        }
    }
}

