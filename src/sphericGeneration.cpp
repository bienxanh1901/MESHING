#include "../include/Mesh.h"

void Mesh::sphericGenerator() {
    this->sphericPoints();
    this->sphericCells();
}

void Mesh::sphericPoints() {
    this->topPartPoints();
    this->leftRightBotPartsPoints();
    this->frontRearPartsPoints();
    this->cubicPartPoints();
}

void Mesh::cubicPartPoints() {
    double R = DIM(1);
    double halfR = 0.5*R;
    double p2 = halfR/sqrt(2.0);
    double corner = halfR - p2*(1.0 - tan(PI/6.0))/sqrt(2.0);
    double sizeC = 2.0*corner/(double)(NODE(0)/4);

    for(double z = corner; z >= -corner - EPS; z-= sizeC) {

        for(double x = -corner; x <= corner + EPS; x+= sizeC) {

            for(double y = -corner; y <= corner + EPS; y+= sizeC) {
                this->addPoint(x, y , z);
            }
        }
    }
}

void Mesh::topPartPoints() {
    double R = DIM(1);
    double p2 = 0.5/sqrt(2.0);
    double corner = 0.5 - p2*(1.0 - tan(PI/6.0))/sqrt(2.0);
    double sizeM = 2.0/(double)(NODE(0)/4);
    double sizeC = 2.0*corner/(double)(NODE(0)/4);
    double sizeM2, norm, R2;
    unsigned sidePoints = NODE(0)/8;

    TypeVector<double> point, unit;

    for (double x = -1.0, x2 = -corner; x <= 1.0 + EPS; x+= sizeM, x2+= sizeC) {

        for (double y = -1.0, y2 = -corner; y <= 1.0 + EPS; y+= sizeM, y2+= sizeC) {
            point = this->cubic2Spheric(x, y, 1.0);
            unit = point;
            point-= TypeVector<double>(x2, y2, corner);
            norm = point.norm();
            sizeM2 = norm/(double)sidePoints;
            R2 = 1.0 - norm + sizeM2;

            for( double step = 1.0; step >= R2 - EPS; step-= sizeM2) {
                this->addPoint(unit*(step*R));
            }
        }
    }
}

void Mesh::leftRightBotPartsPoints() {
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned layer = sidePoints*edgePoints;
    unsigned base = layer*edgePoints;
    double angle;
    TypeVector<double> axis;
    Point point;

    //right part
    angle = PI/2.0;
    axis = TypeVector<double>(0.0, 1.0, 0.0);

    for(unsigned i = layer; i < base; i++) {
        point = this->points[i].rotate(angle, axis);
        this->addPoint(point);
    }

    //bottom part
    angle = PI;

    for(unsigned i = layer; i < base; i++) {
        point = this->points[i].rotate(angle, axis);
        this->addPoint(point);
    }

    //left part
    angle = 3.0*PI/2.0;

    for(unsigned i = layer; i < base - layer; i++) {
        point = this->points[i].rotate(angle, axis);
        this->addPoint(point);
    }
}

void Mesh::frontRearPartsPoints() {
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned layer = sidePoints*edgePoints;
    unsigned base = layer*edgePoints;
    double angle, startp, endp;
    TypeVector<double> axis;
    Point point;

    //front part
    angle = 3.0*PI/2.0;
    axis = TypeVector<double>(0.0, 0.0, 1.0);

    for(unsigned j = 0; j < edgePoints - 2; j++){
        startp = base + j*layer + sidePoints;
        endp = startp + (edgePoints - 2)*sidePoints;
        for(unsigned i = startp; i < endp; i++) {
            point = this->points[i].rotate(angle, axis);
            this->addPoint(point);
        }
    }

    //rear part
    angle = PI/2.0;
    axis = TypeVector<double>(-1.0, 0.0, 0.0);
    for(unsigned j = 0; j < edgePoints - 2; j++) {
        startp = (j + 1)*layer + sidePoints;
        endp = startp + (edgePoints - 2)*sidePoints;
        for(unsigned i = startp; i < endp; i++) {
            point = this->points[i].rotate(angle, axis);
            this->addPoint(point);
        }
    }
}

