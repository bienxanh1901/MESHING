#include <iostream>
#include "./include/Shape.h"
#include "./include/MeshInfomation.h"
#include "./include/Mesh.h"
#include "./common/ShapeType.h"
using namespace std;

int main()
{
    cout << "Hello world!" << "\n";
    Shape shape(CYLINDER);
    shape.addLayer();
    shape.addLayer();
    shape.addLayer();
    Mesh mesh(shape);
    mesh.meshGeneration();
    mesh.writeVTUformat();
    mesh.writeTEACHMesh();
    cout << "bye bye World!" << "\n";
    return 0;
}
