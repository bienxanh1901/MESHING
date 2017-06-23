#include "../include/Element.h"

void Element::tetrahedralProperties()
{
    setFaceOfTetrahedral();
    calcVolumeCentroid();
}

void Element::setFaceOfTetrahedral()
{
    containerNodes node;
    node = findFace(0, 1, 2);
    this->faces.push_back(Element(node, TRI3, ++numberOfFaces));
    node = findFace(1, 2, 3);
    this->faces.push_back(Element(node, TRI3, ++numberOfFaces));
    node = findFace(0, 1, 3);
    this->faces.push_back(Element(node, TRI3, ++numberOfFaces));
    node = findFace(0, 2, 3);
    this->faces.push_back(Element(node, TRI3, ++numberOfFaces));
}
