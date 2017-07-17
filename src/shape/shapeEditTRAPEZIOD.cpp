#include "../../include/Shape.h"


void Shape::editTRAPEZIOID(unsigned layer) {

    double length, width, height, length2, width2;
    double sizeX, sizeY, sizeZ;
    unsigned cellX, cellY, cellZ;
    arrDouble dimOfLayer(this->numberOfDims);
    arrDouble sizesOfLayer(3);
    arrUnsgn  cellsOfLayer(3);

    if(layer == 1) {

        cout << "input dimension of bottom base of layer 1 (length, width, height):\n";
        cin >> length >> width >> height;

        cout << "input mesh sizes of bottom base of layer 1 (sizeX, sizeY, sizeZ):\n";
        cin >> sizeX >> sizeY >> sizeZ;

        cout << "input dimension of top base of layer 1 (length, width):\n";
        cin >> length2 >> width2;

        dimOfLayer.insert(0, length);
        dimOfLayer.insert(1, width);
        dimOfLayer.insert(2, height);
        dimOfLayer.insert(3, length2);
        dimOfLayer.insert(4, width2);

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


                dimOfLayer.insert(0, (this->dim[i - 1])[3]);
                dimOfLayer.insert(1, (this->dim[i - 1])[4]);
                dimOfLayer.insert(2, (this->dim[i])[2]);
                dimOfLayer.insert(3, (this->dim[i])[3]);
                dimOfLayer.insert(4, (this->dim[i])[4]);
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

        cout << "input dimension of top base of layer " << layer << "(length, width):\n";
        cin >> length2 >> width2;


        cellZ = (unsigned)ROUNDED(height/sizeZ, 0.0);
        sizeZ = height/(double)cellZ;

        (this->dim[layer - 1]).insert(2, height);
        (this->dim[layer - 1]).insert(3, length2);
        (this->dim[layer - 1]).insert(4, width2);

        (this->dim[layer]).insert(0, length2);
        (this->dim[layer]).insert(1, width2);

        (this->cellSizes[layer - 1]).insert(2, sizeZ);
        (this->cellNumbers[layer - 1]).insert(2, cellZ);
    }


}
