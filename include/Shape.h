#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <assert.h>
#include "../define/define.h"
#include "../common/ShapeType.h"




using namespace std;

class Shape {
    public:
        Shape();
        Shape(ShapeType);
        virtual ~Shape();
        Shape(const Shape&);
        Shape& operator=(const Shape&);
        ShapeType getShape();
        unsigned getNumberOfDims();
        arrDouble getSizesOfLayer(unsigned);
        arrDouble getDimsOfLayer(unsigned);
        arrUnsgn getCellNumbersOfLayer(unsigned);
        void addLayer();
        void deleteLayer(unsigned);
    protected:
    private:
        ShapeType type;
        unsigned numberOfLayers;
        unsigned numberOfDims;
        vector<arrDouble> dim;
        vector<arrDouble> cellSizes;
        vector<arrUnsgn> cellNumbers;

        void setNumberOfDims();

        void addCUBOID();
        void addTRAPEZIOID();
        void addCYLINDER();
        void addOVAL();
        void addSPHERIC();

        void deleteCUBOID(unsigned);
        void deleteTRAPEZIOID(unsigned);
        void deleteCYLINDER(unsigned);
        void deleteOVAL(unsigned);
        void deleteSPHERIC(unsigned);
};

#endif // SHAPE_H
