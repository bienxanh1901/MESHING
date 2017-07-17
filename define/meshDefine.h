#ifndef MESHDEFINE_H_INCLUDED
#define MESHDEFINE_H_INCLUDED

#include "../include/MeshInfomation.h"
#include "../include/Mesh.h"

#define DIM(layer) this->shape.getDimsOfLayer(layer)
#define CELL(layer) this->shape.getCellNumbersOfLayer(layer)
#define SIZE(layer) this->shape.getSizesOfLayer(layer)
#endif // MESHDEFINE_H_INCLUDED
