#include "../include/Mesh.h"

void Mesh::sphericGeneration()
{
//    generateCubicMesh();
    generateSphereMesh();
}

void Mesh::generateCubicMesh()
{
    double radius = DIM(1)/2.0;
    double halfRadius = 0.5*radius;
    double p2 = halfRadius/sqrt(2.0);
    double corner = halfRadius-p2*(1.0-tan(PI/6.0))/sqrt(2.0);
    double sizeX = 2.0*corner/(NODE(0)/4);

    unsigned edgePoints = NODE(0)/4 + 1;
    unsigned layerPoints = pow(edgePoints,2);
    vector<Node> node;

    for(unsigned k = 0; k<edgePoints; k++)
    {
        for(unsigned j = 0; j<edgePoints; j++)
        {
            for(unsigned i = 0; i<edgePoints; i++)
            {
                nodes.push_back(Node(++this->numberOfNodes, -corner+(double)i*sizeX,
                                                             corner-(double)j*sizeX,
                                                            -corner+(double)k*sizeX));
                if(i>0 && j>0 && k>0)
                {
                    node.push_back(nodes[(k-1)*layerPoints + (j-1)*edgePoints + i-1]);
                    node.push_back(nodes[(k-1)*layerPoints + (j-1)*edgePoints + i]);
                    node.push_back(nodes[(k-1)*layerPoints + j*edgePoints + i]);
                    node.push_back(nodes[(k-1)*layerPoints + j*edgePoints + i-1]);
                    node.push_back(nodes[k*layerPoints + (j-1)*edgePoints + i-1]);
                    node.push_back(nodes[k*layerPoints + (j-1)*edgePoints + i]);
                    node.push_back(nodes[k*layerPoints + j*edgePoints + i]);
                    node.push_back(nodes[k*layerPoints + j*edgePoints + i-1]);

                    elements.push_back(Element(node, HEX8, ++numberOfElems));

                    node.clear();
                }
            }
        }
    }

}

void Mesh::generateSphereMesh()
{
    double angleSize = 2.0*PI/NODE(0);
    double angleRot;
    double theta, phi;
    double radius = DIM(1)/2.0;
    double halfRadius = 0.5*radius;
    double p2 = halfRadius/sqrt(2.0);
    double corner = halfRadius-p2*(1.0-tan(PI/6.0))/sqrt(2.0);
    double a = radius*sin(0.6154797142);
    double step = 2*a/(NODE(0)/4);
    double sizeX = 0.0;
    unsigned sidePoints =2;//NODE(0)/8 ;
    unsigned cubicPoints = 0;//pow(NODE(0)/4+1,3);
    unsigned layerPoints = (NODE(0)/8)*sidePoints;
    vector<Node> node;

    for(unsigned k = 0; k<=1; k++)
    {
        phi = atan((-a+(double)k*step)/a) ;
        for(unsigned j=0; j<=NODE(0)/8-1;j++)
        {
            theta = atan((-a+(double)j*step)/a);
            angleRot = atan(sqrt(pow(a-(double)k*step,2) + pow(a-(double)j*step,2))/a);
            //Point axisRot(0,cos(theta-phi+PI/4), 0, sin(theta-phi+PI/4));
//            cout << angleRot*180/PI <<  TAB << j << ENTER;
//            cout << axisRot << ENTER;
            for(unsigned i= 0; i<sidePoints; i++)
            {
                //Point
                sizeX = (radius - corner/fabs(sin(theta)))/(NODE(0)/8);
                Node origin(++this->numberOfNodes,0,radius-(double)i*sizeX,0);
                //origin.rotation(angleRot, axisRot);
                nodes.push_back(origin);

                //Element
                if(i>0 && j>0 && k>0)
                {
                    node.push_back(nodes[cubicPoints + (k-1)*layerPoints + (j-1)*sidePoints + i-1]);
                    node.push_back(nodes[cubicPoints + (k-1)*layerPoints + (j-1)*sidePoints + i]);
                    node.push_back(nodes[cubicPoints + (k-1)*layerPoints + j*sidePoints + i]);
                    node.push_back(nodes[cubicPoints + (k-1)*layerPoints + j*sidePoints + i-1]);
                    node.push_back(nodes[cubicPoints + k*layerPoints + (j-1)*sidePoints + i-1]);
                    node.push_back(nodes[cubicPoints + k*layerPoints + (j-1)*sidePoints + i]);
                    node.push_back(nodes[cubicPoints + k*layerPoints + j*sidePoints + i]);
                    node.push_back(nodes[cubicPoints + k*layerPoints + j*sidePoints + i-1]);

                    elements.push_back(Element(node, HEX8, ++numberOfElems));

                    node.clear();
                }
            }
        }
    }


}

