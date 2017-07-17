#include "../../include/Shape.h"

void Shape::editCUBOID(unsigned layer) {

    double length, width, height;
    double sizeX, sizeY, sizeZ;
    unsigned cellX, cellY, cellZ;
    arrDouble dimOfLayer(this->numberOfDims);
    arrDouble sizesOfLayer(this->numberOfDims);
    arrUnsgn  cellsOfLayer(this->numberOfDims);

    if(layer == 1) {

        cout << "input dimension of layer 1 (length, width, height):\n";
        cin >> length >> width >> height;

        cout << "input mesh sizes of layer 1 (sizeX, sizeY, sizeZ):\n";
        cin >> sizeX >> sizeY >> sizeZ;

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

        for(unsigned i = 0; i < this->numberOfLayers; i++) {

            if(i > 0) {

                dimOfLayer.insert(2, (this->dim[i])[2]);
                sizesOfLayer.insert(2, (this->cellSizes[i])[2]);
                dimOfLayer.insert(2, (this->cellNumbers[i])[2]);

            }

            this->dim[i] = dimOfLayer;
            this->cellSizes[i] = sizesOfLayer;
            this->cellNumbers[i] = cellsOfLayer;

        }

    } else {

        cout << "input height of layer " << layer << ":\n";
        cin >> height;

        cout << "input mesh size of height of layer " << layer << ":\n";
        cin >> sizeZ;

        cellZ = (unsigned)ROUNDED(height/sizeZ, 0.0);
        sizeZ = height/(double)cellZ;


        (this->dim[layer - 1]).insert(2, height);
        (this->cellSizes[layer - 1]).insert(2, sizeZ);
        (this->cellNumbers[layer - 1]).insert(2, cellZ);

    }

}
