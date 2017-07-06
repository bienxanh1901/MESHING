#include "../include/Face.h"


void Face::triangleProperties() {
    this->triangleArea();
    this->triangleCentroid();
    this->triangleNormal();
}

void Face::triangleArea() {
    TypeVector<double> AB, AC, crossproduct;
    AB = this->points[1] - this->points[0];
    AC = this->points[2] - this->points[0];
    crossproduct = AB.cross(AC);
    this->area = 0.5*crossproduct.norm();
}

void Face::triangleCentroid() {
    TypeVector<double> centerAB, centerAC;
    TypeVector<double> median1, median2;
    TypeVector<double> V, V1, V2;
    double a;
    centerAB = (this->points[0] + this->points[1])*0.5;
    centerAC = (this->points[0] + this->points[2])*0.5;

    median1 = centerAB - this->points[1];
    median2 = centerAC - this->points[2];

    V  = this->points[2] - this->points[1];
    V1 = median1.cross(median2);
    V2 = V.cross(median2);
    a  = V2.norm()/V1.norm();
    this->centroid = this->points[1] + median1*a;
}

void Face::triangleNormal()
{
    TypeVector<double> AB, AC;
    AB = this->points[1] - this->points[0];
    AC = this->points[2] - this->points[0];
    this->normalVector = AC.cross(AB)/(2.0*area);
}
