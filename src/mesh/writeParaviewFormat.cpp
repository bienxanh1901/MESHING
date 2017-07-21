#include "../../include/Mesh.h"


void Mesh::writeVTUformat() {

    ofstream _out;
    _out.open("MeshGeneration.vtu", std::ofstream::out);

    if(_out.is_open()) {

        _out << vtkFunc::VTK_TAG(VTU_TYPE,LITTLE_END) << "\n";
        _out << vtkFunc::HEADER(1) << vtkFunc::TAG(VTU_TYPE) << "\n";
        _out << vtkFunc::HEADER(2) << vtkFunc::PIECE_TAG(this->meshInfo.numberOfPoints, this->meshInfo.numberOfCells) << "\n";

        //Cell data:
        _out << vtkFunc::HEADER(3) << vtkFunc::CELL_DATA_TAG(SCALARSTR) << "\n";
        _out << vtkFunc::HEADER(4) << vtkFunc::ARRAY_TAG(FLOAT32, "layer", 0, ASCII);

        forAllIter(ContainerIDs,this->mark,it) {

            _out << *(it) << " ";

        }

        _out << vtkFunc::ENDTAG(DATA_ARRAY) << "\n";
        _out << vtkFunc::HEADER(3) << vtkFunc::ENDTAG(CELLDATA) << "\n";

        //Points
        _out << vtkFunc::HEADER(3) << vtkFunc::TAG(POINTSTR) << "\n";
        _out << vtkFunc::HEADER(4) << vtkFunc::ARRAY_TAG(FLOAT32, "", 3, ASCII);

        forAllIter(ContainerPoints,this->points,it) {

            _out << *(it);

        }

        _out << vtkFunc::ENDTAG(DATA_ARRAY) << "\n";
        _out << vtkFunc::HEADER(3) << vtkFunc::ENDTAG(POINTSTR) << "\n";

        //Cells
        _out << vtkFunc::HEADER(3) << vtkFunc::TAG(CELLSTR) << "\n";
        _out << vtkFunc::HEADER(4) << vtkFunc::ARRAY_TAG(INT32, CONNECT, 0, ASCII);

        forAllIter(ContainerCells,this->cells,it) {

            it->printPointsIDParaview(_out);

        }

        _out << vtkFunc::ENDTAG(DATA_ARRAY) << "\n";

        //Ofset
        _out << vtkFunc::HEADER(4) << vtkFunc::ARRAY_TAG(INT32, OFSETSTR, 0, ASCII);

        for(unsigned i = 1; i<= this->meshInfo.numberOfCells; i++) {
            _out << i*8 << " ";
        }

        _out << vtkFunc::ENDTAG(DATA_ARRAY) << "\n";

        //cell type
        _out << vtkFunc::HEADER(4) << vtkFunc::ARRAY_TAG(UINT8, CELLTYPE, 0, ASCII);

        for(unsigned i = 1; i<= this->meshInfo.numberOfCells; i++) {
            _out << 12 << " ";
        }

        _out << vtkFunc::ENDTAG(DATA_ARRAY) << "\n";
        _out << vtkFunc::HEADER(3)<< vtkFunc::ENDTAG(CELLSTR) << "\n";
        _out << vtkFunc::HEADER(2) << vtkFunc::ENDTAG(PIECESTR) << "\n";
        _out << vtkFunc::HEADER(1) << vtkFunc::ENDTAG(VTU_TYPE) << "\n";
        _out << vtkFunc::ENDTAG(VTKSTR) << "\n";

        _out.close();
    }
}



void Mesh::writeVTUtest() {

    ofstream _out;
    _out.open("test.vtu", std::ofstream::out);

    if(_out.is_open()) {

        _out << vtkFunc::VTK_TAG(VTU_TYPE,LITTLE_END) << "\n";
        _out << vtkFunc::HEADER(1) << vtkFunc::TAG(VTU_TYPE) << "\n";
        _out << vtkFunc::HEADER(2) << vtkFunc::PIECE_TAG(this->meshInfo.numberOfPoints, this->meshInfo.numberOfFaces) << "\n";


        //Points
        _out << vtkFunc::HEADER(3) << vtkFunc::TAG(POINTSTR) << "\n";
        _out << vtkFunc::HEADER(4) << vtkFunc::ARRAY_TAG(FLOAT32, "", 3, ASCII);

        forAllIter(ContainerPoints,this->points,it) {

            _out << *(it);

        }

        _out << vtkFunc::ENDTAG(DATA_ARRAY) << "\n";
        _out << vtkFunc::HEADER(3) << vtkFunc::ENDTAG(POINTSTR) << "\n";

        //Cells
        _out << vtkFunc::HEADER(3) << vtkFunc::TAG(CELLSTR) << "\n";
        _out << vtkFunc::HEADER(4) << vtkFunc::ARRAY_TAG(INT32, CONNECT, 0, ASCII);

        forAllIter(ContainerFaces, this->faces, it) {

            it->printPointsIDParaview(_out);

        }

        _out << vtkFunc::ENDTAG(DATA_ARRAY) << "\n";

        //Ofset
        _out << vtkFunc::HEADER(4) << vtkFunc::ARRAY_TAG(INT32, OFSETSTR, 0, ASCII);

        for(unsigned i = 1; i<= this->meshInfo.numberOfFaces; i++) {
            _out << i*4 << " ";
        }

        _out << vtkFunc::ENDTAG(DATA_ARRAY) << "\n";

        //cell type
        _out << vtkFunc::HEADER(4) << vtkFunc::ARRAY_TAG(UINT8, CELLTYPE, 0, ASCII);

        for(unsigned i = 1; i<= this->meshInfo.numberOfFaces; i++) {
            _out << 9 << " ";
        }

        _out << vtkFunc::ENDTAG(DATA_ARRAY) << "\n";
        _out << vtkFunc::HEADER(3)<< vtkFunc::ENDTAG(CELLSTR) << "\n";
        _out << vtkFunc::HEADER(2) << vtkFunc::ENDTAG(PIECESTR) << "\n";
        _out << vtkFunc::HEADER(1) << vtkFunc::ENDTAG(VTU_TYPE) << "\n";
        _out << vtkFunc::ENDTAG(VTKSTR) << "\n";

        _out.close();
    }
}
