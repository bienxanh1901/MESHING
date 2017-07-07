#include "../include/Mesh.h"

void Mesh::cylinderGeneratior() {

    this->cylinderPoints();
    this->cylinderInternalFacesandCells();
    this->numberOfBoundaries = 3;
    this->cylinderBoundariesBot();
    this->cylinderBoundariesTop();
    this->cylinderBoundariesAround();

}

void Mesh::cylinderPoints() {

    this->basePoints();
    this->extrudePoints();

}

void Mesh::basePoints(){

    double angleSize = 2.0*PI/(double)NODE(0);
    double RX = DIM(1), RY = DIM(3);
    double halfR = 0.5*RX;
    double p2 = halfR/sqrt(2.0);
    double cornerX = halfR - p2*(1.0 - tan(PI/6.0))/sqrt(2.0);
    halfR = 0.5*RY;
    p2 = halfR/sqrt(2.0);
    double cornerY = halfR - p2*(1.0 - tan(PI/6.0))/sqrt(2.0);

    unsigned sidePoints = NODE(0)/8;
    double costheta, sintheta;
    double x, y;
    double sizeX, sizeY;

    //points of outer circular
    for(double theta = -PI/4; theta < 7*PI/4; theta+= angleSize){
        costheta = cos(theta);
        sintheta = sin(theta);

        if(fabs(costheta) >= 1.0/sqrt(2.0)){
            sizeX = (RX - cornerX/fabs(costheta))/sidePoints;
            sizeY = (RY - cornerY/fabs(costheta))/sidePoints;
        }else {
            sizeX = (RX - cornerX/fabs(sintheta))/sidePoints;
            sizeY = (RY - cornerY/fabs(sintheta))/sidePoints;
        }

        for(unsigned i = 0; i < sidePoints; i++){
            x = (RX - (double)i*sizeX)*sintheta;
            y = (RY - (double)i*sizeY)*costheta;
            this->addPoint(x, y, 0.0);
        }
    }

    // points of inner rectangular
    sizeX = 2.0*cornerX/(double)(NODE(0)/4);
    sizeY = 2.0*cornerY/(double)(NODE(0)/4);

    for(y = cornerY; y >= -cornerY - EPS; y-= sizeY){

        for(x = -cornerX; x <= cornerX + EPS; x+= sizeX){

            this->addPoint(x, y, 0.0);
        }
    }
}

void Mesh::extrudePoints() {

    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned base = NODE(0)*sidePoints + pow(edgePoints,2);
    Point point;

    for(double z = SIZE(1); z <= DIM(2) + EPS; z+= SIZE(1)){

        for(unsigned i = 0; i < base; i++){

            point = this->points[i] + Point(0.0, 0.0, z);
            this->addPoint(point);
        }
    }
}

void Mesh::cylinderInternalFacesandCells() {

    this->baseFacesandCells();
    this->extrudeFaces();
    this->extrudeCells();

}

void Mesh::baseFacesandCells(){
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned outerPoints = NODE(0)*sidePoints;
    unsigned base = outerPoints + pow(edgePoints,2);
    unsigned baseC = outerPoints + pow(edgePoints - 1,2);
    unsigned j1, j2, i1, i2;

    // faces and cells of outer circular
    for(unsigned j = 0; j < NODE(0); j++) {

        j1 = j*sidePoints;
        j2 = (j+1)*sidePoints;
        if(j == NODE(0) -1) j2 = 0;

        for(unsigned i = 1; i < sidePoints; i++) {
            i1 = i - 1;

            this-> addCell(j1 + i1, j1 + i, j2 + i, j2 + i1,
                           base + j1 + i1, base + j1 + i, base + j2 + i, base + j2 + i1);
            this->addFace(j1 + i, j2 + i, base + j2 + i, base + j1 + i);
            this->addOwner(this->numberOfCells);
            this->addNeighbor(this->numberOfCells + 1);

            if(j == 0) {
                this->addFace(i1, i, base + i, base + i1);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(outerPoints - sidePoints + this->numberOfCells);
            }

            if(j < NODE(0) -1) {
                this->addFace(j2 + i1, base + j2 + i1, base + j2 + i, j2 + i);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(this->numberOfCells + sidePoints);
            }

            if(NODE(1) > 1) {
                this->addFace(base + j1 + i1, base + j1 + i, base + j2 + i, base + j2 + i1);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(baseC + this->numberOfCells);
            }
        }

        j1 = (j + 1)*sidePoints - 1;
        j2 = (j + 2)*sidePoints - 1;
        if(j == NODE(0) - 1) j2 = sidePoints - 1;

        this->findPointsconnected2D(j, i1, i2);

        this-> addCell(j1, i1, i2, j2,
                           base + j1, base + i1, base + i2, base + j2);
        this->addFace(i1, i2, base + i2, base + i1);
        this->addOwner(this->numberOfCells);
        this->addNeighbor(i1 + 1);

        if(j == 0) {
            this->addFace(j1, i1, base + i1, base + j1);
            this->addOwner(this->numberOfCells);
            this->addNeighbor(outerPoints);
        }

        if(j < NODE(0) -1) {
            this->addFace(j2, base + j2, base + i2, i2);
            this->addOwner(this->numberOfCells);
            this->addNeighbor(this->numberOfCells + 1);
        }

        if(NODE(1) > 1) {
            this->addFace(base + j1, base + i1, base + i2, base + j2);
            this->addOwner(this->numberOfCells);
            this->addNeighbor(baseC + this->numberOfCells);
        }
    }

    // faces and cells of inner rectangular
    for(unsigned j = 1; j < edgePoints; j++) {
        j1 = outerPoints + (j-1)*edgePoints;
        j2 = outerPoints + j*edgePoints;

        for(unsigned i = 1; i < edgePoints; i++){
            i1 = i - 1;

            this-> addCell(j1 + i1, j1 + i, j2 + i, j2 + i1,
                           base + j1 + i1, base + j1 + i, base + j2 + i, base + j2 + i1);

            if(i < edgePoints - 1) {
                this->addFace(j1 + i, base + j1 + i, base + j2 + i, j2 + i);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(this->numberOfCells + 1);
            }

            if(j < edgePoints - 1) {
                this->addFace(j2 + i1, j2 + i, base + j2 + i, base + j2 + i1);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(this->numberOfCells + edgePoints - 1);
            }

            if(NODE(1) > 1) {
                this->addFace(base + j1 + i1, base + j2 + i1, base + j2 + i, base + j1 + i);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(baseC + this->numberOfCells);
            }
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

            this->addFace(pointsList);
        }
    }

    this->numberOfInternalFaces = this->numberOfFaces;
}

