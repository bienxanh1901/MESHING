#include "../include/Mesh.h"

void Mesh::cubicGeneration(){

    cubicNode();
    if(this->meshInfo.meshShape.getShape()==TRAPEZE) trapezeNode();
//    cubicFace();
    cubicInternalElement();
    cubicBoundariesLeftRight();
    cubicBoundariesFrontRear();
    cubicBoundariesTopBot();
    cubicFindNeighbor();

}

void Mesh::cubicNode(){

    for(double stepZ = 0; stepZ <= DIM(3); stepZ+=SIZE(2)){

        for(double stepY = 0; stepY <= DIM(2); stepY+=SIZE(1)){

            for(double stepX = 0; stepX <= DIM(1); stepX+=SIZE(0)){

                this->nodes.push_back(Node(++this->numberOfNodes, stepX, stepY, stepZ));

            }
        }
    }
}

void Mesh::trapezeNode(){
    double dimRatioX = (DIM(1)-DIM(4))/2;
    double dimRatioY = (DIM(2)-DIM(5))/2;
    double meshDiffX = SIZE(0) - DIM(4)/(double)NODE(0);
    double meshDiffY = SIZE(1) - DIM(5)/(double)NODE(1);
    double transX, transY, signX, signY;

    for(unsigned k=0; k<=NODE(2); k++){
        for(unsigned j=0; j<=NODE(1); j++){
            signY = (double)(sgn((int)(NODE(1)/2)-j));

            if(j<NODE(1)/2)
                 transY =signY*(double)k/(double)(NODE(2))*(dimRatioY-(double)j*meshDiffY);
            else transY =signY*(double)k/(double)(NODE(2))*(dimRatioY-(double)(NODE(1)-j)*meshDiffY);

            for(unsigned i=0; i<=NODE(0); i++){
                signX = (double)(sgn((int)(NODE(0)/2)-i));

                if(i<NODE(0)/2)
                     transX =signX*(double)k/(double)(NODE(2))*(dimRatioX-(double)i*meshDiffX);
                else transX =signX*(double)k/(double)(NODE(2))*(dimRatioX-(double)(NODE(0)-i)*meshDiffX);

                this->nodes.back().translate(transX, transY, 0.0);
            }
        }
    }
}


//void Mesh::cubicFace(){
//    unsigned layerNodes = (NODE(1)+1)*(NODE(0)+1);
//    unsigned lengthNodes = NODE(0)+1;
//    containerNodes node;
//    Element face;
//    for(unsigned i=0; i<=NODE(0); i++){
//        for(unsigned k=1; k<=NODE(2); k++){
//            for(unsigned j=1; j<=NODE(1); j++){
//                node.push_back(nodes[(k-1)*layerNodes + (j-1)*lengthNodes + i]);
//                node.push_back(nodes[(k-1)*layerNodes +  j*lengthNodes+ i]);
//                node.push_back(nodes[ k*layerNodes +  j*lengthNodes+ i]);
//                node.push_back(nodes[ k*layerNodes + (j-1)*lengthNodes+ i]);
//                face = Element(node, QUAD4, ++numberOfFaces);
//                face.geometryProperties();
//                faces.push_back(face);
//                node.clear();
//            }
//        }
//    }
//
//    for(unsigned j=0; j<=NODE(1); j++){
//        for(unsigned k=1; k<=NODE(2); k++){
//            for(unsigned i=1; i<=NODE(0); i++){
//                node.push_back(nodes[(k-1)*layerNodes + j*lengthNodes + i-1]);
//                node.push_back(nodes[(k-1)*layerNodes + j*lengthNodes+ i]);
//                node.push_back(nodes[ k*layerNodes + j*lengthNodes+ i]);
//                node.push_back(nodes[ k*layerNodes + j*lengthNodes+ i-1]);
//                face = Element(node, QUAD4, ++numberOfFaces);
//                face.geometryProperties();
//                faces.push_back(face);
//                node.clear();
//            }
//        }
//    }
//
//    for(unsigned k=0; k<=NODE(2); k++){
//        for(unsigned j=1; j<=NODE(1); j++){
//            for(unsigned i=1; i<=NODE(0); i++){
//                node.push_back(nodes[ k*layerNodes + (j-1)*lengthNodes + i-1]);
//                node.push_back(nodes[ k*layerNodes + (j-1)*lengthNodes + i]);
//                node.push_back(nodes[ k*layerNodes +  j*lengthNodes+ i]);
//                node.push_back(nodes[ k*layerNodes +  j*lengthNodes+ i-1]);
//                face = Element(node, QUAD4, ++numberOfFaces);
//                face.geometryProperties();
//                faces.push_back(face);
//                node.clear();
//            }
//        }
//    }
//}

