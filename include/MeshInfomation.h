#ifndef MESHINFOMATION_H
#define MESHINFOMATION_H

#include <iostream>
#include <math.h>

#include "Shape.h"
#include "../common/ShapeType.h"
#include "../define/define.h"

using namespace std;

class MeshInfomation {
    public:
        MeshInfomation();
        MeshInfomation(const MeshInfomation&);

        virtual ~MeshInfomation();

        MeshInfomation& operator=(const MeshInfomation&);
        bool operator==(const MeshInfomation&);
        ostream& print(ostream&);
        void clear();

        unsigned numberOfPoints;
        unsigned numberOfCells;
        unsigned numberOfFaces;
        unsigned numberOfInternalFaces;
        unsigned numberOfBoundaries;
        containerIDs numberOfCellsOfLayer;
    protected:
        friend ostream& operator<<(ostream& out, MeshInfomation info){
            return info.print(out);
        }
    private:

};

#endif // MESHINFOMATION_H
