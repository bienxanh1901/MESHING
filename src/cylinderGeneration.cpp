#include "../include/Mesh.h"

void Mesh::cylinderGeneration() {

    cylinderPoints();
    cylinderElem();
    cylinderBoundariesBot();
    cylinderBoundariesTop();
    cylinderBoundariesAround();

}

void Mesh::cylinderPoints() {

    baseNode();
    extrudeNode();

}

void Mesh::baseNode(){

    outerCircleNode();
    innerRectangularNode();

}

void Mesh::outerCircleNode(){

    double angleSize = 2.0*PI/NODE(0);
    double radiusX = DIM(1)/2.0;
    double halfRadius = 0.5*radiusX;
    double p2 = halfRadius/sqrt(2.0);
    double cornerX = halfRadius - p2*(1.0 - tan(PI/6.0))/sqrt(2.0);

    double radiusY = DIM(3)/2.0;
    halfRadius = 0.5*radiusY;
    p2 = halfRadius/sqrt(2.0);
    double cornerY = halfRadius - p2*(1.0 - tan(PI/6.0))/sqrt(2.0);
    unsigned sideNodes = NODE(0)/8;
    double costheta, sintheta;
    double coordX, coordY;
    double sizeX, sizeY;

    for(double theta = -PI/4; theta < 7*PI/4; theta+= angleSize){

        costheta = cos(theta);
        sintheta = sin(theta);

        if(fabs(costheta) >= 1.0/sqrt(2.0)){

            sizeX = (radiusX - cornerX/fabs(costheta))/sideNodes;
            sizeY = (radiusY - cornerY/fabs(costheta))/sideNodes;

        }else{

            sizeX = (radiusX - cornerX/fabs(sintheta))/sideNodes;
            sizeY = (radiusY - cornerY/fabs(sintheta))/sideNodes;

        }

        for(unsigned i = 0; i < sideNodes; i++){

            coordX = (radiusX - (double)i*sizeX)*sintheta;
            coordY = (radiusY - (double)i*sizeY)*costheta;
            this->nodes.push_back(Node(++this->numberOfNodes, coordX, coordY));

        }
    }
}

void Mesh::innerRectangularNode(){

    double radius = DIM(1)/2.0;
    double halfRadius = 0.5*radius;
    double p2 = halfRadius/sqrt(2.0);
    double cornerX = halfRadius - p2*(1.0 - tan(PI/6.0))/sqrt(2.0);
    double sizeX = 2.0*cornerX/(NODE(0)/4);
    radius = DIM(3)/2.0;
    halfRadius = 0.5*radius;
    p2 = halfRadius/sqrt(2.0);
    double cornerY = halfRadius - p2*(1.0 - tan(PI/6.0))/sqrt(2.0);
    double sizeY = 2.0*cornerY/(NODE(0)/4);

    for(double coordY = cornerY; coordY >= -cornerY; coordY-= sizeY){

        for(double coordX = -cornerX; coordX <= cornerX; coordX+= sizeX){

            this->nodes.push_back(Node(++this->numberOfNodes, coordX, coordY, 0.0));

        }
    }
}

void Mesh::extrudeNode(){

    unsigned sideNodes = NODE(0)/8;
    unsigned edgeNodes = NODE(0)/4 + 1;
    unsigned baseNodes = NODE(0)*sideNodes + pow(edgeNodes,2);
    Point point;

    for(double coordZ = SIZE(1); coordZ <= DIM(2); coordZ+= SIZE(1)){

        for(unsigned i = 0; i < baseNodes; i++){

            point = this->nodes[i] + Point(0.0, 0.0, coordZ);
            this->nodes.push_back(Node(point, ++this->numberOfNodes));
        }
    }
}

void Mesh::cylinderElem(){

    baseElem();
    extrudeElem();

}

