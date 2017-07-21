#include "../../include/Shape.h"

//void Shape::addOVAL() {
//
//    double radius, radius2, height;
//    double sizeR, sizeZ;
//    unsigned cellR, cellZ;
//    ArrDouble dimOfLayer(this->numberOfDims);
//    ArrDouble sizesOfLayer(2);
//    ArrUnsgn  cellsOfLayer(2);
//
//    if(this->numberOfLayers == 1) {
//
//        cout << "input dimension of layer 1 (major-radius minor-radius height): ";
//        cin >> radius >> radius2 >> height;
//
//        cout << "input mesh sizes of layer 1 (major-sizeR, sizeZ):\n";
//        cin >> sizeR >> sizeZ;
//
//        dimOfLayer.insert(0, radius);
//        dimOfLayer.insert(1, height);
//        dimOfLayer.insert(2, radius2);
//
//        cellR = (unsigned)ROUNDED(2.0*PI*radius/sizeR, 0.0);
//        cellR = (cellR/16 + 1)*16;
//
//        cellZ = (unsigned)ROUNDED(height/sizeZ, 0.0);
//        sizeR = 2.0*PI/cellR;
//        sizeZ = height/(double)cellZ;
//
//        sizesOfLayer.insert(0, sizeR);
//        sizesOfLayer.insert(1, sizeZ);
//
//        cellsOfLayer.insert(0, cellR);
//        cellsOfLayer.insert(1, cellZ);
//
//    } else {
//
//        ArrDouble dim2 = this->dim.back();
//        ArrDouble size2 = this->cellSizes.back();
//        ArrUnsgn cell2 = this->cellNumbers.back();
//        cout << "input height of layer " << this->numberOfLayers << ":\n";
//        cin >> height;
//
//        cout << "input mesh size of height of layer " << this->numberOfLayers << ":\n";
//        cin >> sizeZ;
//
//        dimOfLayer.insert(0, dim2[0]);
//        dimOfLayer.insert(1, height);
//        dimOfLayer.insert(2, dim2[1]);
//
//        cellZ = (unsigned)ROUNDED(height/sizeZ, 0.0);
//        sizeZ = height/(double)cellZ;
//
//        sizesOfLayer.insert(0, size2[0]);
//        sizesOfLayer.insert(1, sizeZ);
//
//        cellsOfLayer.insert(0, cell2[0]);
//        cellsOfLayer.insert(1, cellZ);
//    }
//
//    this->dim.push_back(dimOfLayer);
//    this->cellSizes.push_back(sizesOfLayer);
//    this->cellNumbers.push_back(cellsOfLayer);
//}


void Shape::addOVAL(ArrDouble& sDim, ArrDouble& sSize, ArrDouble& sRatio) {

    unsigned cellR, cellZ;
    ArrUnsgn sCell(2);

    if(this->numberOfLayers == 1) {

        cellR = (unsigned)ROUNDED(2.0*PI*sDim[0]/sSize[0], 0.0);
        cellR = (cellR/16 + 1)*16;

        cellZ = (unsigned)ROUNDED(sDim[1]/sSize[1], 0.0);

        sSize.insert(0, 2.0*PI/(double)cellR) ;

        if(sRatio[1] == 1.0) {

            sSize.insert(1, sDim[1]/(double)cellZ) ;

        } else {

            sSize.insert(1, sDim[1]/2.0*(1.0 - sRatio[1])/(1.0 - pow(sRatio[1], cellZ/2)));

        }

        sCell.insert(0, cellR);
        sCell.insert(1, cellZ);

    } else {

        ArrDouble dim2(this->dim.back()),
                  size2(this->cellSizes.back()),
                  rat2(this->cellToCellRatio.back());
        ArrUnsgn cell2(this->cellNumbers.back());

        sDim.insert(0, dim2[0]);
        sDim.insert(2, dim2[2]);

        sSize.insert(0, size2[0]);

        sCell.insert(0, cell2[0]);

        sRatio.insert(0, rat2[0]);

        cellZ = (unsigned)ROUNDED(sDim[1]/sSize[1], 0.0);

        if(sRatio[1] == 1.0) {

            sSize.insert(1, sDim[1]/(double)cellZ) ;

        } else {

            sSize.insert(1, sDim[1]/2.0*(1.0 - sRatio[1])/(1.0 - pow(sRatio[1], cellZ/2)));

        }

        sCell.insert(1, cellZ);
    }

    this->dim.push_back(sDim);
    this->cellSizes.push_back(sSize);
    this->cellNumbers.push_back(sCell);
    this->cellToCellRatio.push_back(sRatio);
}
