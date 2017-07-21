#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <algorithm>

#include "Cell.h"
#include "Face.h"
#include "Shape.h"
#include "paraviewExp.h"
#include "MeshInfomation.h"
#include "../define/define.h"
#include "../define/paraviewDefine.h"
#include "../define/meshDefine.h"
#include "../common/utilities.h"


using namespace std;
using namespace utilities;

class Mesh
{
    public:
        Mesh();
        Mesh(Shape&);
        virtual ~Mesh();
        Mesh(const Mesh& other);
        Mesh& operator=(const Mesh& other);
        void reMesh();
        void clear();
        void meshGeneration();
        void writeVTUformat();
        void writeVTUtest();
        void writeTEACHMesh();
    protected:
    private:
        typedef vector<Cell> ContainerCells;
        typedef vector<Face> ContainerFaces;
        Shape shape;
        MeshInfomation meshInfo;

        ContainerPoints points;
        ContainerCells cells;
        ContainerFaces faces;
        ContainerIDs boundaries;
        ContainerIDs neighbor;
        ContainerIDs owner;
        ContainerIDs cellsOfLayer;
        // test layer
        ContainerIDs mark;

        // internal function

        void addPoint(double , double , double);
        void addPoint(TypeVector<double>);
        void addFace(ContainerPoints&);
        void addFace(unsigned, unsigned, unsigned, unsigned);
        void addCell(ContainerPoints&);
        void addCell(unsigned, unsigned, unsigned, unsigned,
                     unsigned, unsigned, unsigned, unsigned);
        void addOwner(unsigned);
        void addNeighbor(unsigned);

        // cubic mesh definition
        void cubicGenerator();

        void cubicPoints();

        void cubicInternalFacesandCells();

        void cubicBoundaries();
        void cubicBoundaryLeft();
        void cubicBoundaryRight();
        void cubicBoundaryTop();
        void cubicBoundaryBot();
        void cubicBoundaryFront();
        void cubicBoundaryRear();

        // cylinder mesh definition
        void cylinderGenerator();

        void cylinderPoints();
        void basePoints();
        void extrudePoints();

        void cylinderInternalFacesandCells();
        void cylinderOuterPart(unsigned, unsigned, unsigned, unsigned);
        void cylinderInnerPart(unsigned, unsigned, unsigned);

        void cylinderBoundaries();
        void cylinderBoundaryBot();
        void cylinderBoundaryTop();
        void cylinderBoundariesAround();
        void meshConnected2D(unsigned&, unsigned&, unsigned&, unsigned&, unsigned&);

        // spheric mesh definition

        void sphericGenerator();
        void sphericPoints();
        void cubicPartPoints();
        void topPartPoints();
        void leftRightBotPartsPoints();
        void frontRearPartsPoints();

        void sphericFacesandCells();
        void leftRightBotTopPartsCells();
        void frontPartCells();
        void rearPartCells();
        void cubicPartCells();

        void sphericBoundaries();
        void sphericTopBoundary();
        void sphericBotBoundary();
        void sphericFrontBoundary();
        void sphericRearBoundary();


        void sphericFrontConnectivity();
        void sphericRearConnectivity();
        void findPointsconnected3D(unsigned&, unsigned&, unsigned&, unsigned&, unsigned&);
        TypeVector<double> cubic2Spheric(double, double, double);


//        export Mesh

        void writeMeshInfomation();
        void writeTEACHPoints();
        void writeTEACHCells();
        void writeTEACHFaces();
        void writeTEACHNeighbor();
        void writeTEACHOwner();
        void writeTEACHBoundaries();
        void writeTEACHCellsOfLayer();

};

#endif // MESH_H
