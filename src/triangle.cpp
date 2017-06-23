#include "../include/Element.h"


void Element::triangleProperties()
{
    triangleArea();
    triangleCentroid();
    triangleNormal();
}

void Element::triangleArea()
{
    typeVector<double> AB, AC, crossproduct;
    AB = this->nodes[1] - this->nodes[0];
    AC = this->nodes[2] - this->nodes[0];
    crossproduct = AB.cross(AC);
    this->area = 0.5*crossproduct.norm();
}

void Element::triangleCentroid()
{
    typeVector<double> centerAB, centerAC;
    typeVector<double> median1, median2;
    typeVector<double> V, V1, V2;
    double a;
    centerAB = (this->nodes[0] + this->nodes[1])*0.5;
    centerAC = (this->nodes[0] + this->nodes[2])*0.5;

    median1 = centerAB - this->nodes[1];
    median2 = centerAC - this->nodes[2];

    V  = this->nodes[2] - this->nodes[1];
    V1 = median1.cross(median2);
    V2 = V.cross(median2);
    a  = V2.norm()/V1.norm();
    this->centroid = this->nodes[1] + median1*a;
}

void Element::triangleNormal()
{
    typeVector<double> AB, AC;
    AB = this->nodes[1] - this->nodes[0];
    AC = this->nodes[2] - this->nodes[0];
    this->norm = AC.cross(AB)/(2.0*area);
}
