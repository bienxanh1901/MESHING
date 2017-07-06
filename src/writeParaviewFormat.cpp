#include "../include/Mesh.h"
void Mesh::writeVTUformat() {

    ofstream _out;
    _out.open("MeshGeneration.vtu", std::ofstream::out);

    if(_out.is_open()) {

        _out << vtkFunc::VTK_TAG(VTU_TYPE,LITTLE_END) << "\n";
        _out << vtkFunc::HEADER(1) << vtkFunc::TAG(VTU_TYPE) << "\n";
        _out << vtkFunc::HEADER(2) << vtkFunc::PIECE_TAG(this->numberOfPoints , this->numberOfCells ) << "\n";

        //Points
        _out << vtkFunc::HEADER(3) << vtkFunc::TAG(POINT) << "\n";
        _out << vtkFunc::HEADER(4) << vtkFunc::ARRAY_TAG(FLOAT32, "", 3, ASCII);

        for(containerPoints::iterator it = this->points.begin(); it != this->points.end(); it++) {
            _out << *(it);
        }

        _out << vtkFunc::ENDTAG(DATA_ARRAY) << "\n";
        _out << vtkFunc::HEADER(3) << vtkFunc::ENDTAG(POINT) << "\n";

        //Cells
        _out << vtkFunc::HEADER(3) << vtkFunc::TAG(CELL) << "\n";
        _out << vtkFunc::HEADER(4) << vtkFunc::ARRAY_TAG(INT32, CONNECT, 0, ASCII);

        for(containerCells::iterator it = this->cells.begin(); it != this->cells.end(); it++) {
            it->printPointsIDParaview(_out);
        }

        _out << vtkFunc::ENDTAG(DATA_ARRAY) << "\n";

        //Ofset
        _out << vtkFunc::HEADER(4) << vtkFunc::ARRAY_TAG(INT32, OFSET, 0, ASCII);

        for(unsigned i = 1; i<= this->numberOfCells; i++) {
            _out << i*8 << " ";
        }

        _out << vtkFunc::ENDTAG(DATA_ARRAY) << "\n";

        //cell type
        _out << vtkFunc::HEADER(4) << vtkFunc::ARRAY_TAG(UINT8, CELLTYPE, 0, ASCII);

        for(unsigned i = 1; i<= this->numberOfCells; i++) {
            _out << 12 << " ";
        }

        _out << vtkFunc::ENDTAG(DATA_ARRAY) << "\n";
        _out << vtkFunc::HEADER(3)<< vtkFunc::ENDTAG(CELL) << "\n";
        _out << vtkFunc::HEADER(2) << vtkFunc::ENDTAG(PIECE) << "\n";
        _out << vtkFunc::HEADER(1) << vtkFunc::ENDTAG(VTU_TYPE) << "\n";
        _out << vtkFunc::ENDTAG(VTK) << "\n";

        _out.close();
    }
}
