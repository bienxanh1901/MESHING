#include "../../include/Cell.h"

void Cell::hexahedralProperties() {

    ContainerPrtPoints pointsList;
    ContainerFaces faces;
    pointsList = findFace(0, 3, 7, 4);
    faces.push_back(Face(pointsList, QUAD4));
    pointsList = findFace(1, 2, 6, 5);
    faces.push_back(Face(pointsList, QUAD4));
    pointsList = findFace(0, 1, 5, 4);
    faces.push_back(Face(pointsList, QUAD4));
    pointsList = findFace(3, 2, 6, 7);
    faces.push_back(Face(pointsList, QUAD4));
    pointsList = findFace(0, 1, 2, 3);
    faces.push_back(Face(pointsList, QUAD4));
    pointsList = findFace(4, 5, 6, 7);
    faces.push_back(Face(pointsList, QUAD4));
    this->calcVolumeCentroid(faces);
}
