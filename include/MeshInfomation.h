#ifndef MESHINFOMATION_H
#define MESHINFOMATION_H

#include <iostream>
#include <math.h>

#include "Shape.h"
#include "../common/ShapeType.h"
#include "../define/define.h"

using namespace std;

class MeshInfomation
{
    public:
        MeshInfomation();
        virtual ~MeshInfomation();
        MeshInfomation(Shape&, double*);
        MeshInfomation(const MeshInfomation& other);
        MeshInfomation& operator=(const MeshInfomation& other);
        void calculateNodenumbers();

        Shape meshShape;
        double meshSize[3];
        unsigned meshNode[3];
    protected:
    private:

};

#endif // MESHINFOMATION_H