void Mesh::baseElem(){
    unsigned sideNodes = NODE(0)/8;
    unsigned edgeNodes = NODE(0)/4 + 1;
    unsigned outerNodes = NODE(0)*sideNodes;
    unsigned baseNodes = NODE(0)*sideNodes + pow(edgeNodes,2);
    unsigned j1, j2, i1, i2, tmp, tmp2, ID;
    containerNodes node;
    containerElements::iterator it;

    for(unsigned j = 0; j < NODE(0); j++){

        j1 = j*sideNodes;
        j2 = (j+1)*sideNodes;
        if(j == NODE(0) -1) j2 = 0;

        for(unsigned i = 1; i < sideNodes; i++){

            node.push_back(this->nodes[j1 + i - 1]);
            node.push_back(this->nodes[j1 + i]);
            node.push_back(this->nodes[j2 + i]);
            node.push_back(this->nodes[j2 + i - 1]);
            node.push_back(this->nodes[baseNodes + j1 + i - 1]);
            node.push_back(this->nodes[baseNodes + j1 + i]);
            node.push_back(this->nodes[baseNodes + j2 + i]);
            node.push_back(this->nodes[baseNodes + j2 + i - 1]);

            this->elements.push_back(Element(node, HEX8, ++this->numberOfElems));
            node.clear();

            if(j > 0){

                ID = this->numberOfElems - sideNodes;
                it = this->elements.begin() + this->numberOfElems - 1;
                it->addNeighbor(ID);
                it = this->elements.begin() + ID - 1;
                it->addNeighbor(this->numberOfElems);

            }

            if(i > 1){

                ID = this->numberOfElems - 1;
                it = this->elements.begin() + this->numberOfElems - 1;
                it->addNeighbor(ID);
                it = this->elements.begin() + ID - 1;
                it->addNeighbor(this->numberOfElems);

            }

            if(j == NODE(0) -1){

                ID = i;
                it = this->elements.begin() + this->numberOfElems - 1;
                it->addNeighbor(ID);
                it = this->elements.begin() + ID - 1;
                it->addNeighbor(this->numberOfElems);

            }

        }

        j1 = (j + 1)*sideNodes - 1;
        j2 = (j + 2)*sideNodes - 1;
        if(j == NODE(0) - 1) j2 = sideNodes - 1;
        tmp = j/(edgeNodes -1);
        tmp2 = j%(edgeNodes - 1);
        switch(tmp){

            case 0: i1 = outerNodes + j; i2 = i1 + 1; break;
            case 1: i1 = outerNodes + edgeNodes + tmp2*edgeNodes - 1; i2 = i1 + edgeNodes; break;
            case 2: i1 = outerNodes + edgeNodes*edgeNodes - tmp2 - 1; i2 = i1 - 1; break;
            case 3: i1 = outerNodes + (edgeNodes - tmp2 - 1)*edgeNodes; i2 = i1 - edgeNodes; break;
        }

        node.push_back(this->nodes[j1]);
        node.push_back(this->nodes[i1]);
        node.push_back(this->nodes[i2]);
        node.push_back(this->nodes[j2]);
        node.push_back(this->nodes[baseNodes + j1]);
        node.push_back(this->nodes[baseNodes + i1]);
        node.push_back(this->nodes[baseNodes + i2]);
        node.push_back(this->nodes[baseNodes + j2]);

        this->elements.push_back(Element(node, HEX8, ++this->numberOfElems));
        node.clear();

        ID = this->numberOfElems - 1;
        it = this->elements.begin() + this->numberOfElems - 1;
        it->addNeighbor(ID);
        it = this->elements.begin() + ID - 1;
        it->addNeighbor(this->numberOfElems);

        if(j > 0){

            ID = this->numberOfElems - sideNodes;
            it = this->elements.begin() + this->numberOfElems - 1;
            it->addNeighbor(ID);
            it = this->elements.begin() + ID - 1;
            it->addNeighbor(this->numberOfElems);

        }

        if(j == NODE(0) -1){

            ID = sideNodes;
            it = this->elements.begin() + this->numberOfElems - 1;
            it->addNeighbor(ID);
            it = this->elements.begin() + ID - 1;
            it->addNeighbor(this->numberOfElems);

        }
    }

    for(unsigned j = 1; j < edgeNodes; j++){

        j1 = outerNodes + (j-1)*edgeNodes;
        j2 = outerNodes + j*edgeNodes;

        for(unsigned i = 1; i < edgeNodes; i++){

            node.push_back(this->nodes[j1 + i - 1]);
            node.push_back(this->nodes[j1 + i]);
            node.push_back(this->nodes[j2 + i]);
            node.push_back(this->nodes[j2 + i - 1]);
            node.push_back(this->nodes[baseNodes + j1 + i - 1]);
            node.push_back(this->nodes[baseNodes + j1 + i]);
            node.push_back(this->nodes[baseNodes + j2 + i]);
            node.push_back(this->nodes[baseNodes + j2 + i - 1]);

            this->elements.push_back(Element(node, HEX8, ++this->numberOfElems));
            node.clear();

            if(i == 1){

                ID = outerNodes - (j - 1)*sideNodes;
                it = this->elements.begin() + this->numberOfElems - 1;
                it->addNeighbor(ID);
                it = this->elements.begin() + ID - 1;
                it->addNeighbor(this->numberOfElems);

            }else{

                ID = this->numberOfElems - 1;
                it = elements.begin() + this->numberOfElems - 1;
                it->addNeighbor(ID);
                it = this->elements.begin() + ID - 1;
                it->addNeighbor(this->numberOfElems);

                if(i == edgeNodes - 1){

                    ID = (i + j)*sideNodes;
                    it = this->elements.begin() + this->numberOfElems - 1;
                    it->addNeighbor(ID);
                    it = this->elements.begin() + ID - 1;
                    it->addNeighbor(this->numberOfElems);

                }
            }

            if(j == 1){

                ID = i*sideNodes;
                it = this->elements.begin() + this->numberOfElems - 1;
                it->addNeighbor(ID);
                it = this->elements.begin() + ID - 1;
                it->addNeighbor(this->numberOfElems);

            }else{

                ID = this->numberOfElems - edgeNodes + 1;
                it = this->elements.begin() + this->numberOfElems - 1;
                it->addNeighbor(ID);
                it = this->elements.begin() + ID - 1;
                it->addNeighbor(this->numberOfElems);

                if(j == edgeNodes - 1){

                    ID = (3*j - i + 1)*sideNodes;
                    it = this->elements.begin() + this->numberOfElems - 1;
                    it->addNeighbor(ID);
                    it = this->elements.begin() + ID - 1;
                    it->addNeighbor(this->numberOfElems);
                }
            }
        }
    }
}

