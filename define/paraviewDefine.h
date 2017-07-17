#ifndef PARAVIEWDEFINE_H_INCLUDED
#define PARAVIEWDEFINE_H_INCLUDED

#include <cstdlib>
#include <string>
using namespace std;
// XML paraview file
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#define VTKSTR         "VTKFile"
#define PIECESTR       "Piece"
#define POINTSTR       "Points"
#define POINTDATA   "PointData"
#define CELLSTR        "Cells"
#define CELLDATA    "CellData"
#define DATA_ARRAY  "DataArray"
#define LITTLE_END  "LittleEndian"
#define BIG_END     "BigEndian"
#define VTU_TYPE    "UnstructuredGrid"
#define FLOAT32     "Float32"
#define INT32       "Int32"
#define UINT8       "UInt8"
#define ASCII       "ascii"
#define SCALARSTR      "scalars"
#define CONNECT     "connectivity"
#define OFSETSTR       "offsets"
#define CELLTYPE    "types"

// legacy paraview file




#endif // PARAVIEWDEFINE_H_INCLUDED
