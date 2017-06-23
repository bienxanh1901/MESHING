#include "../include/Element.h"

void Element::hexahedralProperties()
{
    setFaceOfHexahedral();
    calcVolumeCentroid();
}

void Element::setFaceOfHexahedral()
{
    containerNodes node;
    numberOfFaces = 0;
    node = findFace(0, 3, 7, 4);
    this->faces.push_back(Element(node, QUAD4, ++numberOfFaces));
    node = findFace(1, 2, 6, 5);
    this->faces.push_back(Element(node, QUAD4, ++numberOfFaces));
    node = findFace(0, 1, 5, 4);
    this->faces.push_back(Element(node, QUAD4, ++numberOfFaces));
    node = findFace(3, 2, 6, 7);
    this->faces.push_back(Element(node, QUAD4, ++numberOfFaces));
    node = findFace(0, 1, 2, 3);
    this->faces.push_back(Element(node, QUAD4, ++numberOfFaces));
    node = findFace(4, 5, 6, 7);
    this->faces.push_back(Element(node, QUAD4, ++numberOfFaces));
}
