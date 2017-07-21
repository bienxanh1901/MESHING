#include "../../include/Face.h"
void Face::quadrilateralProperties() {
    this->quadrilateralArea();
    this->quadrilateralCentroid();
    this->quadrilateralNormal();
}

void Face::quadrilateralArea() {
    TypeVector<double> AC, BD, crossproduct;
    AC = this->points[0] - this->points[2];
    BD = this->points[1] - this->points[3];
    crossproduct = AC.cross(BD);
    this->area = 0.5*crossproduct.norm();
}

void Face::quadrilateralCentroid() {
    TypeVector<double> centerAB, centerBC, centerCD, centerDA;
    TypeVector<double> bimedian1, bimedian2;
    TypeVector<double> V, V1, V2;
    double a;
    centerAB = (this->points[0] + this->points[1])*0.5;
    centerBC = (this->points[1] + this->points[2])*0.5;
    centerCD = (this->points[2] + this->points[3])*0.5;
    centerDA = (this->points[3] + this->points[0])*0.5;

    bimedian1 = centerCD - centerAB;
    bimedian2 = centerDA - centerBC;

    V  = centerBC - centerAB;
    V1 = bimedian1.cross(bimedian2);
    V2 = V.cross(bimedian2);
    a  = V2.norm()/V1.norm();
    this->centroid = centerAB + bimedian1*a;
}

void Face::quadrilateralNormal() {
    TypeVector<double> AC, BD;
    AC = this->points[0] - this->points[2];
    BD = this->points[1] - this->points[3];
    this->normalVector = AC.cross(BD)/(2.0*area);
}
