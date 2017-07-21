#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <fstream>
#include <vector>
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

        void setShape(ShapeType);
        void addLayer(ArrDouble&, ArrDouble&, ArrDouble&);
        void deleteLayer(unsigned);
        void editLayer(unsigned, ArrDouble&, ArrDouble&, ArrDouble&);
        void clear();

        ShapeType getShape();
        unsigned getNumberOfDims();
        unsigned getNumberOfLayers();
        ArrDouble& getSizesOfLayer(unsigned);
        ArrDouble& getDimsOfLayer(unsigned);
        ArrDouble& getRatitoOfLayer(unsigned);
        ArrUnsgn& getCellNumbersOfLayer(unsigned);

        ostream& print(ostream&);
    protected:
        friend ostream& operator <<(ostream& out, Shape& s) {
            return s.print(out);
        }
    private:
        ShapeType type;
        unsigned numberOfLayers;
        unsigned numberOfDims;
        ContainerArrD dim;
        ContainerArrD cellSizes;
        ContainerArrU cellNumbers;
        ContainerArrD cellToCellRatio;

        void setNumberOfDims();

        void addCUBOID(ArrDouble&, ArrDouble&, ArrDouble&);
        void addTRAPEZIOID(ArrDouble&, ArrDouble&, ArrDouble&);
        void addCYLINDER(ArrDouble&, ArrDouble&, ArrDouble&);
        void addOVAL(ArrDouble&, ArrDouble&, ArrDouble&);
        void addSPHERIC(ArrDouble&, ArrDouble&, ArrDouble&);

        void deleteCUBOID(unsigned);
        void deleteTRAPEZIOID(unsigned);
        void deleteCYLINDER(unsigned);
        void deleteOVAL(unsigned);
        void deleteSPHERIC(unsigned);

        void editCUBOID(unsigned, ArrDouble&, ArrDouble&, ArrDouble&);
        void editTRAPEZIOID(unsigned, ArrDouble&, ArrDouble&, ArrDouble&);
        void editCYLINDER(unsigned, ArrDouble&, ArrDouble&, ArrDouble&);
        void editOVAL(unsigned, ArrDouble&, ArrDouble&, ArrDouble&);
        void editSPHERIC(unsigned, ArrDouble&, ArrDouble&, ArrDouble&);

};

#endif // SHAPE_H
