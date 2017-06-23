
#ifndef TYPEVECTOR_H
#define TYPEVECTOR_H
#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;
template<class T>
class typeVector
{
    public:
        typeVector(T = 0, T = 0, T = 0 );
        typeVector(const typeVector<T>&);
        virtual ~typeVector() {}
        typeVector<T>& operator=(const typeVector<T>&);
        typeVector<T> operator+(const typeVector<T>&);
        typeVector<T> operator-(const typeVector<T>&);
        typeVector<T> operator*(const T);
        T operator*(const typeVector<T>&);
        typeVector<T> operator/(const T);
        typeVector<T>& operator+=(const typeVector<T>&);
        typeVector<T>& operator-=(const typeVector<T>&);
        typeVector<T>& operator*=(const T);
        typeVector<T>& operator/=(const T);
        T& operator() (const unsigned );
        const T& operator() (const unsigned ) const;
        bool operator==(const typeVector<T>&);
        bool operator>(const typeVector<T>&);
        bool operator>=(const typeVector<T>&);
        bool operator<(const typeVector<T>&);
        bool operator<=(const typeVector<T>&);
        bool operator!=(const typeVector<T>&);
        typeVector<T> cross(const typeVector<T>&);
        typeVector<T> unit();
        T norm();
        T norm_sq();
        void assign(const typeVector<T>&);
        void add(const typeVector<T>&);
        void subtract(const typeVector<T>&);
        void translate(T, T, T);
        ostream& print(ostream&);
    protected:
        T coords[3];
        friend ostream& operator<<(ostream& out,typeVector<T>& V )
        {
            return V.print(out);
        }
    private:
};

template<class T>
typeVector<T>::typeVector(T x, T y, T z )
{
    coords[0] = x;
    coords[1] = y;
    coords[2] = z;

}

template<class T>
typeVector<T>::typeVector(const typeVector<T>& other)
{
    coords[0] = other.coords[0];
    coords[1] = other.coords[1];
    coords[2] = other.coords[2];
}

template<class T>
typeVector<T>& typeVector<T>::operator=(const typeVector<T>& rhs)
{
    coords[0] = rhs.coords[0];
    coords[1] = rhs.coords[1];
    coords[2] = rhs.coords[2];
    return *this;

}

template<class T>
typeVector<T> typeVector<T>::operator+(const typeVector<T>& rhs)
{
    return typeVector<T>(coords[0]+rhs.coords[0],
                          coords[1]+rhs.coords[1],
                          coords[2]+rhs.coords[2]);
}

template<class T>
typeVector<T> typeVector<T>::operator-(const typeVector<T>& rhs)
{
    return typeVector<T>(coords[0]-rhs.coords[0],
                         coords[1]-rhs.coords[1],
                         coords[2]-rhs.coords[2]);
}

template<class T>
T typeVector<T>::operator*(const typeVector<T>& rhs)
{
    return coords[0]*rhs.coords[0]+
           coords[1]*rhs.coords[1]+
           coords[2]*rhs.coords[2];
}

template<class T>
typeVector<T> typeVector<T>::operator*(const T factor)
{
    return typeVector<T>(coords[0]*factor,
                          coords[1]*factor,
                          coords[2]*factor);
}

template<class T>
typeVector<T> typeVector<T>::operator/(const T factor)
{
    return typeVector<T>(coords[0]/factor,
                          coords[1]/factor,
                          coords[2]/factor);
}

template<class T>
typeVector<T>& typeVector<T>::operator+=(const typeVector<T>& rhs)
{
    coords[0]+=rhs.coords[0];
    coords[1]+=rhs.coords[1];
    coords[2]+=rhs.coords[2];
    return *this;
}

template<class T>
typeVector<T>& typeVector<T>::operator-=(const typeVector<T>& rhs)
{
    coords[0]-=rhs.coords[0];
    coords[1]-=rhs.coords[1];
    coords[2]-=rhs.coords[2];
    return *this;
}

