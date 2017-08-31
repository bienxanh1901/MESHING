#ifndef CELL_H
#define CELL_H

#include<vector>
#include "Element.h"
#include "Face.h"

using namespace std;


class Cell : public Element {
    public:
        Cell();
        virtual ~Cell();
        Cell(const Cell& p) : Element(p) { this->volume = p.volume;}
        Cell(const ContainerPrtPoints&, elemType, unsigned );
        Cell& operator=(const Cell&);

        double getVolume() { return this->volume;}
        ostream& printCellProperties(ostream&);

    protected:

    private:
        typedef vector<Face> ContainerFaces;
        double volume;
        void geometryProperties();
        void hexahedralProperties();
        void tetrahedralProperties();
        void calcVolumeCentroid(ContainerFaces& faces);
        ContainerPrtPoints findFace(unsigned, unsigned, unsigned, unsigned = 0);
};

#endif // CELL_H