TypeVector<double> Mesh::cubic2Spheric(double x, double y, double z) {
    double xx = x*x;
    double yy = y*y;
    double zz = z*z;
    return TypeVector<double>(x*sqrt(1.0 - yy/2.0 - zz/2.0 + yy*zz/3.0),
                              y*sqrt(1.0 - xx/2.0 - zz/2.0 + xx*zz/3.0),
                              z*sqrt(1.0 - xx/2.0 - yy/2.0 + xx*yy/3.0));
}

void Mesh::firstPartFaces() {
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned layer = sidePoints*edgePoints;
    unsigned layerC= edgePoints*edgePoints;
    unsigned outerPoints= NODE(0)*layer + 2*(edgePoints - 2)*(edgePoints - 2)*sidePoints;
    unsigned innerPoints= edgePoints*layerC;
    unsigned i1, i2, j1, j2, k1, k2, tmp, tmp2;

    containerPoints pointsList;

    // left right bottom top faces
    for(unsigned i = 0; i < NODE(0); i++) {
        i1 = i*layer;
        i2 = i1 + layer;
        if(i == NODE(0) -1) i2 = 0;
        for(unsigned j = 0; j < edgePoints; j++) {
            j1 = j*sidePoints;
            j2 = j1 + sidePoints;
            for(unsigned k = 1; k < sidePoints; k++) {
                k1 = k - 1;

                if(i == 0) {
                    pointsList.push_back(this->points[i1 + j1 + k1]);
                    pointsList.push_back(this->points[i1 + j2 + k1]);
                    pointsList.push_back(this->points[i1 + j2 + k]);
                    pointsList.push_back(this->points[i1 + j1 + k]);
                    this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
                    pointsList.clear();
                }

                if(i < NODE(0) - 1) {
                    pointsList.push_back(this->points[i2 + j1 + k1]);
                    pointsList.push_back(this->points[i2 + j1 + k]);
                    pointsList.push_back(this->points[i2 + j2 + k]);
                    pointsList.push_back(this->points[i2 + j2 + k1]);
                    this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
                    pointsList.clear();
                }

                if(j == 0) {
                    pointsList.push_back(this->points[i1 + j1 + k1]);
                    pointsList.push_back(this->points[i1 + j1 + k]);
                    pointsList.push_back(this->points[i2 + j1 + k]);
                    pointsList.push_back(this->points[i2 + j1 + k1]);
                    this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
                    pointsList.clear();
                }

                pointsList.push_back(this->points[i1 + j2 + k1]);
                pointsList.push_back(this->points[i2 + j2 + k1]);
                pointsList.push_back(this->points[i2 + j2 + k]);
                pointsList.push_back(this->points[i1 + j2 + k]);
                this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
                pointsList.clear();

                pointsList.push_back(this->points[i1 + j1 + k]);
                pointsList.push_back(this->points[i1 + j2 + k]);
                pointsList.push_back(this->points[i2 + j2 + k]);
                pointsList.push_back(this->points[i2 + j1 + k]);
                this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
                pointsList.clear();
            }

            //connects with cubic
            j1 = (j + 1)*sidePoints - 1;
            j2 = j1 + sidePoints;

            tmp = i/(edgePoints -1);
            tmp2 = i%(edgePoints - 1);
            switch(tmp){
                case 0: k1 = outerPoints + i*edgePoints + j; k2 = k1 + edgePoints; break;
                case 1: k1 = outerPoints + i*edgePoints + tmp2*(layerC - edgePoints)  + j; k2 = k1 + layerC; break;
                case 2: k1 = outerPoints + innerPoints - tmp2*edgePoints - edgePoints + j; k2 = k1 - edgePoints; break;
                case 3: k1 = outerPoints + (edgePoints - tmp2 - 1)*layerC + j; k2 = k1 - layerC; break;
            }

            if(i == 0) {
                pointsList.push_back(this->points[i1 + j1]);
                pointsList.push_back(this->points[i1 + j2]);
                pointsList.push_back(this->points[k1 + 1]);
                pointsList.push_back(this->points[k1]);
                this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
                pointsList.clear();
            }

            if(i < NODE(0) - 1) {
                pointsList.push_back(this->points[i2 + j1]);
                pointsList.push_back(this->points[k2]);
                pointsList.push_back(this->points[k2 + 1]);
                pointsList.push_back(this->points[i2 + j2]);
                this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
                pointsList.clear();
            }

            if(j == 0) {
                pointsList.push_back(this->points[i1 + j1]);
                pointsList.push_back(this->points[k1]);
                pointsList.push_back(this->points[k2]);
                pointsList.push_back(this->points[i2 + j1]);
                this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
                pointsList.clear();
            }

            pointsList.push_back(this->points[i1 + j2]);
            pointsList.push_back(this->points[i2 + j2]);
            pointsList.push_back(this->points[k2 + 1]);
            pointsList.push_back(this->points[k1 + 1]);
            this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
            pointsList.clear();

            pointsList.push_back(this->points[k1]);
            pointsList.push_back(this->points[k1 + 1]);
            pointsList.push_back(this->points[k2 + 1]);
            pointsList.push_back(this->points[k2]);
            this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
            pointsList.clear();

        }
    }

    // front faces
    unsigned base = layer*edgePoints;
    unsigned base2 = base + base - layer;
    unsigned base3 = base2 + base - layer;
    unsigned base4 = base3 + base - 2*layer;

    for(unsigned i = 0; i < edgePoints; i++) {
        i1 = base4 + i*layer;
        i2 = i1 + layer;

        for(unsigned j = 0; j < edgePoints; j++) {
                j1 = j*sidePoints;
                j2 = j1 + sidePoints;

            for(unsigned k = 1; k < sidePoints; k++) {
                k1 = k - 1;

                if(i < edgePoints - 1) {
                    if(j == 0) pointsList.push_back(this->points[i2 - base4 + k1]);
                    else pointsList.push_back(this->points[i2 + j1 + k1]);

                    if(j == edgePoints - 1) {
                        pointsList.push_back(this->points[base3 - (i + 2)*layer + k1]);
                        pointsList.push_back(this->points[base3 - (i + 2)*layer + k]);
                    } else {
                        pointsList.push_back(this->points[i2 + j2 + k1]);
                        pointsList.push_back(this->points[i2 + j2 + k]);
                    }

                    if(j == 0) pointsList.push_back(this->points[i2 - base + k]);
                    else pointsList.push_back(this->points[i2 + j2 + k]);

                    this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
                    pointsList.clear();
                }

                if(j < edgePoints - 1) {
                    if(i == 0) {
                        pointsList.push_back(this->points[base4 - j*layer + k1]);
                        pointsList.push_back(this->points[base4 - j*layer + k]);
                    } else {
                        pointsList.push_back(this->points[i1 + j2 + k1]);
                        pointsList.push_back(this->points[i1 + j2 + k]);
                    }

                    if(i == edgePoints - 1) {
                        pointsList.push_back(this->points[base2 + j*layer + k]);
                        pointsList.push_back(this->points[base2 + j*layer + k1]);
                    } else {
                        pointsList.push_back(this->points[i2 + j2 + k]);
                        pointsList.push_back(this->points[i2 + j2 + k1]);
                    }
                    this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
                    pointsList.clear();
                }

                if(j == 0) {
                    pointsList.push_back(this->points[i2 + k]);
                    pointsList.push_back(this->points[i1 + k]);
                } else {
                    if(i == edgePoints - 1) pointsList.push_back(this->points[base2 + j*layer + k]);
                    else pointsList.push_back(this->points[i2 + j2 + k]);

                    if(i == 0) pointsList.push_back(this->points[base4 - j*layer + k]);
                    else pointsList.push_back(this->points[i1 + j2 + k]);
                }

                if(j == edgePoints - 1) {
                    pointsList.push_back(this->points[base3 - (i + 1)*layer + k]);
                    pointsList.push_back(this->points[base3 - (i + 2)*layer + k]);
                } else {
                    if(i == 0) pointsList.push_back(this->points[base4 - j*layer + k]);
                    else pointsList.push_back(this->points[i1 + j2 + k]);

                    if(i == edgePoints - 1) pointsList.push_back(this->points[base2 + j*layer + k]);
                    else pointsList.push_back(this->points[i2 + j2 + k]);
                }

                this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
                pointsList.clear();
            }

            //connects with cubic
            i1 = base4 + (i + 1)*layer - 1;
            i2 = i1 + layer;
            j1 = (j + 1)*sidePoints - 1;
            j2 = j1 + sidePoints;

            k1 = outerPoints + j*layerC + i*edgePoints;
            k2 = k1 + layerC;

            if(i < edgePoints - 1) {
                pointsList.push_back(this->points[i2 + j1]);
                pointsList.push_back(this->points[i2 + j2]);
                pointsList.push_back(this->points[k2 + edgePoints]);
                pointsList.push_back(this->points[k1 + edgePoints]);
                this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
                pointsList.clear();
            }

            if(j < edgePoints - 1) {
                pointsList.push_back(this->points[i1 + j2]);
                pointsList.push_back(this->points[k2]);
                pointsList.push_back(this->points[k2 + edgePoints]);
                pointsList.push_back(this->points[i2 + j2]);
                this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
                pointsList.clear();
            }

            pointsList.push_back(this->points[k1]);
            pointsList.push_back(this->points[k1 + 1]);
            pointsList.push_back(this->points[k2 + 1]);
            pointsList.push_back(this->points[k2]);
            this->faces.push_back(Face(pointsList, QUAD4, ++numberOfFaces));
            pointsList.clear();

        }
    }
}


