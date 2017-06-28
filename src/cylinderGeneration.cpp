#include "../include/Mesh.h"

void Mesh::cylinderGeneration() {

    this->cylinderPoints();
    this->cylinderInternalFaces();
    this->cylinderCells();
//    cylinderBoundariesBot();
//    cylinderBoundariesTop();
//    cylinderBoundariesAround();

}

void Mesh::cylinderPoints() {

    this->basePoints();
    this->extrudePoints();

}

void Mesh::basePoints(){

    double angleSize = 2.0*PI/NODE(0);
    double radiusX = DIM(1);
    double radiusY = DIM(3);
    double halfRadius = 0.5*radiusX;
    double p2 = halfRadius/sqrt(2.0);
    double cornerX = halfRadius - p2*(1.0 - tan(PI/6.0))/sqrt(2.0);
    halfRadius = 0.5*radiusY;
    p2 = halfRadius/sqrt(2.0);
    double cornerY = halfRadius - p2*(1.0 - tan(PI/6.0))/sqrt(2.0);

    unsigned sidePoints = NODE(0)/8;
    double costheta, sintheta;
    double coordX, coordY;
    double sizeX, sizeY;

    //points of outer circular
    for(double theta = -PI/4; theta < 7*PI/4; theta+= angleSize){
        costheta = cos(theta);
        sintheta = sin(theta);

        if(fabs(costheta) >= 1.0/sqrt(2.0)){
            sizeX = (radiusX - cornerX/fabs(costheta))/sidePoints;
            sizeY = (radiusY - cornerY/fabs(costheta))/sidePoints;
        }else {
            sizeX = (radiusX - cornerX/fabs(sintheta))/sidePoints;
            sizeY = (radiusY - cornerY/fabs(sintheta))/sidePoints;
        }

        for(unsigned i = 0; i < sidePoints; i++){
            coordX = (radiusX - (double)i*sizeX)*sintheta;
            coordY = (radiusY - (double)i*sizeY)*costheta;
            this->points.push_back(Point(coordX, coordY, 0.0, ++this->numberOfPoints));
        }
    }

    // points of inner rectangular
    sizeX = 2.0*cornerX/(double)(NODE(0)/4);
    sizeY = 2.0*cornerY/(double)(NODE(0)/4);
    for(double coordY = cornerY; coordY >= -cornerY - EPS; coordY-= sizeY){

        for(double coordX = -cornerX; coordX <= cornerX + EPS; coordX+= sizeX){

            this->points.push_back(Point(coordX, coordY, 0.0, ++this->numberOfPoints));
        }
    }
}

void Mesh::extrudePoints(){

    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned base = NODE(0)*sidePoints + pow(edgePoints,2);
    Point point;

    for(double coordZ = SIZE(1); coordZ <= DIM(2) + EPS; coordZ+= SIZE(1)){

        for(unsigned i = 0; i < base; i++){

            point = this->points[i] + Point(0.0, 0.0, coordZ);
            this->points.push_back(Point(point, ++this->numberOfPoints));
        }
    }
}

void Mesh::cylinderInternalFaces() {

    this->baseFaces();
    this->extrudeFaces();

}

