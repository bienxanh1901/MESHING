#ifndef NODE_H
#define NODE_H


class Node
{
    public:
        Node();
        Node(double = 0.0, double = 0.0, double = 0.0);
        Node(const Node&);
        virtual ~Node();
        Node& operator=(const Node&);
        Node& operator+(const Node&);
        Node& operator-(const Node&);
    protected:
    private:
        double x,y,z;
};

#endif // NODE_H
