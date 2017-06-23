#include "../include/Mesh.h"
void Mesh::writeVTUformat()
{
    ofstream _out;
    _out.open("MeshGeneration.vtu", std::ofstream::out);
    if(_out.is_open())
    {
        _out << vtkFunc::VTK_TAG(VTU_TYPE,LITTLE_END) << ENTER;

        _out << vtkFunc::HEADER(1) << vtkFunc::TAG(VTU_TYPE) << ENTER;

        _out << vtkFunc::HEADER(2) << vtkFunc::PIECE_TAG(this->nodes.size() , this->elements.size() ) << ENTER;

        //Points
        _out << vtkFunc::HEADER(3) << vtkFunc::TAG(POINT) << ENTER;
        _out << vtkFunc::HEADER(4) << vtkFunc::ARRAY_TAG(FLOAT32, "", 3, ASCII);
        for(containerNodes::iterator i = this->nodes.begin(); i != this->nodes.end(); i++)
        {
            _out << *(i);
        }
        _out << vtkFunc::ENDTAG(DATA_ARRAY) << ENTER;
        _out << vtkFunc::HEADER(3) << vtkFunc::ENDTAG(POINT) << ENTER;

        //Cells
        _out << vtkFunc::HEADER(3) << vtkFunc::TAG(CELL) << ENTER;
        _out << vtkFunc::HEADER(4) << vtkFunc::ARRAY_TAG(INT32, CONNECT, 0, ASCII);
        for(containerElements::iterator i = this->elements.begin(); i != this->elements.end(); i++)
        {
            //_out << *(i);
            i->printNode(_out);
        }
        _out << vtkFunc::ENDTAG(DATA_ARRAY) << ENTER;

        //Ofset
        _out << vtkFunc::HEADER(4) << vtkFunc::ARRAY_TAG(INT32, OFSET, 0, ASCII);
        for(int i = 1; i<= (int)elements.size(); i++)
        {
            _out << i*8 << " ";
        }
        _out << vtkFunc::ENDTAG(DATA_ARRAY) << ENTER;

        //cell type
        _out << vtkFunc::HEADER(4) << vtkFunc::ARRAY_TAG(UINT8, CELLTYPE, 0, ASCII);
        for(int i = 1; i<= (int)elements.size(); i++)
        {
            _out << 12 << " ";
        }
        _out << vtkFunc::ENDTAG(DATA_ARRAY) << ENTER;

        _out << vtkFunc::HEADER(3)<< vtkFunc::ENDTAG(CELL) << ENTER;

        _out << vtkFunc::HEADER(2) << vtkFunc::ENDTAG(PIECE) << ENTER;

        _out << vtkFunc::HEADER(1) << vtkFunc::ENDTAG(VTU_TYPE) << ENTER;

        _out << vtkFunc::ENDTAG(VTK) << ENTER;

        _out.close();
    }
}
