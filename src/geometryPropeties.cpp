#include "../include/Element.h"

void Element::geometryProperties()
{
    this->center = Point();
    this->centroid = Point();
    this->norm = typeVector<double>();
    this->volume = 0;
    this->area = 0;
    calcCenter();
    if(elementType <= QUAD9) faceProperties();
    else cellProperties();
}

void Element::faceProperties()
{
    if(elementType == QUAD4) quadrilateralProperties();
    else if (elementType == TRI3) triangleProperties();
}

void Element::cellProperties()
{
    if(elementType == HEX8) hexahedralProperties();
    else if (elementType == TET4) tetrahedralProperties();
}

void Element::calcCenter()
{
    for(containerNodes::iterator i = this->nodes.begin(); i!= this->nodes.end(); i++)
    {
        this->center+=*i;
    }
    this->center/=(double)this->numberOfNodes;
}

void Element::calcVolumeCentroid()
{
    typeVector<double> vec1;
    double sign;
    for(containerElements::iterator i=this->faces.begin(); i!=this->faces.end(); i++)
    {
        vec1 = this->center - i->centroid;
        sign = vec1*i->norm;
        double intergal;
        if(sign>0)i->norm*=-1;
        intergal = (i->centroid*i->norm)*i->area;
        this->volume += intergal;
        this->centroid += i->centroid*intergal;
    }
    this->volume/=3.0;
    this->centroid/=(4.0*volume);
}

vector<Node> Element::findFace(unsigned vertice1, unsigned vertice2, unsigned vertice3, unsigned vertice4)
{
    containerNodes result;
    result.push_back(this->nodes[vertice1]);
    result.push_back(this->nodes[vertice2]);
    result.push_back(this->nodes[vertice3]);
    if(elementType == HEX8) result.push_back(nodes[vertice4]);
    return result;
}