void Mesh::sphericCells() {
    this->leftRightBotTopPartsCells();
    this->frontPartCells();
    this->rearPartCells();
    this->cubicPartCells();
}

void Mesh::leftRightBotTopPartsCells() {
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned layer = sidePoints*edgePoints;
    unsigned edgeCells = NODE(0)/4;
    unsigned layerC = sidePoints*edgeCells;
    unsigned frontC = (edgeCells - 2)*(edgeCells - 2)*sidePoints + 4*(edgeCells - 1)*sidePoints;
    unsigned baseC  = layerC*NODE(0);
    unsigned baseC2  = baseC + frontC ;
    unsigned i1, i2, i3, i4, j1, j2, k1, k2, k3;

    i3 = baseC;
    i4 = baseC2 + 4*(edgeCells - 1)*sidePoints;
    for(unsigned i = 0; i < NODE(0); i++) {

        i1 = i*layer;
        i2 = i1 + layer;
        if(i == NODE(0) - 1) i2 = 0;

        // for cell connection with front
        if(i%edgeCells != 0) i3+= sidePoints;
        if(i == NODE(0) - 1) i3 = baseC;

        // for cell connection with rear
        if(i == 1) i4 += 4*(edgeCells - 1)*sidePoints;
        if(i%edgeCells != 0) i4-= sidePoints;
        if(i == 0) i4 = baseC2;

        for(unsigned j = 0; j < edgePoints - 1; j++) {
            j1 = j*sidePoints;
            j2 = j1 + sidePoints;


            for(unsigned k = 1; k < sidePoints; k++) {
                k1 = k - 1;
                this->addCell(i1 + j1 + k1, i2 + j1 + k1, i2 + j2 + k1, i1 + j2 + k1,
                              i1 + j1 + k, i2 + j1 + k, i2 + j2 + k, i1 + j2 + k);
                if(i == 0) {
                    this->addFace(i1 + j1 + k1, i1 + j2 + k1, i1 + j2 + k, i1 + j1 + k);
                    this->addOwner(this->numberOfCells);
                    this->addNeighbor(baseC - layerC + j1 + k);
                }

                if(i < NODE(0) - 1) {
                    this->addFace(i2 + j1 + k1, i2 + j1 + k, i2 + j2 + k, i2 + j2 + k1);
                    this->addOwner(this->numberOfCells);
                    this->addNeighbor(this->numberOfCells + layerC);
                }

                if(j == 0) {
                    this->addFace(i1 + j1 + k1, i1 + j1 + k, i2 + j1 + k, i2 + j1 + k1);
                    this->addOwner(this->numberOfCells);
                    this->addNeighbor(i3 + k);
                }

                this->addFace(i1 + j2 + k1, i2 + j2 + k1, i2 + j2 + k, i1 + j2 + k);
                this->addOwner(this->numberOfCells);
                if(j == edgePoints - 2) this->addNeighbor(i4 + k);
                else this->addNeighbor(this->numberOfCells + sidePoints);

                this->addFace(i1 + j1 + k, i1 + j2 + k, i2 + j2 + k, i2 + j1 + k);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(this->numberOfCells + 1);
            }

            //connects with cubic
            j1 = (j + 1)*sidePoints - 1;
            j2 = j1 + sidePoints;

            this->findPointsconnected3D(i, j, k1, k2, k3);

            this->addCell(i1 + j1, i2 + j1, i2 + j2, i1 + j2,
                          k1, k2, k2 + 1, k1 + 1);
            if(i == 0) {
                this->addFace(i1 + j1, i1 + j2, k1 + 1, k1);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(baseC - layerC + j1 + 1);
            }

            if(i < NODE(0) - 1) {
                this->addFace(i2 + j1, k2, k2 + 1, i2 + j2);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(this->numberOfCells + layerC);
            }

            if(j == 0) {
                this->addFace(i1 + j1, k1, k2, i2 + j1);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(i3 + sidePoints);
            }

            this->addFace(i1 + j2, i2 + j2, k2 + 1, k1 + 1);
            this->addOwner(this->numberOfCells);
            if(j == edgePoints - 2) this->addNeighbor(i4 + sidePoints);
            else this->addNeighbor(this->numberOfCells + sidePoints);

            this->addFace(k1, k1 + 1, k2 + 1, k2);
            this->addOwner(this->numberOfCells);
            this->addNeighbor(k3);
        }
    }
}

