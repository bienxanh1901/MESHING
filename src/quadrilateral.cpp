#include "../include/Element.h"
void Element::quadrilateralProperties()
{
    quadrilateralArea();
    quadrilateralCentroid();
    quadrilateralNormal();
}

void Element::quadrilateralArea()
{
    typeVector<double> AC, BD, crossproduct;
    AC = this->nodes[0] - this->nodes[2];
    BD = this->nodes[1] - this->nodes[3];
    crossproduct = AC.cross(BD);
    this->area = 0.5*crossproduct.norm();
}

void Element::quadrilateralCentroid()
{
    typeVector<double> centerAB, centerBC, centerCD, centerDA;
    typeVector<double> bimedian1, bimedian2;
    typeVector<double> V, V1, V2;
    double a;
    centerAB = (this->nodes[0] + this->nodes[1])*0.5;
    centerBC = (this->nodes[1] + this->nodes[2])*0.5;
    centerCD = (this->nodes[2] + this->nodes[3])*0.5;
    centerDA = (this->nodes[3] + this->nodes[0])*0.5;

    bimedian1 = centerCD - centerAB;
    bimedian2 = centerDA - centerBC;

    V  = centerBC - centerAB;
    V1 = bimedian1.cross(bimedian2);
    V2 = V.cross(bimedian2);
    a  = V2.norm()/V1.norm();
    this->centroid = centerAB + bimedian1*a;
}

void Element::quadrilateralNormal()
{
    typeVector<double> AC, BD;
    AC = this->nodes[0] - this->nodes[2];
    BD = this->nodes[1] - this->nodes[3];
    this->norm = AC.cross(BD)/(2.0*area);
}
