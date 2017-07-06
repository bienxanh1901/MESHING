#include "../include/Cell.h"

void Cell::tetrahedralProperties() {
    containerPoints pointsList;
    containerFaces faces;
    pointsList = findFace(0, 1, 2);
    faces.push_back(Face(pointsList, TRI3));
    pointsList = findFace(1, 2, 3);
    faces.push_back(Face(pointsList, TRI3));
    pointsList = findFace(0, 1, 3);
    faces.push_back(Face(pointsList, TRI3));
    pointsList = findFace(0, 2, 3);
    faces.push_back(Face(pointsList, TRI3));
    this->calcVolumeCentroid(faces);
}