void Mesh::frontPartCells() {
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned layer = sidePoints*edgePoints;
    unsigned layerC = edgePoints*edgePoints;
    unsigned base = NODE(0)*layer;
    unsigned outerPoints= base + 2*(edgePoints - 2)*(edgePoints - 2)*sidePoints;
    unsigned i1, i2, j1, j2, k1, k2;

    containerPoints pointsList;

    this->sphericFrontConnectivity();

    for(unsigned i = 1; i < edgePoints - 2; i++) {
        i1 = base + (i - 1)*(edgePoints - 2)*sidePoints;
        i2 = i1 + (edgePoints - 2)*sidePoints;
        for(unsigned j = 1; j < edgePoints - 2; j++) {
            j1 = (j - 1)*sidePoints;
            j2 = j1 + sidePoints;

            for(unsigned k = 1; k < sidePoints; k++) {
                k1 = k - 1;

                this->addCell(i1 + j1 + k1, i2 + j1 + k1, i2 + j2 + k1, i1 + j2 + k1,
                              i1 + j1 + k, i2 + j1 + k, i2 + j2 + k, i1 + j2 + k);

                if(i < edgePoints - 3) {
                    this->addFace(i2 + j1 + k1, i2 + j1 + k2, i2 + j2 + k2, i2 + j2 + k1);
                    this->addOwner(this->numberOfCells);
                    this->addNeighbor(this->numberOfCells + (edgePoints - 3)*sidePoints);
                }

                if(i < NODE(0) - 1) {
                    this->addFace(i1 + j2 + k1, i2 + j2 + k1, i2 + j2 + k2, i1 + j2 + k1);
                    this->addOwner(this->numberOfCells);
                    this->addNeighbor(this->numberOfCells + sidePoints);
                }

                this->addFace(i1 + j1 + k2, i1 + j2 + k2, i2 + j2 + k2, i2 + j1 + k2);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(numberOfCells + 1);
            }

            //connects with cubic
            j1 = j*sidePoints - 1;
            j2 = j1 + sidePoints;
            k1 = outerPoints + j*edgePoints + i*layerC;
            k2 = k1 + layerC;

            this->addCell(i1 + j1, i2 + j1, i2 + j2, i1 + j2,
                          k1, k2, k2 + edgePoints, k1 + edgePoints);
        }
    }
}