/*
void Mesh::generateSphereMesh()
{
    double ratioX = 0.0, ratioY = 0.0, ratioZ = 0.0;
    double coordX, coordY, coordZ, coord;
    double angleSize = 2.0*PI/NODE(0);
    double angleSizeZ = 2*0.6154797087/(NODE(0)/4);
    double angleRot = (PI/4.0 - 0.6154797087)/(double)(NODE(0)/8);
    double radius = DIM(1)/2.0;
    double halfRadius = 0.5*radius;
    double p2 = halfRadius/sqrt(2.0);
    double corner = halfRadius-p2*(1.0-tan(PI/6.0))/sqrt(2.0);
    double a = radius*sin(0.6154797142);
    double step = 2*a/(NODE(0)/4);
    double sizeX = 0.0, sizeZ = 0.0;
    double theta, phi, phi2;
    unsigned sidePoints = NODE(0)/8 ;
    unsigned cubicPoints = 0;//pow(NODE(0)/4+1,3);
    unsigned layerPoints = (NODE(0)/4+1)*sidePoints;

    vector<Point> points;

    for(unsigned k = 0; k<=NODE(0)/4; k++)
    {
        phi = -PI/4+(double)k*angleSize ;
        ratioZ = sin(phi);
        sizeZ = (radius - corner/fabs(ratioZ))/sidePoints;
        for(unsigned j=0; j<=NODE(0)/4;j++)
        {
            theta = -PI/4.0+(double)j*angleSize;
            ratioX = sin(theta);
            ratioY = cos(theta);
            if(fabs(ratioY)>= 1.0/sqrt(2.0))
                 sizeX = (radius - corner/fabs(ratioY))/sidePoints;
            else sizeX = (radius - corner/fabs(ratioX))/sidePoints;
            for(unsigned i= 0; i<sidePoints; i++)
            {
                //Point
                if(j <NODE(0))
                {
                    coord  = (radius-(double)i*sizeX);
                    coordX = coord*ratioX*cos(phi);
                    coordY = coord*ratioY*cos(phi);
                    coordZ = coord*ratioZ;
                    nodes.push_back(Point(++this->numberOfNodes, coordX, coordY, coordZ));
                }

                //Element
                if(i>0 && j>0 && k>0)
                {
                    points.push_back(nodes[cubicPoints + (k-1)*layerPoints + (j-1)*sidePoints + i-1]);
                    points.push_back(nodes[cubicPoints + (k-1)*layerPoints + (j-1)*sidePoints + i]);

                    if(j == NODE(0))
                    {
                        points.push_back(nodes[cubicPoints + (k-1)*layerPoints + i]);
                        points.push_back(nodes[cubicPoints + (k-1)*layerPoints + i-1]);
                    }
                    else
                    {
                        points.push_back(nodes[cubicPoints + (k-1)*layerPoints + j*sidePoints + i]);
                        points.push_back(nodes[cubicPoints + (k-1)*layerPoints + j*sidePoints + i-1]);
                    }

                    points.push_back(nodes[cubicPoints + k*layerPoints + (j-1)*sidePoints + i-1]);
                    points.push_back(nodes[cubicPoints + k*layerPoints + (j-1)*sidePoints + i]);

                    if(j == NODE(0))
                    {
                        points.push_back(nodes[cubicPoints + k*layerPoints + i]);
                        points.push_back(nodes[cubicPoints + k*layerPoints + i-1]);
                    }
                    else
                    {
                        points.push_back(nodes[cubicPoints + k*layerPoints + j*sidePoints + i]);
                        points.push_back(nodes[cubicPoints + k*layerPoints + j*sidePoints + i-1]);
                    }

                    elements.push_back(Element(++numberOfElems, HEXADEDRON, points));

                    points.clear();
                }
            }
        }
    }


} */
