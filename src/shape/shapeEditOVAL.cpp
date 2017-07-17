#include "../../include/Shape.h"

void Shape::editOVAL(unsigned layer) {

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
        dimOfLayer.insert(1, height);
        dimOfLayer.insert(2, radius2);

        cellR = (unsigned)ROUNDED(2.0*PI*radius/sizeR, 0.0);
        cellR = (cellR/16 + 1)*16;

        cellZ = (unsigned)ROUNDED(height/sizeZ, 0.0);
        sizeR = 2.0*PI/cellR;
        sizeZ = height/(double)cellZ;

        sizesOfLayer.insert(0, sizeR);
        sizesOfLayer.insert(1, sizeZ);

        cellsOfLayer.insert(0, cellR);
        cellsOfLayer.insert(1, cellZ);

        for(unsigned i = 0; i < this->numberOfLayers; i++) {

            if(i > 0) {

                dimOfLayer.insert(1, (this->dim[i])[1]);
                sizesOfLayer.insert(1, (this->cellSizes[i])[1]);
                dimOfLayer.insert(1, (this->cellNumbers[i])[1]);

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

        (this->dim[layer - 1]).insert(1, height);
        (this->cellSizes[layer - 1]).insert(1, sizeZ);
        (this->cellNumbers[layer - 1]).insert(1, cellZ);


    }

}