void Mesh::rearPartCells() {
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned layer = sidePoints*edgePoints;
    unsigned layerC = edgePoints*edgePoints;
    unsigned base = NODE(0)*layer + (edgePoints - 2)*(edgePoints - 2)*sidePoints;
    unsigned outerPoints= base + (edgePoints - 2)*(edgePoints - 2)*sidePoints;
    unsigned i1, i2, j1, j2, k1, k2;

    containerPoints pointsList;



    this->sphericRearConnectivity();

    for(unsigned i = 1; i < edgePoints - 2; i++) {
        i1 = base + (i - 1)*(edgePoints - 2)*sidePoints;
        i2 = i1 + (edgePoints - 2)*sidePoints;
        for(unsigned j = 1; j < edgePoints - 2; j++) {
            j1 = (j - 1)*sidePoints;
            j2 = j1 + sidePoints;

            for(unsigned k = 1; k < sidePoints; k++) {
                k1 = k - 1;

                this->addCell(i1 + j1 + k1, i2 + j1 + k1, i2 + j2 + k1, i1 + j2 + k1,
                              i1 + j1 + k, i2 + j1 + k, i2 + j2 + k, i1 + j2 + k);

                if(i < edgePoints - 3) {
                    this->addFace(i2 + j1 + k1, i2 + j1 + k2, i2 + j2 + k2, i2 + j2 + k1);
                    this->addOwner(this->numberOfCells);
                    this->addNeighbor(this->numberOfCells + (edgePoints - 3)*sidePoints);
                }

                if(i < NODE(0) - 1) {
                    this->addFace(i1 + j2 + k1, i2 + j2 + k1, i2 + j2 + k2, i1 + j2 + k1);
                    this->addOwner(this->numberOfCells);
                    this->addNeighbor(this->numberOfCells + sidePoints);
                }

                this->addFace(i1 + j1 + k2, i1 + j2 + k2, i2 + j2 + k2, i2 + j1 + k2);
                this->addOwner(this->numberOfCells);
                this->addNeighbor(numberOfCells + 1);
                }

            //connects with cubic
            j1 = j*sidePoints - 1;
            j2 = j1 + sidePoints;
            k1 = outerPoints + j*layerC + (i + 1)*edgePoints - 1;
            k2 = k1 + layerC;

            this->addCell(i1 + j1, i2 + j1, i2 + j2, i1 + j2,
                          k1, k1 + edgePoints, k2 + edgePoints, k2);
        }
    }
}

