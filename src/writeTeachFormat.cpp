#include "../include/Mesh.h"

void Mesh::writeTEACHMesh()
{
    writeTEACHPoint();
//    writeTEACHElement();
    writeTEACHCell();
    writeTEACHFaceOfCell();
    writeTEACHBoundary();
    writeTEACHNeighbor();
}

void Mesh::writeTEACHPoint()
{
    ofstream _out;


    _out.open("Node.teach", std::ofstream::out);
    if(_out.is_open())
    {
        //Points
        _out << "Point data" << TAB << this->numberOfNodes << ENTER;
        for(containerNodes::iterator i = this->nodes.begin(); i != this->nodes.end(); i++)
        {
            _out << *(i) << ENTER;
        }
        _out.close();
    }
}

//void Mesh::writeTEACHElement()
//{
//    ofstream _out;
//
//    Point centroid;
//    typeVector<double> normal;
//    _out.open("Face.teach", std::ofstream::out);
//    if(_out.is_open())
//    {
//        //Elements
//        _out << "Face data" << TAB << numberOfFaces << ENTER;
//        for(containerElements::iterator i = faces.begin(); i!=faces.end(); i++)
//        {
//            centroid = i->getCentroid();
//            normal = i->getNormalVector();
//            _out << *(i) << TAB;
//            _out << centroid << TAB;
//            _out << (i->getArea()) << TAB;
//            _out << normal << ENTER;
//        }
//         _out.close();
//    }
//}


void Mesh::writeTEACHCell()
{
    ofstream _out;
    _out.open("Element.teach", std::ofstream::out);
    if(_out.is_open())
    {
        Point centroid;
        //Cells
        _out << "Cell data" << TAB << this->numberOfElems << ENTER;
        for(containerElements::iterator i = this->elements.begin(); i != this->elements.end(); i++)
        {
            centroid = i->getCentroid();
            _out << *(i) << TAB;
            _out << centroid << TAB;
            _out << (i->getVolume()) << ENTER;
        }
        _out.close();
    }
}

void Mesh::writeTEACHFaceOfCell()
{
    ofstream _out;

    Point centroid;
    typeVector<double> normal;
    _out.open("FaceOfCell.teach", std::ofstream::out);
    if(_out.is_open())
    {
        //Elements
        _out << "Face data" << ENTER;
        for(containerElements::iterator i = this->elements.begin(); i != this->elements.end(); i++)
        {
            i->printFace(_out);

        }
         _out.close();
    }
}

void Mesh::writeTEACHBoundary()
{
    ofstream _out;
    _out.open("boundary.teach", std::ofstream::out);
    if(_out.is_open())
    {
        Point centroid;
        typeVector<double> normal;
        //boundary
        _out << "Boundary data" << TAB << this->numberOfBoundaries << ENTER;
        for(vector<containerElements>::iterator i = this->boundaries.begin(); i != this->boundaries.end(); i++)
        {
            _out << i->size() << TAB;
        }
        _out << ENTER;

        for(vector<containerElements>::iterator i = this->boundaries.begin(); i != this->boundaries.end(); i++)
        {
            for(containerElements::iterator j = i->begin(); j!=i->end(); j++)
            {
                centroid = j->getCentroid();
                normal = j->getNormalVector();
                _out << *j << TAB << j->getArea() << TAB << centroid << TAB << normal;
                _out << ENTER;
            }

        }
        _out.close();
    }
}

void Mesh::writeTEACHNeighbor()
{
    ofstream _out;
    _out.open("neighbor.teach", std::ofstream::out);
    if(_out.is_open())
    {
        for(vector<containerIDs>::iterator i = this->neighbor.begin(); i != this->neighbor.end(); i++)
        {
            _out << i->size() << ENTER;
            for(containerIDs::iterator j = i->begin(); j!=i->end(); j++)
            {
                _out << *j << TAB;
            }
            _out << ENTER;
        }

        _out.close();
    }
}

