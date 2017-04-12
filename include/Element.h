#ifndef ELEMENT_H
#define ELEMENT_H


class Element
{
    public:
        Element();
        Element(const Element& );
        virtual ~Element();
        Element& operator=(const Element& other);
    protected:
    private:
};

#endif // ELEMENT_H