void Mesh::baseFaces(){
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned outerPoints = NODE(0)*sidePoints;
    unsigned base = outerPoints + pow(edgePoints,2);
    unsigned j1, j2, i1, i2, tmp, tmp2;
    containerPoints pointsList;

    // faces of outer circular
    for(unsigned j = 0; j < NODE(0); j++) {

        j1 = j*sidePoints;
        j2 = (j+1)*sidePoints;
        if(j == NODE(0) -1) j2 = 0;

        for(unsigned i = 1; i < sidePoints; i++) {

            pointsList.push_back(this->points[j1 + i]);
            pointsList.push_back(this->points[j2 + i]);
            pointsList.push_back(this->points[base + j2 + i]);
            pointsList.push_back(this->points[base + j1 + i]);
            this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
            pointsList.clear();

            if(j == 0) {
                pointsList.push_back(this->points[i - 1]);
                pointsList.push_back(this->points[i]);
                pointsList.push_back(this->points[base + i - 1]);
                pointsList.push_back(this->points[base + i]);
                this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
                pointsList.clear();
            }


            if(j < NODE(0) -1) {
                pointsList.push_back(this->points[j2 + i - 1]);
                pointsList.push_back(this->points[base + j2 + i - 1]);
                pointsList.push_back(this->points[base + j2 + i - 1]);
                pointsList.push_back(this->points[j2 + i]);
                this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
                pointsList.clear();
            }

            pointsList.push_back(this->points[base + j1 + i - 1]);
            pointsList.push_back(this->points[base + j1 + i]);
            pointsList.push_back(this->points[base + j2 + i]);
            pointsList.push_back(this->points[base + j2 + i - 1]);
            this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
            pointsList.clear();
        }

        j1 = (j + 1)*sidePoints - 1;
        j2 = (j + 2)*sidePoints - 1;
        if(j == NODE(0) - 1) j2 = sidePoints - 1;
        tmp = j/(edgePoints -1);
        tmp2 = j%(edgePoints - 1);
        switch(tmp){
            case 0: i1 = outerPoints + j; i2 = i1 + 1; break;
            case 1: i1 = outerPoints + edgePoints + tmp2*edgePoints - 1; i2 = i1 + edgePoints; break;
            case 2: i1 = outerPoints + edgePoints*edgePoints - tmp2 - 1; i2 = i1 - 1; break;
            case 3: i1 = outerPoints + (edgePoints - tmp2 - 1)*edgePoints; i2 = i1 - edgePoints; break;
        }

        pointsList.push_back(this->points[i1]);
        pointsList.push_back(this->points[i2]);
        pointsList.push_back(this->points[base + i2]);
        pointsList.push_back(this->points[base + i1]);
        this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
        pointsList.clear();

        if(j == 0) {
            pointsList.push_back(this->points[j1]);
            pointsList.push_back(this->points[i1]);
            pointsList.push_back(this->points[base + i1]);
            pointsList.push_back(this->points[base + j1]);
            this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
            pointsList.clear();
        }

        pointsList.push_back(this->points[j2]);
        pointsList.push_back(this->points[base + j2]);
        pointsList.push_back(this->points[base + i2]);
        pointsList.push_back(this->points[i2]);
        this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
        pointsList.clear();

        pointsList.push_back(this->points[base + j1]);
        pointsList.push_back(this->points[base + i1]);
        pointsList.push_back(this->points[base + i2]);
        pointsList.push_back(this->points[base + j2]);
        this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
        pointsList.clear();

    }


    // faces of inner rectangular
    for(unsigned j = 1; j <= edgePoints; j++) {
        j1 = outerPoints + (j-1)*edgePoints;
        j2 = outerPoints + j*edgePoints;

        for(unsigned i = 1; i <= edgePoints; i++){
                i1 = i - 1;
                if(i < edgePoints) {
                    pointsList.push_back(this->points[j1 + i]);
                    pointsList.push_back(this->points[base + j1 + i]);
                    pointsList.push_back(this->points[base + j2 + i]);
                    pointsList.push_back(this->points[j2 + i]);
                    this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
                    pointsList.clear();
                }

                if(j < edgePoints) {
                    pointsList.push_back(this->points[j2 + i1]);
                    pointsList.push_back(this->points[j2 + i]);
                    pointsList.push_back(this->points[base + j2 + i]);
                    pointsList.push_back(this->points[base + j2 + i1]);
                    this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
                    pointsList.clear();
                }

                pointsList.push_back(this->points[base + j1 + i1]);
                pointsList.push_back(this->points[base + j2 + i1]);
                pointsList.push_back(this->points[base + j2 + i]);
                pointsList.push_back(this->points[base + j1 + i]);
                this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
                pointsList.clear();
        }
    }
}

void Mesh::extrudeFaces() {
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned base = NODE(0)*sidePoints + pow(edgePoints,2);
    unsigned baseF = this->numberOfFaces;
    unsigned ID;
    containerPoints pointsList, pointFaces;

    for(unsigned k = 1; k < NODE(1); k++) {

        for(unsigned j = 0; j< baseF; j++) {

            pointFaces = this->faces[j].getPointsList();

            for(containerPoints::iterator it = pointFaces.begin(); it != pointFaces.end(); it++) {
                ID = it->getID() + k*base - 1;
                pointsList.push_back(this->points[ID]);
            }
            this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
            pointsList.clear();
        }
    }

    this->numberOfInternalFaces = this->numberOfFaces;
}


void Mesh::cylinderCells() {

    this->baseCells();
    this->extrudeCells();

}

