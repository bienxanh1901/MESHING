#include "../include/Shape.h"

void Shape::addCUBOID() {

    double length, width, height;
    double sizeX, sizeY, sizeZ;
    unsigned cellX, cellY, cellZ;
    arrDouble dimOfLayer(this->numberOfDims);
    arrDouble sizesOfLayer(this->numberOfDims);
    arrUnsgn  cellsOfLayer(this->numberOfDims);

    if(this->numberOfLayers == 1) {

        cout << "input dimension of layer 1 (length, width, height):\n";
        cin >> length << width << height;

        cout << "input mesh sizes of layer 1 (sizeX, sizeY, sizeZ):\n";
        cin >> sizeX << sizeY << sizeZ;

        dimOfLayer.insert(0, length);
        dimOfLayer.insert(1, width);
        dimOfLayer.insert(2, height);

        cellX = (unsigned)ROUNDED(length/sizeX, 0.0);
        cellY = (unsigned)ROUNDED(width/sizeY, 0.0);
        cellZ = (unsigned)ROUNDED(height/sizeZ, 0.0);
        sizeX = length/(double)cellX;
        sizeY = width/(double)cellY;
        sizeZ = height/(double)cellZ;

        sizesOfLayer.insert(0, sizeX);
        sizesOfLayer.insert(1, sizeY);
        sizesOfLayer.insert(2, sizeZ);

        cellsOfLayer.insert(0, cellX);
        cellsOfLayer.insert(1, cellY);
        cellsOfLayer.insert(2, cellZ);

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
        sizesOfLayer.insert(1, size2[1]);
        sizesOfLayer.insert(2, sizeZ);

        cellsOfLayer.insert(0, cell2[0]);
        cellsOfLayer.insert(1, cell2[1]);
        cellsOfLayer.insert(2, cellZ);
    }

    this->dim.push_back(dimOfLayer);
    this->cellSizes.push_back(sizesOfLayer);
    this->cellNumbers.push_back(cellsOfLayer);
}
