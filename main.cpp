#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>    // std::remove_if
#include <cstdlib> // std::strtol
#include <sstream>
#include <ctype.h> // isspace


#include "./include/Shape.h"
#include "./include/MeshInfomation.h"
#include "./include/Mesh.h"
#include "./common/ShapeType.h"

using namespace std;

bool readInputFile(string, Shape&);
bool readShape(string&, Shape&);
bool readLayer(istream&, Shape&);
string parse_label(string&);

int main(int argc, char* argv[])
{
    cout << "Hello world!" << "\n";

    if(argc != 2) {
        cout << "Wrong syntax!\n";
		cout << argv[0] << " [inputFile]\n";
		cout << "bye bye World!" << "\n";
		exit(1);
    }

    Shape shape;
    if(readInputFile(argv[1], shape)) {
        Mesh mesh(shape);
        mesh.meshGeneration();
        mesh.writeTEACHMesh();
        mesh.writeVTUformat();
    }
    cout << "bye bye World!" << "\n";
    return 0;
}



bool readInputFile(string fileName, Shape& shape) {

    ifstream _in;
    _in.open(fileName.c_str(), ios::in);

    if(_in.is_open()) {

        string line;
        // read lines from file
        while(_in.peek() != EOF) {

            getline(_in, line);
            if (line.find("SHAPECODE") == static_cast<string::size_type>(0)) {

                if(readShape(line, shape) == false) return false;
                continue;
            }

            if (line.find("LAYER") == static_cast<string::size_type>(0)) {

                if(readLayer(_in, shape) == false) return false;
                continue;
            }

        }

    } else {

        cout << "Can't open file " << fileName << "!!!\n";
        return false;

    }

    _in.close();
    if(shape.getShape() == INVALID__SHAPE) return false;
    if(shape.getNumberOfLayers() == 0) return false;
    return true;

}


bool readShape(string& line, Shape& shape ) {


    string s = parse_label(line);

    if(*s.c_str() < '0' || *s.c_str() > '4') {

        cout << "Errors: Invalid shape!!\n\n";
        return false;

    } else {

        stringstream ss;
        int sc;
        ss.str(s);
        ss >> sc;
        shape.setShape((ShapeType)sc);
        return true;
    }

}


bool readLayer(istream& _in, Shape& shape) {

    ShapeType type(shape.getShape());
    unsigned ndim, nsize, nrat;

    switch(type) {
        case CUBOID:
            ndim = 3;
            nsize = 3;
            nrat = 3;
            break;
        case TRAPEZIOD:
            ndim = 5;
            nsize = 3;
            nrat = 3;
            break;
        case CYLINDER:
            ndim = 2;
            nsize = 2;
            nrat = 2;
            break;
        case OVAL:
            ndim = 3;
            nsize = 2;
            nrat = 2;
            break;
        case SPHERIC:
            ndim = 1;
            nsize = 1;
            nrat = 1;
            break;
        default:
            return 0;

    }

    string line;
    unsigned n = 0;
    ArrDouble sDim(ndim), sSize(nsize), sRat(nrat);

    while(_in.peek() != EOF && _in.peek() != '*' && n <= 3) {
        n++;
        if(n == 1) _in >> sDim;
        else if(n == 2) _in >> sSize;
        else _in >> sRat;
        getline(_in, line);

    }

    shape.addLayer(sDim, sSize, sRat);
    return true;

}


string parse_label(string& line) {

    //remove space
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    size_t index = line.find("=") + 1;
    return string(line.begin() + index, line.end());
}
