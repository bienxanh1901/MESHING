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
        ShapeType getShape();
        void setShape(ShapeType);
        void addLayer();
        void deleteLayer(unsigned);
        void editLayer(unsigned);
        void clear();

        unsigned getNumberOfDims();
        unsigned getNumberOfLayers();
        arrDouble& getSizesOfLayer(unsigned);
        arrDouble& getDimsOfLayer(unsigned);
        arrUnsgn& getCellNumbersOfLayer(unsigned);

        ostream& print(ostream&);
    protected:
        friend ostream& operator <<(ostream& out, Shape& s) {
            return s.print(out);
        }
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

        void editCUBOID(unsigned);
        void editTRAPEZIOID(unsigned);
        void editCYLINDER(unsigned);
        void editOVAL(unsigned);
        void editSPHERIC(unsigned);

};

#endif // SHAPE_H
