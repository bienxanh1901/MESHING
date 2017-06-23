#include "../include/Element.h"

Element::Element(){

    this->ID = 0;
    this->numberOfNodes = 0;
    this->numberOfFaces = 0;
    this->elementType = INVALID_ELEM;
    this->area = 0;
    this->volume = 0;

}

Element::~Element(){

    this->nodes.clear();
    this->faces.clear();
    this->neighbors.clear();
}

Element::Element(const Element& other){

    this->ID = other.ID;
    this->numberOfFaces = other.numberOfFaces;
    this->numberOfNodes = other.numberOfNodes;
    this->elementType = other.elementType;
    this->area = other.area;
    this->volume = other.volume;
    this->center = other.center;
    this->centroid = other.centroid;
    this->norm = other.norm;
    this->nodes = other.nodes;
    this->faces = other.faces;
    this->neighbors = other.neighbors;
}

Element::Element(Node * nodeArr, elemType type, unsigned nNodes, unsigned elemID){
    this->elementType = type;
    this->ID = elemID;
    this->numberOfNodes = nNodes;
    for(unsigned i=0; i<nNodes; i++)
    {
        (this->nodes).push_back(*(nodeArr+i));
    }
    geometryProperties();
}

Element::Element(const containerNodes& node, elemType type, unsigned elemID){
    this->elementType = type;
    this->ID = elemID;
    this->numberOfNodes = node.size();
    this->nodes = node;
    geometryProperties();
}

Element& Element::operator=(const Element& other){
    this->ID = other.ID;
    this->numberOfFaces = other.numberOfFaces;
    this->numberOfNodes = other.numberOfNodes;
    this->elementType = other.elementType;
    this->area = other.area;
    this->volume = other.volume;
    this->center = other.center;
    this->centroid = other.centroid;
    this->norm = other.norm;
    this->nodes = other.nodes;
    this->faces = other.faces;
    this->neighbors = other.neighbors;
    return *this;
}

void Element::clear(){
    this->ID = 0;
    this->numberOfNodes = 0;
    this->numberOfFaces = 0;
    this->elementType = INVALID_ELEM;
    this->area = 0;
    this->volume = 0;
    this->nodes.clear();
    this->faces.clear();
}

void Element::setID(unsigned ID){
    this->ID = ID;
}

unsigned Element::getID(){
    return this->ID;
}

Node& Element::getNode(unsigned ith){
    return this->nodes[ith-1];
}

Element& Element::getFace(unsigned ith){
    return this->faces[ith-1];
}

elemType Element::getType(){
    return this->elementType;
}

Point Element::getCenter(){
    return this->center;
}

Point Element::getCentroid(){
    return this->centroid;
}

double Element::getVolume(){
    return this->volume;
}

double Element::getArea(){
    return this->area;
}

typeVector<double> Element::getNormalVector(){
    return this->norm;
}

void Element::addNeighbor(unsigned elemID){
    this->neighbors.push_back(elemID);
}

vector<unsigned> Element::getNeighbor(){
    return this->neighbors;


}

bool Element::operator ==(Element elem){
    if(this->elementType != elem.elementType) return false;
    unsigned cnt = 0;
    for(containerNodes::iterator it = nodes.begin(); it != nodes.end(); it++){
        for(containerNodes::iterator it2 = nodes.begin(); it2 != nodes.end(); it2++){
            if(*it == *it2) cnt++;
        }
    }
    if(cnt == this->numberOfNodes) return true;
    return false;
}

ostream& Element::print(ostream& out){
    for(containerNodes::iterator i=this->nodes.begin(); i!=this->nodes.end(); i++)
    {
        out << i->getID() << " ";
    }
    return out;
}

ostream& Element::printFace(ostream& out){
    for(containerElements::iterator i = faces.begin(); i != faces.end(); i++)
    {
        out << *i << TAB;
        Point centroid;
        typeVector<double> normal;
        centroid = i->getCentroid();
        normal = i->getNormalVector();
        out << i->getArea() << TAB << centroid << TAB << normal;
        out << ENTER;
    }
    return out;
}

ostream& Element::printNode(ostream& out){
    for(vector<Node>::iterator i = nodes.begin(); i != nodes.end(); i++)
    {
        out << i->getID() - 1 << TAB;
    }
    return out;
}