void Mesh::baseCells() {
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned outerPoints = NODE(0)*sidePoints;
    unsigned base = outerPoints + pow(edgePoints,2);
    unsigned baseC = outerPoints + pow(edgePoints - 1,2);
    unsigned j1, j2, i1, i2, tmp, tmp2;
    containerPoints pointsList;

    for(unsigned j = 0; j < NODE(0); j++) {

        j1 = j*sidePoints;
        j2 = (j+1)*sidePoints;
        if(j == NODE(0) -1) j2 = 0;

        // cells of outer circular
        for(unsigned i = 1; i < sidePoints; i++) {
            i1 = i - 1;
            pointsList.push_back(this->points[j1 + i1]);
            pointsList.push_back(this->points[j1 + i]);
            pointsList.push_back(this->points[j2 + i]);
            pointsList.push_back(this->points[j2 + i1]);
            pointsList.push_back(this->points[base + j1 + i1]);
            pointsList.push_back(this->points[base + j1 + i]);
            pointsList.push_back(this->points[base + j2 + i]);
            pointsList.push_back(this->points[base + j2 + i1]);
            this->cells.push_back(Cell(pointsList, HEX8, ++this->numberOfCells));
            pointsList.clear();

            // neighbour and owner
            this->owner.push_back(this->numberOfCells);
            this->neighbor.push_back(this->numberOfCells + 1);

            if(j == 0) {
                this->owner.push_back(this->numberOfCells);
                this->neighbor.push_back(outerPoints - sidePoints + this->numberOfCells);
            }

            this->owner.push_back(this->numberOfCells);
            this->neighbor.push_back(this->numberOfCells + sidePoints);

            this->owner.push_back(this->numberOfCells);
            this->neighbor.push_back(baseC + this->numberOfCells);

        }

        j1 = (j + 1)*sidePoints - 1;
        j2 = (j + 2)*sidePoints - 1;
        if(j == NODE(0) - 1) j2 = sidePoints - 1;
        tmp = j/(edgePoints -1);
        tmp2 = j%(edgePoints - 1);
        switch(tmp) {
            case 0: i1 = outerPoints + j; i2 = i1 + 1; break;
            case 1: i1 = outerPoints + edgePoints + tmp2*edgePoints - 1; i2 = i1 + edgePoints; break;
            case 2: i1 = outerPoints + edgePoints*edgePoints - tmp2 - 1; i2 = i1 - 1; break;
            case 3: i1 = outerPoints + (edgePoints - tmp2 - 1)*edgePoints; i2 = i1 - edgePoints; break;
        }

        pointsList.push_back(this->points[j1]);
        pointsList.push_back(this->points[i1]);
        pointsList.push_back(this->points[i2]);
        pointsList.push_back(this->points[j2]);
        pointsList.push_back(this->points[base + j1]);
        pointsList.push_back(this->points[base + i1]);
        pointsList.push_back(this->points[base + i2]);
        pointsList.push_back(this->points[base + j2]);
        this->cells.push_back(Cell(pointsList, HEX8, ++this->numberOfCells));
        pointsList.clear();

        // neighbour and owner
        this->owner.push_back(this->numberOfCells);
        this->neighbor.push_back(i1 + 1);

        if(j == 0) {
            this->owner.push_back(this->numberOfCells);
            this->neighbor.push_back(outerPoints);
        }

        this->owner.push_back(this->numberOfCells);
        this->neighbor.push_back(this->numberOfCells + 1);

        this->owner.push_back(this->numberOfCells);
        this->neighbor.push_back(baseC + this->numberOfCells);
    }

    // cells of inner rectangular
    for(unsigned j = 1; j < edgePoints; j++){

        j1 = outerPoints + (j-1)*edgePoints;
        j2 = outerPoints + j*edgePoints;

        for(unsigned i = 1; i < edgePoints; i++){
            i1 = i - 1;
            pointsList.push_back(this->points[j1 + i1]);
            pointsList.push_back(this->points[j1 + i]);
            pointsList.push_back(this->points[j2 + i]);
            pointsList.push_back(this->points[j2 + i1]);
            pointsList.push_back(this->points[base + j1 + i1]);
            pointsList.push_back(this->points[base + j1 + i]);
            pointsList.push_back(this->points[base + j2 + i]);
            pointsList.push_back(this->points[base + j2 + i1]);

            this->cells.push_back(Cell(pointsList, HEX8, ++this->numberOfCells));
            pointsList.clear();

            if(i < edgePoints) {
                this->owner.push_back(this->numberOfCells);
                this->neighbor.push_back(this->numberOfCells + 1);
            }

            if(j < edgePoints) {
                this->owner.push_back(this->numberOfCells);
                this->neighbor.push_back(this->numberOfCells + edgePoints - 1);
            }

            this->owner.push_back(this->numberOfCells);
            this->neighbor.push_back(baseC + this->numberOfCells);
        }
    }
}

void Mesh::extrudeCells(){
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned outerPoints = NODE(0)*sidePoints;
    unsigned base = NODE(0)*sidePoints + pow(edgePoints,2);
    unsigned baseC = outerPoints + pow(edgePoints - 1,2);
    unsigned ID;
    containerPoints pointsList, pointCells;

    for(unsigned k = 1; k < NODE(1); k++) {
        for(unsigned j = 0; j< baseC; j++) {
            pointCells = this->cells[j].getPointsList();
            for(containerPoints::iterator it = pointCells.begin(); it != pointCells.end(); it++){
                ID = it->getID() + k*base - 1;
                pointsList.push_back(this->points[ID]);
            }
            this->cells.push_back(Cell(pointsList, HEX8, ++this->numberOfCells));
            pointsList.clear();
        }
    }
}

