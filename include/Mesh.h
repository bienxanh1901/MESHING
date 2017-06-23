#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include <cstdlib>

#include "Node.h"
#include "Element.h"
#include "Shape.h"
#include "Element.h"
#include "MeshInfomation.h"
#include "../define/define.h"
#include "../define/paraviewDefine.h"
#include "../define/meshDefine.h"
#include "paraviewExp.h"
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
        typedef vector<Node> containerNodes;
        typedef vector<Element> containerElements;
        typedef vector<unsigned> containerIDs;
        MeshInfomation meshInfo;
        unsigned numberOfNodes;
        unsigned numberOfElems;
        unsigned numberOfFaces;
        unsigned numberOfBoundaries;
        containerNodes nodes;
        containerElements elements;
        containerElements faces;
        vector<containerElements> boundaries;
        vector<containerIDs> neighbor;

        // internal function
        void setNumberOfBoundaries();

        void sphericGeneration();


        void generateCubicMesh();
        void generateSphereMesh();

        // cubic mesh definition
        void cubicGeneration();
        void cubicNode();
        void trapezeNode();
        void cubicFace();
        void cubicInternalElement();
        void cubicBoundariesLeftRight();
        void cubicBoundariesTopBot();
        void cubicBoundariesFrontRear();
        void cubicFindNeighbor();

        // cylinder mesh definition
        void cylinderGeneration();
        void cylinderNode();
        void cylinderElem();
        void baseNode();
        void baseElem();
        void extrudeNode();
        void extrudeElem();
        void outerCircleNode();
        void innerRectangularNode();
        void cylinderBoundariesBot();
        void cylinderBoundariesTop();
        void cylinderBoundariesAround();


        //export Mesh
        void writeTEACHPoint();
        void writeTEACHFaceOfCell();
        void writeTEACHCell();
        void writeTEACHBoundary();
        void writeTEACHNeighbor();

};

#endif // MESH_H
