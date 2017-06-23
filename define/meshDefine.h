#ifndef MESHDEFINE_H_INCLUDED
#define MESHDEFINE_H_INCLUDED

#include "../include/MeshInfomation.h"
#include "../include/Mesh.h"

#define DIM(i) meshInfo.meshShape.getDimension(i)
#define NODE(i) meshInfo.meshNode[i]
#define SIZE(i) meshInfo.meshSize[i]
#endif // MESHDEFINE_H_INCLUDED
