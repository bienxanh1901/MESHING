#include "../include/Mesh.h"

void Mesh::cubicGeneration() {

    this->cubicPoints();
    this->cubicInternalFaces();
    this->cubicInternalCells();
    this->numberOfBoundaries = 6;
    this->cubicBoundariesLeftRight();
    this->cubicBoundariesFrontRear();
    this->cubicBoundariesTopBot();
}

void Mesh::cubicPoints(){

    double ratioX, ratioY;
    double dimX, dimY;
    double sizeX, sizeY;
    double startX, startY;
    unsigned cnt = 0;

    dimX = DIM(1);
    dimY = DIM(2);
    sizeX = SIZE(0);
    sizeY = SIZE(1);
    startX = 0.0;
    startY = 0.0;

    if(this->meshInfo.meshShape.getShape()==TRAPEZE){
        ratioX = SIZE(2)*(DIM(1) - DIM(4))/DIM(3);
        ratioY = SIZE(2)*(DIM(2) - DIM(5))/DIM(3);
    }

    double stepX, stepY, stepZ;
    unsigned i, j, k;
    for(k = 0, stepZ = 0; k <= NODE(2); k++, stepZ+= SIZE(2)) {

        for(j = 0, stepY = 0; j <= NODE(1); j++, stepY+= sizeY) {

            for(i = 0, stepX = 0; i <= NODE(0); i++, stepX+= sizeX) {

                this->points.push_back(Point(stepX + startX, stepY + startY, stepZ, ++this->numberOfPoints));

            }
        }

        if(this->meshInfo.meshShape.getShape() == TRAPEZE){
            dimX-= ratioX;
            dimY-= ratioY;
            sizeX = dimX/(double)NODE(0);
            sizeY = dimY/(double)NODE(1);
            startX = (DIM(1) - dimX)/2.0;
            startY = (DIM(2) - dimY)/2.0;
        }
    }
}

void Mesh::cubicInternalFaces() {

    unsigned layerPoints = (NODE(1) + 1)*(NODE(0) + 1);
    unsigned lengthPoints = NODE(0) + 1;
    unsigned k1, k2, j1, j2, i1;
    containerPoints pointlist;

    for(unsigned k = 1; k <= NODE(2); k++) {
        k1 = (k - 1)*layerPoints;
        k2 = k*layerPoints;

        for(unsigned j = 1; j <= NODE(1); j++) {
            j1 = (j - 1)*lengthPoints;
            j2 = j*lengthPoints;

            for(unsigned i = 1; i <= NODE(0); i++) {
                i1 = i - 1;
                if(i < NODE(0)) {
                    pointlist.push_back(this->points[k1 + j1 + i]);
                    pointlist.push_back(this->points[k1 + j2 + i]);
                    pointlist.push_back(this->points[k2 + j2 + i]);
                    pointlist.push_back(this->points[k2 + j1 + i]);
                    this->faces.push_back(Face(pointlist, QUAD4, ++numberOfFaces));
                    pointlist.clear();
                }

                if(j < NODE(1)) {
                    pointlist.push_back(this->points[k1 + j2 + i1]);
                    pointlist.push_back(this->points[k2 + j2 + i1]);
                    pointlist.push_back(this->points[k2 + j2 + i]);
                    pointlist.push_back(this->points[k1 + j2 + i]);
                    this->faces.push_back(Face(pointlist, QUAD4, ++numberOfFaces));
                    pointlist.clear();
                }

                if(k < NODE(2)) {
                    pointlist.push_back(this->points[k1 + j1 + i1]);
                    pointlist.push_back(this->points[k1 + j1 + i]);
                    pointlist.push_back(this->points[k1 + j2 + i]);
                    pointlist.push_back(this->points[k1 + j2 + i1]);
                    this->faces.push_back(Face(pointlist, QUAD4, ++numberOfFaces));
                    pointlist.clear();
                }
            }
        }
    }

    this->numberOfInternalFaces = this->numberOfFaces;
}