void Mesh::cubicInternalElement(){
    unsigned layerNodes = (NODE(1)+1)*(NODE(0)+1);
    unsigned lengthNodes = NODE(0)+1;
    containerNodes node;

    for(unsigned k = 1; k <= NODE(2); k++){

        for(unsigned j = 1; j <= NODE(1); j++){

            for(unsigned i = 1; i <= NODE(0); i++){

                node.push_back(this->nodes[(k-1)*layerNodes + (j-1)*lengthNodes + i-1]);
                node.push_back(this->nodes[(k-1)*layerNodes + (j-1)*lengthNodes + i]);
                node.push_back(this->nodes[(k-1)*layerNodes +  j*lengthNodes + i]);
                node.push_back(this->nodes[(k-1)*layerNodes +  j*lengthNodes + i-1]);
                node.push_back(this->nodes[ k*layerNodes + (j-1)*lengthNodes + i-1]);
                node.push_back(this->nodes[ k*layerNodes + (j-1)*lengthNodes + i]);
                node.push_back(this->nodes[ k*layerNodes +  j*lengthNodes + i]);
                node.push_back(this->nodes[ k*layerNodes +  j*lengthNodes + i-1]);

                this->elements.push_back(Element(node, HEX8, ++this->numberOfElems));
                node.clear();

            }
        }
    }
}


void Mesh::cubicBoundariesLeftRight(){
    unsigned lengthNodes = NODE(0) + 1;
    unsigned widthNodes = NODE(1) + 1;
    unsigned layerNodes = lengthNodes*widthNodes;
    unsigned j1, j2, k1, k2;
    containerNodes nodeLeft, nodeRight;
    containerElements faceLeft, faceRight;

    for(unsigned k = 1; k <= NODE(2); k++){

        k1 = (k - 1)*layerNodes;
        k2 = k*layerNodes;

        for(unsigned j = 1; j <= NODE(1); j++){

            j1 = (j - 1)*lengthNodes;
            j2 = j*lengthNodes;

            nodeLeft.push_back(this->nodes[k1 + j1]);
            nodeLeft.push_back(this->nodes[k2 + j1]);
            nodeLeft.push_back(this->nodes[k2 + j2]);
            nodeLeft.push_back(this->nodes[k1 + j2]);
            faceLeft.push_back(Element(nodeLeft, QUAD4, 0));

            nodeRight.push_back(this->nodes[k1 + j1 + lengthNodes-1]);
            nodeRight.push_back(this->nodes[k1 + j2 + lengthNodes-1]);
            nodeRight.push_back(this->nodes[k2 + j2 + lengthNodes-1]);
            nodeRight.push_back(this->nodes[k2 + j1 + lengthNodes-1]);
            faceRight.push_back(Element(nodeRight, QUAD4, 0));

            nodeLeft.clear();
            nodeRight.clear();
        }
    }

    this->boundaries.push_back(faceLeft);
    this->boundaries.push_back(faceRight);
    faceLeft.clear();
    faceRight.clear();
}

