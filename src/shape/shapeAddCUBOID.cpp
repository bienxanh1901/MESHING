#include "../../include/Shape.h"

//void Shape::addCUBOID() {
//
//    double length, width, height;
//    double sizeX, sizeY, sizeZ;
//    unsigned cellX, cellY, cellZ;
//    ArrDouble dimOfLayer(this->numberOfDims);
//    ArrDouble sizesOfLayer(this->numberOfDims);
//    ArrUnsgn  cellsOfLayer(this->numberOfDims);
//
//    if(this->numberOfLayers == 1) {
//
//        cout << "input dimension of layer 1 (length, width, height):\n";
//        cin >> length >> width >> height;
//
//        cout << "input mesh sizes of layer 1 (sizeX, sizeY, sizeZ):\n";
//        cin >> sizeX >> sizeY >> sizeZ;
//
//        dimOfLayer.insert(0, length);
//        dimOfLayer.insert(1, width);
//        dimOfLayer.insert(2, height);
//
//        cellX = (unsigned)ROUNDED(length/sizeX, 0.0);
//        cellY = (unsigned)ROUNDED(width/sizeY, 0.0);
//        cellZ = (unsigned)ROUNDED(height/sizeZ, 0.0);
//        sizeX = length/(double)cellX;
//        sizeY = width/(double)cellY;
//        sizeZ = height/(double)cellZ;
//
//        sizesOfLayer.insert(0, sizeX);
//        sizesOfLayer.insert(1, sizeY);
//        sizesOfLayer.insert(2, sizeZ);
//
//        cellsOfLayer.insert(0, cellX);
//        cellsOfLayer.insert(1, cellY);
//        cellsOfLayer.insert(2, cellZ);
//
//    } else {
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
//        dimOfLayer.insert(1, dim2[1]);
//        dimOfLayer.insert(2, height);
//
//
//        cellZ = (unsigned)ROUNDED(height/sizeZ, 0.0);
//        sizeZ = height/(double)cellZ;
//
//        sizesOfLayer.insert(0, size2[0]);
//        sizesOfLayer.insert(1, size2[1]);
//        sizesOfLayer.insert(2, sizeZ);
//
//        cellsOfLayer.insert(0, cell2[0]);
//        cellsOfLayer.insert(1, cell2[1]);
//        cellsOfLayer.insert(2, cellZ);
//    }
//
//    this->dim.push_back(dimOfLayer);
//    this->cellSizes.push_back(sizesOfLayer);
//    this->cellNumbers.push_back(cellsOfLayer);
//}



void Shape::addCUBOID(ArrDouble& sDim, ArrDouble& sSize, ArrDouble& sRatio) {

    unsigned cellX, cellY, cellZ;
    ArrUnsgn sCell(this->numberOfDims);

    if(this->numberOfLayers == 1) {

        cellX = (unsigned)ROUNDED(sDim[0]/sSize[0], 0.0);
        cellY = (unsigned)ROUNDED(sDim[1]/sSize[1], 0.0);
        cellZ = (unsigned)ROUNDED(sDim[2]/sSize[2], 0.0);

        if(sRatio[0] == 1.0) {

            sSize.insert(0, sDim[0]/(double)cellX) ;

        } else {

            sSize.insert(0, sDim[0]/2.0*(1.0 - sRatio[0])/(1.0 - pow(sRatio[0], cellX/2)));

        }

        if(sRatio[1] == 1.0) {

            sSize.insert(1, sDim[1]/(double)cellY) ;

        } else {

            sSize.insert(1, sDim[1]/2.0*(1.0 - sRatio[1])/(1.0 - pow(sRatio[1], cellY/2)));

        }

        if(sRatio[2] == 1.0) {

            sSize.insert(2, sDim[2]/(double)cellZ) ;

        } else {

            sSize.insert(2, sDim[2]/2.0*(1.0 - sRatio[2])/(1.0 - pow(sRatio[2], cellZ/2)));

        }

        sCell.insert(0, cellX);
        sCell.insert(1, cellY);
        sCell.insert(2, cellZ);

    } else {

        ArrDouble dim2(this->dim.back()),
                  size2(this->cellSizes.back()),
                  rat2(this->cellToCellRatio.back());
        ArrUnsgn cell2(this->cellNumbers.back());

        sDim.insert(0, dim2[0]);
        sDim.insert(1, dim2[1]);

        sSize.insert(0, size2[0]);
        sSize.insert(1, size2[1]);

        sCell.insert(0, cell2[0]);
        sCell.insert(1, cell2[1]);

        sRatio.insert(0, rat2[0]);
        sRatio.insert(1, rat2[1]);


        cellZ = (unsigned)ROUNDED(sDim[2]/sSize[2], 0.0);

        if(sRatio[2] == 1.0) {

            sSize.insert(2, sDim[2]/(double)cellZ) ;

        } else {

            sSize.insert(2, sDim[2]/2.0*(1.0 - sRatio[2])/(1.0 - pow(sRatio[2], cellZ/2)));

        }

        sCell.insert(2, cellZ);
    }

    this->dim.push_back(sDim);
    this->cellSizes.push_back(sSize);
    this->cellNumbers.push_back(sCell);
    this->cellToCellRatio.push_back(sRatio);

}