//void Mesh::cylinderBoundariesBot(){
//    unsigned sidePoints = NODE(0)/8;
//    unsigned edgePoints = NODE(0)/4 + 1;
//    unsigned outerPoints = NODE(0)*sidePoints;
//    unsigned j1, j2, i1, i2, tmp, tmp2;
//    containerPoints node;
//    containerElements face;
//
//    for(unsigned j = 0; j < NODE(0); j++){
//        j1 = j*sidePoints;
//        j2 = (j+1)*sidePoints;
//        if(j == NODE(0) -1) j2 = 0;
//        for(unsigned i = 1; i < sidePoints; i++){
//            node.push_back(this->points[j1 + i - 1]);
//            node.push_back(this->points[j1 + i]);
//            node.push_back(this->points[j2 + i]);
//            node.push_back(this->points[j2 + i - 1]);
//            face.push_back(Element(node, QUAD4, 0));
//            node.clear();
//        }
//        j1 = (j + 1)*sidePoints - 1;
//        j2 = (j + 2)*sidePoints - 1;
//        if(j == NODE(0) - 1) j2 = sidePoints - 1;
//        tmp = j/(edgePoints -1);
//        tmp2 = j%(edgePoints - 1);
//        switch(tmp){
//            case 0: i1 = outerPoints + j; i2 = i1 + 1; break;
//            case 1: i1 = outerPoints + edgePoints + tmp2*edgePoints - 1; i2 = i1 + edgePoints; break;
//            case 2: i1 = outerPoints + edgePoints*edgePoints - tmp2 - 1; i2 = i1 - 1; break;
//            case 3: i1 = outerPoints + (edgePoints - tmp2 - 1)*edgePoints; i2 = i1 - edgePoints; break;
//        }
//        node.push_back(this->points[j1]);
//        node.push_back(this->points[i1]);
//        node.push_back(this->points[i2]);
//        node.push_back(this->points[j2]);
//        face.push_back(Element(node, QUAD4, 0));
//        node.clear();
//    }
//
//    for(unsigned j = 1; j < edgePoints; j++){
//        j1 = outerPoints + (j-1)*edgePoints;
//        j2 = outerPoints + j*edgePoints;
//        for(unsigned i = 1; i < edgePoints; i++){
//            node.push_back(this->points[j1 + i - 1]);
//            node.push_back(this->points[j1 + i]);
//            node.push_back(this->points[j2 + i]);
//            node.push_back(this->points[j2 + i - 1]);
//            face.push_back(Element(node, QUAD4, 0));
//            node.clear();
//        }
//    }
//    this->boundaries.push_back(face);
//    face.clear();
//}
//
//void Mesh::cylinderBoundariesTop(){
//    unsigned sidePoints = NODE(0)/8;
//    unsigned edgePoints = NODE(0)/4 + 1;
//    unsigned base = NODE(0)*sidePoints + pow(edgePoints,2);
//    unsigned ID;
//    containerPoints node;
//    containerElements face1, face2;
//    face1 = this->boundaries[0];
//    for(containerElements::iterator j = face1.begin(); j != face1.end(); j++){
//        for(unsigned i = 1; i <= 4; i++){
//            ID = (j->getNode(i)).getID() + NODE(1)*base - 1;
//            node.push_back(nodes[ID]);
//        }
//        face2.push_back(Element(node, QUAD4, 0));
//        node.clear();
//    }
//    this->boundaries.push_back(face2);
//    face1.clear();
//    face2.clear();
//}
//
//void Mesh::cylinderBoundariesAround()
//{
//    unsigned sidePoints = NODE(0)/8;
//    unsigned edgePoints = NODE(0)/4 + 1;
//    unsigned base = NODE(0)*sidePoints + pow(edgePoints,2);
//    unsigned j1, j2, k1, k2;
//    containerPoints node;
//    containerElements face;
//    for(unsigned k = 1; k <= NODE(1); k++){
//        k1 = (k-1)*base;
//        k2 = k*base;
//        for(unsigned j = 1; j <= NODE(0); j++){
//            j1 = (j-1)*sidePoints;
//            j2 = j*sidePoints;
//            if(j == NODE(0))j2 = 0;
//            node.push_back(this->points[k1 + j1]);
//            node.push_back(this->points[k2 + j1]);
//            node.push_back(this->points[k2 + j2 ]);
//            node.push_back(this->points[k1 + j2]);
//            face.push_back(Element(node, QUAD4, 0));
//            node.clear();
//        }
//    }
//    this->boundaries.push_back(face);
//    face.clear();
//}