template<class T>
typeVector<T>& typeVector<T>::operator*=(const T factor)
{
    coords[0]*=factor;
    coords[1]*=factor;
    coords[2]*=factor;
    return *this;
}

template<class T>
typeVector<T>& typeVector<T>::operator/=(const T factor)
{
    coords[0]/=factor;
    coords[1]/=factor;
    coords[2]/=factor;
    return *this;
}

template<class T>
T& typeVector<T>::operator() (const unsigned i)
{
    //@TODO this function still incomplete
    //Note that: you can use assert to terminate the if i > 2
    return coords[i];
}

template<class T>
const T& typeVector<T>::operator() (const unsigned i) const
{
    //@TODO this function still incomplete
    //Note that: you can use assert to terminate the if i > 2
    return coords[i];
}

template<class T>
bool typeVector<T>::operator==(const typeVector<T>& rhs)
{
    return (coords[0] == rhs.coords[0] &&
            coords[1] == rhs.coords[1] &&
            coords[2] == rhs.coords[2]);
}

template<class T>
bool typeVector<T>::operator>(const typeVector<T>& rhs)
{
    for (unsigned i = 0; i<3; i++)
    {
        if((*this)(i)>rhs(i))return true;
        if((*this)(i)<rhs(i))return false;
    }
    return false;
}

template<class T>
bool typeVector<T>::operator>=(const typeVector<T>& rhs)
{
    for (unsigned i = 0; i<3; i++)
    {
        if((*this)(i)>rhs(i))return true;
        if((*this)(i)<rhs(i))return false;
    }
    return true;
}


template<class T>
bool typeVector<T>::operator<(const typeVector<T>& rhs)
{
    for (unsigned i = 0; i<3; i++)
    {
        if((*this)(i)<rhs(i))return true;
        if((*this)(i)>rhs(i))return false;
    }
    return false;
}

template<class T>
bool typeVector<T>::operator<=(const typeVector<T>& rhs)
{
    for (unsigned i = 0; i<3; i++)
    {
        if((*this)(i)<rhs(i))return true;
        if((*this)(i)>rhs(i))return false;
    }
    return true;
}

template<class T>
bool typeVector<T>::operator!=(const typeVector<T>& rhs)
{
    return (coords[0] != rhs.coords[0] ||
            coords[1] != rhs.coords[1] ||
            coords[2] != rhs.coords[2]);
}

template<class T>
typeVector<T> typeVector<T>::cross(const typeVector<T>& rhs)
{
    return typeVector<T>((*this)(1)*rhs(2)-(*this)(2)*rhs(1),
                         (*this)(2)*rhs(0)-(*this)(0)*rhs(2),
                         (*this)(0)*rhs(1)-(*this)(1)*rhs(0));
}

template<class T>
typeVector<T> typeVector<T>::unit()
{
    T nm = this->norm();
    return typeVector<T>((*this)(0)/nm,
                         (*this)(1)/nm,
                         (*this)(2)/nm);
}

template<class T>
T typeVector<T>::norm()
{
    return sqrt(this->norm_sq());
}

template<class T>
T typeVector<T>::norm_sq()
{
    return (*this)(0)*(*this)(0)+
           (*this)(1)*(*this)(1)+
           (*this)(2)*(*this)(2);
}

template<class T>
void typeVector<T>::assign(const typeVector<T>& rhs)
{
    //assign
    coords[0] = rhs.coords[0];
    coords[1] = rhs.coords[1];
    coords[2] = rhs.coords[2];

}

template<class T>
void typeVector<T>::add(const typeVector<T>& rhs)
{
    *this += rhs;
}

template<class T>
void typeVector<T>::subtract(const typeVector<T>& rhs)
{
    *this -= rhs;
}

template<class T>
ostream& typeVector<T>::print(ostream& out)
{
    out << coords[0]  << " " << coords[1]  << " " << coords[2] << " ";
    return out;
}

template<class T>
void typeVector<T>::translate(T x, T y, T z)
{
    *this += typeVector<T>(x,y,z);
}
#endif // TYPEVECTOR_H