void Mesh::extrudeElem(){
    unsigned sideNodes = NODE(0)/8;
    unsigned edgeNodes = NODE(0)/4 + 1;
    unsigned baseNodes = NODE(0)*sideNodes + pow(edgeNodes,2);
    unsigned baseElems = NODE(0)*sideNodes + pow(edgeNodes - 1,2);
    unsigned ID;
    Node nodetmp;
    containerNodes node;
    containerIDs elemNeighbor;

    for(unsigned k = 1; k < NODE(1); k++){
        for(unsigned j = 0; j< baseElems; j++){

            for(unsigned i = 1; i <= 8; i++){
                nodetmp = this->elements[j].getNode(i);
                ID = nodetmp.getID() + k*baseNodes - 1;
                node.push_back(this->nodes[ID]);
            }
            this->elements.push_back(Element(node, HEX8, ++this->numberOfElems));
            node.clear();
        }
    }

    for(unsigned k = 1; k < NODE(1); k++){
        for(unsigned j = 0; j< baseElems; j++){

            elemNeighbor = elements[j].getNeighbor();
//            for(containerIDs::iterator it = elemNeighbor.begin(); it != elemNeighbor.end(); it++){
//                ID = *it + k*baseElems;
//                elements[j + baseElems].addNeighbor(ID);
//                elements[ID - 1].addNeighbor(numberOfElems);
//            }
//
//            if(k == 1){
//                ID = j + 1;
//                elements[j + baseElems].addNeighbor(ID);
//                elements[ID - 1].addNeighbor(numberOfElems);
//            }
        }
    }
}