void Mesh::cubicInternalCells(){

    unsigned layerPoints = (NODE(1) + 1)*(NODE(0) + 1);
    unsigned lengthPoints = NODE(0) + 1;
    unsigned layerCells = NODE(0)*NODE(1);
    unsigned lengthCells = NODE(0);
    unsigned k1, k2, j1, j2, i1;
    containerPoints pointlist;

    for(unsigned k = 1; k <= NODE(2); k++){
        k1 = (k - 1)*layerPoints;
        k2 = k*layerPoints;

        for(unsigned j = 1; j <= NODE(1); j++){
            j1 = (j - 1)*lengthPoints;
            j2 = j*lengthPoints;

            for(unsigned i = 1; i <= NODE(0); i++){
                i1 = i - 1;
                pointlist.push_back(this->points[k1 + j1 + i1]);
                pointlist.push_back(this->points[k1 + j1 + i]);
                pointlist.push_back(this->points[k1 + j2 + i]);
                pointlist.push_back(this->points[k1 + j2 + i1]);
                pointlist.push_back(this->points[k2 + j1 + i1]);
                pointlist.push_back(this->points[k2 + j1 + i]);
                pointlist.push_back(this->points[k2 + j2 + i]);
                pointlist.push_back(this->points[k2 + j2 + i1]);

                this->cells.push_back(Cell(pointlist, HEX8, ++this->numberOfCells));
                pointlist.clear();

                if(i < NODE(0)) {
                    this->owner.push_back(this->numberOfCells);
                    this->neighbor.push_back(this->numberOfCells + 1);
                }

                if(j < NODE(1)) {
                    this->owner.push_back(this->numberOfCells );
                    this->neighbor.push_back(this->numberOfCells + lengthCells);
                }

                if(k < NODE(2)) {
                    this->owner.push_back(this->numberOfCells);
                    this->neighbor.push_back(this->numberOfCells + layerCells);
                }
            }
        }
    }
}


void Mesh::cubicBoundariesLeftRight(){

    unsigned lengthPoints = NODE(0) + 1;
    unsigned widthPoints = NODE(1) + 1;
    unsigned layerPoints = lengthPoints*widthPoints;
    unsigned layerCells = NODE(0)*NODE(1);
    unsigned j1, j2, j3, k1, k2, k3, i1;
    containerPoints pointlist;

    i1 = lengthPoints - 1;
    for(unsigned k = 1; k <= NODE(2); k++){
        k1 = (k - 1)*layerPoints;
        k2 = k*layerPoints;
        k3 = (k - 1)*layerCells;

        for(unsigned j = 1; j <= NODE(1); j++){
            j1 = (j - 1)*lengthPoints;
            j2 = j*lengthPoints;
            j3 = (j - 1)*NODE(1);

            pointlist.push_back(this->points[k1 + j1]);
            pointlist.push_back(this->points[k2 + j1]);
            pointlist.push_back(this->points[k2 + j2]);
            pointlist.push_back(this->points[k1 + j2]);
            this->faces.push_back(Face(pointlist, QUAD4, ++numberOfFaces));
            pointlist.clear();
            this->owner.push_back(k3 + j3 + 1);
        }
    }
    this->boundaries.push_back(NODE(2)*NODE(1));

    for(unsigned k = 1; k <= NODE(2); k++){
        k1 = (k - 1)*layerPoints;
        k2 = k*layerPoints;
        k3 = (k - 1)*layerCells;

        for(unsigned j = 1; j <= NODE(1); j++){
            j1 = (j - 1)*lengthPoints;
            j2 = j*lengthPoints;
            j3 = (j - 1)*NODE(1);

            pointlist.push_back(this->points[k1 + j1 + i1]);
            pointlist.push_back(this->points[k1 + j2 + i1]);
            pointlist.push_back(this->points[k2 + j2 + i1]);
            pointlist.push_back(this->points[k2 + j1 + i1]);
            this->faces.push_back(Face(pointlist, QUAD4, ++numberOfFaces));
            pointlist.clear();
            this->owner.push_back(k3 + j3 + i1);
        }
    }
    this->boundaries.push_back(NODE(2)*NODE(1));
}