void Mesh::cubicPartCells() {
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned edgeCells = NODE(0)/4;
    unsigned layer = sidePoints*edgePoints;
    unsigned layerC= edgePoints*edgePoints;
    unsigned layerCells = edgeCells*edgeCells;
    unsigned outerPoints= NODE(0)*layer + 2*(edgePoints - 2)*(edgePoints - 2)*sidePoints;
    unsigned i1, i2, j1, k1, k2;

    containerPoints pointsList;

    for(unsigned k = 1; k < edgePoints; k++) {
        k1 = outerPoints + (k - 1)*layerC;
        k2 = k1 + layerC;
        for(unsigned i = 1; i < edgePoints; i++) {
            i1 = (i - 1)*edgePoints;
            i2 = i1 + edgePoints;
            for(unsigned j = 1; j < edgePoints; j++) {
                j1 = j - 1;

                this->addCell(i1 + j1 + k1, i2 + j1 + k1, i2 + j + k1, i1 + j + k1,
                          i1 + j1 + k2, i2 + j1 + k2, i2 + j + k2, i1 + j + k2);

                if(i < edgeCells) {
                    this->addFace(k1 + j1 + i2, k2 + j1 + i2, k2 + j + i2, k1 + j + i2);
                    this->addOwner(this->numberOfCells);
                    this->addNeighbor(this->numberOfCells + edgeCells);
                }

                if(j < edgeCells) {
                    this->addFace(k1 + j + i1, k1 + j + i2, k2 + j + i2, k2 + j + i1);
                    this->addOwner(this->numberOfCells);
                    this->addNeighbor(this->numberOfCells + 1);
                }

                if(k < edgeCells) {
                    this->addFace(k2 + j1 + i1, k2 + j + i1, k2 + j + i2, k2 + j1 + i2);
                    this->addOwner(this->numberOfCells);
                    this->addNeighbor(this->numberOfCells + layerCells);
                }
            }
        }
    }

}
