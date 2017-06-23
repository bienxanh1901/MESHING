#ifndef PARAVIEWEXP_H_INCLUDED
#define PARAVIEWEXP_H_INCLUDED

#include <iostream>
#include <string>
#include <sstream>
#include "../define/paraviewDefine.h"
#include "../define/define.h"
using namespace std;


namespace vtkFunc
{
    // Declaration
    inline string HEADER(int level)
    {
        std::stringstream header;
        for(int i=0; i<level; i++)
        {
            header << TAB;
        }
        return header.str();
    }

    inline string TAG(string tagName)
    {
        std::stringstream tag;
        tag << "<" << tagName << ">";
        return tag.str();
    }

    inline string ENDTAG(string tagName)
    {
        std::stringstream endTag;
        endTag << "</" << tagName << ">";
        return endTag.str();
    }

    inline string VTK_TAG(string gridType, string byteOrder)
    {
        std::stringstream vtk;
        vtk << "<VTKFile type=\"" << gridType << "\" version=\"0.1\" byte_order=\"" << byteOrder << "\">";
        return vtk.str();
    }

    inline string PIECE_TAG(unsigned pointNumber, unsigned cellNumber)
    {
        std::stringstream piece;
        piece << "<Piece NumberOfPoints=\"" << pointNumber << "\" NumberOfCells=\"" << cellNumber << "\">";
        return piece.str();
    }

    inline string POINT_DATA_TAG(string type)
    {
        std::stringstream pointTag;
        pointTag << "<PointData Scalars=\"" << type << "\">";
        return pointTag.str();
    }

    inline string CELL_DATA_TAG(string type)
    {
        std::stringstream cellTag;
        cellTag << "<CellData Scalars=\"" << type << "\">";
        return cellTag.str();
    }

    inline string ARRAY_TAG(string dataType, string name, int component, string formatType)
    {
        std::stringstream arrTag;
        arrTag << "<DataArray type=\"" << dataType;
        if(name.compare("") != 0) arrTag << "\" Name=\"" << name;
        if(component>0) arrTag << "\" NumberOfComponents=\"" << component;
        arrTag << "\" format=\"" << formatType << "\">";
        return arrTag.str();
    }
}






#endif // PARAVIEWEXP_H_INCLUDED