void Mesh::cubicBoundariesFrontRear(){

    unsigned lengthPoints = NODE(0) + 1;
    unsigned widthPoints = NODE(1) + 1;
    unsigned layerPoints = lengthPoints*widthPoints;
    unsigned layerCells = NODE(0)*NODE(1);
    unsigned i1, k1, k2, k3, j1, j2;
    containerPoints pointlist;

    j1 = NODE(1)*lengthPoints;
    j2 = (NODE(1) - 1)*NODE(0);
    for(unsigned k = 1; k <= NODE(2); k++){

        k1 = (k - 1)*layerPoints;
        k2 = k*layerPoints;
        k3 = (k - 1)*layerCells;

        for(unsigned i = 1; i <= NODE(0); i++){
            i1 = i - 1;
            pointlist.push_back(this->points[k1 + i1]);
            pointlist.push_back(this->points[k1 + i]);
            pointlist.push_back(this->points[k2 + i]);
            pointlist.push_back(this->points[k2 + i1]);
            this->faces.push_back(Face(pointlist, QUAD4, ++numberOfFaces));
            pointlist.clear();
            this->owner.push_back(k3 + i);
        }
    }
    this->boundaries.push_back(NODE(2)*NODE(0));

    for(unsigned k = 1; k <= NODE(2); k++){

        k1 = (k - 1)*layerPoints;
        k2 = k*layerPoints;
        k3 = (k - 1)*layerCells;
        for(unsigned i = 1; i <= NODE(0); i++){
            i1 = i - 1;

            pointlist.push_back(this->points[k1 + j1 + i1]);
            pointlist.push_back(this->points[k2 + j1 + i1]);
            pointlist.push_back(this->points[k2 + j1 + i]);
            pointlist.push_back(this->points[k1 + j1 + i]);
            this->faces.push_back(Face(pointlist, QUAD4, ++numberOfFaces));
            pointlist.clear();
            this->owner.push_back(k3 + j2 + i);
        }
    }
    this->boundaries.push_back(NODE(2)*NODE(0));
}

void Mesh::cubicBoundariesTopBot(){
    unsigned lengthPoints = NODE(0) + 1;
    unsigned widthPoints = NODE(1) + 1;
    unsigned layerPoints = lengthPoints*widthPoints;
    unsigned layerCells = NODE(0)*NODE(1);
    unsigned i1, j1, j2, j3, k1, k2;
    containerPoints pointlist;

    k1 = layerPoints*NODE(2);
    k2 = layerCells*(NODE(2) - 1);

    for(unsigned j = 1; j <= NODE(1); j++){
        j1 = (j - 1)*lengthPoints;
        j2 = j*lengthPoints;
        j3 = (j - 1)*NODE(1);

        for(unsigned i = 1; i <= NODE(0); i++){
            i1 = i - 1;
            pointlist.push_back(this->points[j1 + i1]);
            pointlist.push_back(this->points[j2 + i1]);
            pointlist.push_back(this->points[j2 + i]);
            pointlist.push_back(this->points[j1 + i]);
            this->faces.push_back(Face(pointlist, QUAD4, ++numberOfFaces));
            pointlist.clear();
            this->owner.push_back(j3 + i);
        }
    }
    this->boundaries.push_back(NODE(1)*NODE(0));

    for(unsigned j = 1; j <= NODE(1); j++){
        j1 = (j - 1)*lengthPoints;
        j2 = j*lengthPoints;
        j3 = (j - 1)*NODE(1);

        for(unsigned i = 1; i <= NODE(0); i++){
            i1 = i - 1;
            pointlist.push_back(this->points[k1 + j1 + i1]);
            pointlist.push_back(this->points[k1 + j1 + i]);
            pointlist.push_back(this->points[k1 + j2 + i]);
            pointlist.push_back(this->points[k1 + j2 + i1]);
            this->faces.push_back(Face(pointlist, QUAD4, ++numberOfFaces));
            pointlist.clear();
            this->owner.push_back(k2 + j3 + i);
        }
    }
    this->boundaries.push_back(NODE(1)*NODE(0));

}