void Mesh::cubicBoundariesFrontRear(){
    unsigned lengthNodes = NODE(0) + 1;
    unsigned widthNodes = NODE(1) + 1;
    unsigned layerNodes = lengthNodes*widthNodes;
    unsigned j, k1, k2;
    containerNodes nodeFront, nodeRear;
    containerElements faceFront, faceRear;

    j = NODE(1)*lengthNodes;

    for(unsigned k = 1; k <= NODE(2); k++){

        k1 = (k - 1)*layerNodes ;
        k2 = k*layerNodes;

        for(unsigned i = 1; i <= NODE(0); i++){

            nodeFront.push_back(this->nodes[k1 + i - 1]);
            nodeFront.push_back(this->nodes[k1 + i]);
            nodeFront.push_back(this->nodes[k2 + i]);
            nodeFront.push_back(this->nodes[k2 + i - 1]);
            faceFront.push_back(Element(nodeFront, QUAD4, 0));

            nodeRear.push_back(this->nodes[k1 + j + i - 1]);
            nodeRear.push_back(this->nodes[k2 + j + i - 1]);
            nodeRear.push_back(this->nodes[k2 + j + i]);
            nodeRear.push_back(this->nodes[k1 + j + i]);
            faceRear.push_back(Element(nodeRear, QUAD4, 0));

            nodeFront.clear();
            nodeRear.clear();
        }
    }

    this->boundaries.push_back(faceFront);
    this->boundaries.push_back(faceRear);
    faceFront.clear();
    faceRear.clear();
}

void Mesh::cubicBoundariesTopBot(){
    unsigned lengthNodes = NODE(0) + 1;
    unsigned widthNodes = NODE(1) + 1;
    unsigned layerNodes = lengthNodes*widthNodes;
    unsigned  k = layerNodes*NODE(2);
    unsigned j1, j2;
    containerNodes nodeBot, nodeTop;
    containerElements faceBot, faceTop;

    for(unsigned j = 1; j <= NODE(1); j++){

        j1 = (j - 1)*lengthNodes;
        j2 = j*lengthNodes;

        for(unsigned i = 1; i <= NODE(0); i++){

            nodeBot.push_back(this->nodes[j1 + i - 1]);
            nodeBot.push_back(this->nodes[j2 + i - 1]);
            nodeBot.push_back(this->nodes[j2 + i]);
            nodeBot.push_back(this->nodes[j1 + i]);
            faceBot.push_back(Element(nodeBot, QUAD4, 0));

            nodeTop.push_back(this->nodes[k + j1 + i - 1]);
            nodeTop.push_back(this->nodes[k + j1 + i]);
            nodeTop.push_back(this->nodes[k + j2 + i]);
            nodeTop.push_back(this->nodes[k + j2 + i - 1]);
            faceTop.push_back(Element(nodeTop, QUAD4, 0));

            nodeBot.clear();
            nodeTop.clear();
        }
    }

    this->boundaries.push_back(faceBot);
    this->boundaries.push_back(faceTop);
    faceBot.clear();
    faceTop.clear();
}

void Mesh::cubicFindNeighbor(){
    unsigned lengthElement = NODE(0);
    unsigned layerElement = NODE(0)*NODE(1);
    containerIDs elem;
    for(unsigned k = 0; k < NODE(2); k++){

        for(unsigned j = 0; j < NODE(1); j++){

            for(unsigned i = 0; i < NODE(0); i++){

                if(i > 0) elem.push_back(k*layerElement + j*lengthElement + i);
                if(i < NODE(0)-1) elem.push_back(k*layerElement + j*lengthElement + i + 2);

                if(j > 0) elem.push_back(k*layerElement + (j-1)*lengthElement + i+1);
                if(j < NODE(1)-1) elem.push_back(k*layerElement + (j+1)*lengthElement + i+1);

                if(k > 0) elem.push_back((k-1)*layerElement + j*lengthElement + i+1);
                if(k < NODE(2)-1) elem.push_back((k+1)*layerElement + j*lengthElement + i+1);

                this->neighbor.push_back(elem);
                elem.clear();

            }
        }
    }
}
