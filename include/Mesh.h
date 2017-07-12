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
        Mesh(MeshInfomation&);
        virtual ~Mesh();
        Mesh(const Mesh& other);
        Mesh& operator=(const Mesh& other);
        void meshGeneration();
        void writeVTUformat();
        void writeTEACHMesh();
    protected:
    private:
        typedef vector<Cell> containerCells;
        typedef vector<Face> containerFaces;
        MeshInfomation meshInfo;

        containerPoints points;
        containerCells cells;
        containerFaces faces;
        containerIDs boundaries;
        containerIDs neighbor;
        containerIDs owner;

        // internal function

        void addPoint(double , double , double);
        void addPoint(TypeVector<double>);
        void addFace(containerPoints&);
        void addFace(unsigned, unsigned, unsigned, unsigned);
        void addCell(containerPoints&);
        void addCell(unsigned, unsigned, unsigned, unsigned,
                            unsigned, unsigned, unsigned, unsigned);
        void addOwner(unsigned);
        void addNeighbor(unsigned);

        // cubic mesh definition
        void cubicGenerator();

        void cubicPoints();

        void cubicInternalFacesandCells();

        void cubicBoundaries();
        void cubicBoundariesLeftRight();
        void cubicBoundariesTopBot();
        void cubicBoundariesFrontRear();

        // cylinder mesh definition
        void cylinderGenerator();

        void cylinderPoints();
        void basePoints();
        void extrudePoints();

        void cylinderInternalFacesandCells();
        void baseFacesandCells();
        void extrudeFaces();
        void extrudeCells();

        void cylinderBoundaries();
        void cylinderBoundaryBot();
        void cylinderBoundaryTop();
        void cylinderBoundariesAround();
        void findPointsconnected2D(unsigned&, unsigned&, unsigned&);

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

};

#endif // MESH_H
