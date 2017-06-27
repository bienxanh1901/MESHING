#include "../include/Cell.h"

void Cell::hexahedralProperties() {

    containerPoints pointlist;
    containerFaces faces;
    pointlist = findFace(0, 3, 7, 4);
    faces.push_back(Face(pointlist, QUAD4));
    pointlist = findFace(1, 2, 6, 5);
    faces.push_back(Face(pointlist, QUAD4));
    pointlist = findFace(0, 1, 5, 4);
    faces.push_back(Face(pointlist, QUAD4));
    pointlist = findFace(3, 2, 6, 7);
    faces.push_back(Face(pointlist, QUAD4));
    pointlist = findFace(0, 1, 2, 3);
    faces.push_back(Face(pointlist, QUAD4));
    pointlist = findFace(4, 5, 6, 7);
    faces.push_back(Face(pointlist, QUAD4));
    this->calcVolumeCentroid(faces);
}
