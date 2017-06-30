#include "../include/Mesh.h"

void Mesh::sphericGenerator()
{
    this->sphericPoints();
    this->sphericCells();
}

void Mesh::sphericPoints() {
    this->firstPart();
}

void Mesh::firstPart() {
    double R = DIM(1);
    double halfR = 0.5*R;
    double p2 = halfR/sqrt(2.0);
    double corner = halfR - p2*(1.0 - tan(PI/6.0))/sqrt(2.0);
    double sizeM = 2.0*R/(double)(NODE(0)/4);
    double sizeC = 2.0*corner/(double)(NODE(0)/4);
    double sizeM2, norm, R2;
    double z = R;
    unsigned sidePoints = NODE(0)/8, cnt = 0;

    TypeVector<double> point, unit;

    for (double x = -R, x2 = -corner; x <= R + EPS; x+= sizeM, x2+= sizeC) {

        for (double y = -R, y2 = -corner; y <= R + EPS; y+= sizeM, y2+= sizeC) {
            point = this->cubic2Spheric(x, y, z);
            unit = point.unit();
            point-= TypeVector<double>(x2, y2, corner);

            norm = point.norm();
            sizeM2 = norm/(double)sidePoints;
            R2 = R - norm + sizeM2;
            cnt = 0;
            for( double step = R; step >= R2 - EPS; step-= sizeM2) {
                    cnt++;
                this->points.push_back(Point(unit*(step), ++this->numberOfPoints));
            }
        }
    }


}

TypeVector<double> Mesh::cubic2Spheric(double& x, double& y, double& z) {
    double xx = x*x;
    double yy = y*y;
    double zz = z*z;
    return TypeVector<double>(x*sqrt(1.0 - yy/2.0 - zz/2.0 + yy*zz/3.0),
                              y*sqrt(1.0 - xx/2.0 - zz/2.0 + xx*zz/3.0),
                              z*sqrt(1.0 - xx/2.0 - yy/2.0 + xx*yy/3.0));
}

void Mesh::sphericCells() {
    unsigned sidePoints = NODE(0)/8;
    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned i1, i2, j1, j2, k1;

    containerPoints pointsList;
    for(unsigned i = 1; i < edgePoints; i++) {
        i1 = (i - 1)*edgePoints*sidePoints;
        i2 = i*edgePoints*sidePoints;
        for(unsigned j = 1; j < edgePoints; j++) {
            j1 = (j - 1)*sidePoints;
            j2 = j*sidePoints;
            for(unsigned k = 1; k < sidePoints; k++) {
                    k1 = k - 1;
                    pointsList.push_back(this->points[i1 + j1 + k1]);
                    pointsList.push_back(this->points[i2 + j1 + k1]);
                    pointsList.push_back(this->points[i2 + j2 + k1]);
                    pointsList.push_back(this->points[i1 + j2 + k1]);
                    pointsList.push_back(this->points[i1 + j1 + k]);
                    pointsList.push_back(this->points[i2 + j1 + k]);
                    pointsList.push_back(this->points[i2 + j2 + k]);
                    pointsList.push_back(this->points[i1 + j2 + k]);
                    this->cells.push_back(Cell(pointsList, HEX8, ++this->numberOfCells));
                    pointsList.clear();

            }
        }
    }
}
