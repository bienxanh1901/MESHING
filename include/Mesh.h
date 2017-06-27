#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include <cstdlib>

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
        unsigned numberOfPoints;
        unsigned numberOfCells;
        unsigned numberOfFaces;
        unsigned numberOfInternalFaces;
        unsigned numberOfBoundaries;
        containerPoints points;
        containerCells cells;
        containerFaces faces;
        containerIDs boundaries;
        containerIDs neighbor;
        containerIDs owner;

        // internal function

//        void sphericGeneration();


        void generateCubicMesh();
//        void generateSphereMesh();

        // cubic mesh definition
        void cubicGeneration();
        void cubicPoints();
        void trapezePoints();
        void cubicInternalFaces();
        void cubicInternalCells();
        void cubicBoundariesLeftRight();
        void cubicBoundariesTopBot();
        void cubicBoundariesFrontRear();
//        void cubicFindNeighbor();

        // cylinder mesh definition
//        void cylinderGeneration();
        void cylinderPoints();
//        void cylinderElem();
//        void baseNode();
//        void baseElem();
//        void extrudeNode();
//        void extrudeElem();
//        void outerCircleNode();
//        void innerRectangularNode();
//        void cylinderBoundariesBot();
//        void cylinderBoundariesTop();
//        void cylinderBoundariesAround();


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
