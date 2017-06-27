#include "../include/Cell.h"

void Cell::tetrahedralProperties() {
    containerPoints pointlist;
    containerFaces faces;
    pointlist = findFace(0, 1, 2);
    faces.push_back(Face(pointlist, TRI3));
    pointlist = findFace(1, 2, 3);
    faces.push_back(Face(pointlist, TRI3));
    pointlist = findFace(0, 1, 3);
    faces.push_back(Face(pointlist, TRI3));
    pointlist = findFace(0, 2, 3);
    faces.push_back(Face(pointlist, TRI3));
    this->calcVolumeCentroid(faces);
}