void Mesh::extrudeCells() {
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned outerPoints = NODE(0)*sidePoints;
    unsigned base = NODE(0)*sidePoints + pow(edgePoints,2);
    unsigned baseC = outerPoints + pow(edgePoints - 1,2);
    unsigned baseN = this->neighbor.size();
    unsigned ID;
    containerPoints pointsList, pointCells;

    for(unsigned k = 1; k < NODE(1); k++) {
        for(unsigned j = 0; j< baseC; j++) {
            pointCells = this->cells[j].getPointsList();
            for(containerPoints::iterator it = pointCells.begin(); it != pointCells.end(); it++){
                ID = it->getID() + k*base - 1;
                pointsList.push_back(this->points[ID]);
            }
            this->addCell(pointsList);
            this->addOwner(this->numberOfCells);
        }
    }

    //set neighbor
    containerIDs::iterator it;
    for(unsigned k = 1; k < NODE(1); k++) {
        for(unsigned j = 0; j < baseN; j++) {
                ID = this->neighbor[j] + k*baseN;
                if(ID <= this->numberOfCells) this->addNeighbor(ID);
        }
    }
}

void Mesh::cylinderBoundariesBot(){
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned outerPoints = NODE(0)*sidePoints;
    unsigned baseC = outerPoints + pow(edgePoints - 1,2);
    unsigned j1, j2, i1, i2;

    for(unsigned j = 0; j < NODE(0); j++){
        j1 = j*sidePoints;
        j2 = (j+1)*sidePoints;
        if(j == NODE(0) -1) j2 = 0;
        for(unsigned i = 1; i < sidePoints; i++){
            i1 = i - 1;

            this->addFace(j1 + i1, j2 + i1, j2 + i, j1 + i);
            this->addOwner(j1 + i);
        }

        j1 = (j + 1)*sidePoints - 1;
        j2 = (j + 2)*sidePoints - 1;
        if(j == NODE(0) - 1) j2 = sidePoints - 1;

        this->findPointsconnected2D(j, i1, i2);

        this->addFace(j1, j2, i2, i1);
        this->addOwner(j1 + 1);
    }

    for(unsigned j = 1; j < edgePoints; j++){
        j1 = outerPoints + (j-1)*edgePoints;
        j2 = outerPoints + j*edgePoints;
        for(unsigned i = 1; i < edgePoints; i++){
            i1 = i - 1;

            this->addFace(j1 + i1, j1 + i, j2 + i, j2 + i1);
            this->addOwner(j1 + i);
        }
    }
    this->boundaries.push_back(baseC);
}

void Mesh::cylinderBoundariesTop(){
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned outerPoints = NODE(0)*sidePoints;
    unsigned base = outerPoints + pow(edgePoints,2);
    unsigned baseC = outerPoints + pow(edgePoints - 1,2);
    unsigned ID, j1, cnt;
    containerPoints pointsList, pointFaces;

    cnt = NODE(1)*baseC;

    for(unsigned j = this->numberOfInternalFaces; j < this->numberOfInternalFaces + baseC; j++){
        j1 = NODE(1)*base - 1;
        pointFaces = this->faces[j].getPointsList();
        for(containerPoints::iterator it = pointFaces.begin(); it != pointFaces.end(); it++){
            ID = it->getID() + j1;
            pointsList.push_back(this->points[ID]);
        }
        reverse(pointsList.begin(), pointsList.end());

        this->addFace(pointsList);
        this->addOwner(++cnt);
    }
    this->boundaries.push_back(baseC);
}

void Mesh::cylinderBoundariesAround()
{
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned outerPoints = NODE(0)*sidePoints;
    unsigned base = NODE(0)*sidePoints + pow(edgePoints,2);
    unsigned baseC = outerPoints + pow(edgePoints - 1,2);
    unsigned j1, j2, k1, k2, k3;
    containerPoints pointsList;
    for(unsigned k = 1; k <= NODE(1); k++){
        k1 = (k - 1)*base;
        k2 = k*base;
        k3 = (k - 1)*baseC;
        for(unsigned j = 1; j <= NODE(0); j++){
            j1 = (j - 1)*sidePoints;
            j2 = j*sidePoints;
            if(j == NODE(0))j2 = 0;

            this->addFace(k1 + j1, k2 + j1, k2 + j2, k1 + j2);
            this->addOwner(k3 + j1 + 1);
        }
    }
    this->boundaries.push_back(NODE(0)*NODE(1));
}