void Mesh::cylinderBoundariesBot(){
    unsigned sideNodes = NODE(0)/8;
    unsigned edgeNodes = NODE(0)/4 + 1;
    unsigned outerNodes = NODE(0)*sideNodes;
    unsigned j1, j2, i1, i2, tmp, tmp2;
    containerNodes node;
    containerElements face;

    for(unsigned j = 0; j < NODE(0); j++){
        j1 = j*sideNodes;
        j2 = (j+1)*sideNodes;
        if(j == NODE(0) -1) j2 = 0;
        for(unsigned i = 1; i < sideNodes; i++){
            node.push_back(this->nodes[j1 + i - 1]);
            node.push_back(this->nodes[j1 + i]);
            node.push_back(this->nodes[j2 + i]);
            node.push_back(this->nodes[j2 + i - 1]);
            face.push_back(Element(node, QUAD4, 0));
            node.clear();
        }
        j1 = (j + 1)*sideNodes - 1;
        j2 = (j + 2)*sideNodes - 1;
        if(j == NODE(0) - 1) j2 = sideNodes - 1;
        tmp = j/(edgeNodes -1);
        tmp2 = j%(edgeNodes - 1);
        switch(tmp){
            case 0: i1 = outerNodes + j; i2 = i1 + 1; break;
            case 1: i1 = outerNodes + edgeNodes + tmp2*edgeNodes - 1; i2 = i1 + edgeNodes; break;
            case 2: i1 = outerNodes + edgeNodes*edgeNodes - tmp2 - 1; i2 = i1 - 1; break;
            case 3: i1 = outerNodes + (edgeNodes - tmp2 - 1)*edgeNodes; i2 = i1 - edgeNodes; break;
        }
        node.push_back(this->nodes[j1]);
        node.push_back(this->nodes[i1]);
        node.push_back(this->nodes[i2]);
        node.push_back(this->nodes[j2]);
        face.push_back(Element(node, QUAD4, 0));
        node.clear();
    }

    for(unsigned j = 1; j < edgeNodes; j++){
        j1 = outerNodes + (j-1)*edgeNodes;
        j2 = outerNodes + j*edgeNodes;
        for(unsigned i = 1; i < edgeNodes; i++){
            node.push_back(this->nodes[j1 + i - 1]);
            node.push_back(this->nodes[j1 + i]);
            node.push_back(this->nodes[j2 + i]);
            node.push_back(this->nodes[j2 + i - 1]);
            face.push_back(Element(node, QUAD4, 0));
            node.clear();
        }
    }
    this->boundaries.push_back(face);
    face.clear();
}

void Mesh::cylinderBoundariesTop(){
    unsigned sideNodes = NODE(0)/8;
    unsigned edgeNodes = NODE(0)/4 + 1;
    unsigned baseNodes = NODE(0)*sideNodes + pow(edgeNodes,2);
    unsigned ID;
    containerNodes node;
    containerElements face1, face2;
    face1 = this->boundaries[0];
    for(containerElements::iterator j = face1.begin(); j != face1.end(); j++){
        for(unsigned i = 1; i <= 4; i++){
            ID = (j->getNode(i)).getID() + NODE(1)*baseNodes - 1;
            node.push_back(nodes[ID]);
        }
        face2.push_back(Element(node, QUAD4, 0));
        node.clear();
    }
    this->boundaries.push_back(face2);
    face1.clear();
    face2.clear();
}

void Mesh::cylinderBoundariesAround()
{
    unsigned sideNodes = NODE(0)/8;
    unsigned edgeNodes = NODE(0)/4 + 1;
    unsigned baseNodes = NODE(0)*sideNodes + pow(edgeNodes,2);
    unsigned j1, j2, k1, k2;
    containerNodes node;
    containerElements face;
    for(unsigned k = 1; k <= NODE(1); k++){
        k1 = (k-1)*baseNodes;
        k2 = k*baseNodes;
        for(unsigned j = 1; j <= NODE(0); j++){
            j1 = (j-1)*sideNodes;
            j2 = j*sideNodes;
            if(j == NODE(0))j2 = 0;
            node.push_back(this->nodes[k1 + j1]);
            node.push_back(this->nodes[k2 + j1]);
            node.push_back(this->nodes[k2 + j2 ]);
            node.push_back(this->nodes[k1 + j2]);
            face.push_back(Element(node, QUAD4, 0));
            node.clear();
        }
    }
    this->boundaries.push_back(face);
    face.clear();
}




