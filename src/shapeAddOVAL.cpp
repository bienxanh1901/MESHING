#include "../include/Shape.h"

void Shape::addOVAL() {

    double radius, radius2, height;
    double sizeR, sizeZ;
    unsigned cellR, cellZ;
    arrDouble dimOfLayer(this->numberOfDims);
    arrDouble sizesOfLayer(2);
    arrUnsgn  cellsOfLayer(2);

    if(this->numberOfLayers == 1) {

        cout << "input dimension of layer 1 (major-radius minor-radius height): ";
        cin >> radius >> radius2 >> height;

        cout << "input mesh sizes of layer 1 (major-sizeR, sizeZ):\n";
        cin >> sizeR >> sizeZ;

        dimOfLayer.insert(0, radius);
        dimOfLayer.insert(1, radius2);
        dimOfLayer.insert(2, height);

        cellR = (unsigned)ROUNDED(2.0*PI*radius/sizeR, 0.0);
        cellR = (cellR/16 + 1)*16;

        cellZ = (unsigned)ROUNDED(height/sizeZ, 0.0);
        sizeR = 2.0*PI/cellR;
        sizeZ = height/(double)cellZ;

        sizesOfLayer.insert(0, sizeR);
        sizesOfLayer.insert(1, sizeZ);

        cellsOfLayer.insert(0, cellR);
        cellsOfLayer.insert(1, cellZ);

    } else {

        arrDouble dim2 = this->dim.back();
        arrDouble size2 = this->cellSizes.back();
        arrUnsgn cell2 = this->cellNumbers.back();
        cout << "input height of layer " << this->numberOfLayers << ":\n";
        cin >> height;

        cout << "input mesh size of height of layer " << this->numberOfLayers << ":\n";
        cin >> sizeZ;

        dimOfLayer.insert(0, dim2[0]);
        dimOfLayer.insert(1, dim2[1]);
        dimOfLayer.insert(2, height);

        cellZ = (unsigned)ROUNDED(height/sizeZ, 0.0);
        sizeZ = height/(double)cellZ;

        sizesOfLayer.insert(0, size2[0]);
        sizesOfLayer.insert(1, sizeZ);

        cellsOfLayer.insert(0, cell2[0]);
        cellsOfLayer.insert(1, cellZ);
    }

    this->dim.push_back(dimOfLayer);
    this->cellSizes.push_back(sizesOfLayer);
    this->cellNumbers.push_back(cellsOfLayer);
}
