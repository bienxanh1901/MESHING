#include <iostream>
#include "./include/Shape.h"
#include "./include/MeshInfomation.h"
#include "./include/Mesh.h"
#include "./common/ShapeType.h"
using namespace std;

int main()
{
    cout << "Hello world!" << "\n";
    double dim[5];
    double meshsize[3];

//    for(int i=0; i<3; i++)
//    {
//        dim[i] = 1+(double)i;
//    }
//        dim[0]  = 0.8660254*2.0;//dim[1] = 0.1;
        dim[0]  = 0.15;dim[1] = 0.15;
        dim[2]  = 0.2;
        dim[3] = 0.05; dim[4] = 0.05;


//    for(int i=0; i<3; i++)
//    {
//       meshsize[i] = 0.1*(double)(i+1);
//    }
        meshsize[0] = 0.02;
        meshsize[1] = 0.03;
        meshsize[2] = 0.03;

//    Shape shape(RECTANGULAR,dim);
    Shape shape(TRAPEZE,dim);
//    Shape shape(CYLINDER,dim);
//      Shape shape(OVAL,dim);
      //Shape shape(SPHERIC,dim);

    MeshInfomation infomesh(shape, meshsize);
    Mesh mesh(infomesh);
    mesh.writeVTUformat();
    mesh.writeTEACHMesh();
    cout << "bye bye World!" << "\n";
    return 0;
}
