#include "Element.h"

Element::Element()
{
    //ctor
}

Element::~Element()
{
    //dtor
}

Element::Element(const Element& other)
{
    //copy ctor
}

Element& Element::operator=(const Element& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
