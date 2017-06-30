
#ifndef TypeVector_H
#define TypeVector_H
#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;
template<class T>
class TypeVector {
    public:
        TypeVector(T = 0, T = 0, T = 0 );
        TypeVector(const TypeVector<T>&);
        virtual ~TypeVector() {}
        TypeVector<T>& operator=(const TypeVector<T>&);
        TypeVector<T> operator+(const TypeVector<T>&);
        TypeVector<T> operator-(const TypeVector<T>&);
        TypeVector<T> operator*(const T);
        T operator*(const TypeVector<T>&);
        TypeVector<T> operator/(const T);
        TypeVector<T>& operator+=(const TypeVector<T>&);
        TypeVector<T>& operator-=(const TypeVector<T>&);
        TypeVector<T>& operator*=(const T);
        TypeVector<T>& operator/=(const T);
        T& operator() (const unsigned );
        const T& operator() (const unsigned ) const;
        bool operator==(const TypeVector<T>&);
        bool operator>(const TypeVector<T>&);
        bool operator>=(const TypeVector<T>&);
        bool operator<(const TypeVector<T>&);
        bool operator<=(const TypeVector<T>&);
        bool operator!=(const TypeVector<T>&);
        TypeVector<T> cross(const TypeVector<T>&);
        TypeVector<T> plus(const T, const T, const T);
        TypeVector<T> unit();
        T norm();
        T norm_sq();
        void assign(const TypeVector<T>&);
        void add(const TypeVector<T>&);
        void subtract(const TypeVector<T>&);
        void translate(T, T, T);
        TypeVector<T> rotate(T&, TypeVector<T>&);
        ostream& print(ostream&);
    protected:
        T coords[3];
        friend ostream& operator<<(ostream& out,TypeVector<T>& V ) {
            return V.print(out);
        }
    private:
};

template<class T>
TypeVector<T>::TypeVector(T x, T y, T z ) {
    coords[0] = x;
    coords[1] = y;
    coords[2] = z;

}

template<class T>
TypeVector<T>::TypeVector(const TypeVector<T>& other) {
    coords[0] = other.coords[0];
    coords[1] = other.coords[1];
    coords[2] = other.coords[2];
}

template<class T>
TypeVector<T>& TypeVector<T>::operator=(const TypeVector<T>& rhs) {
    coords[0] = rhs.coords[0];
    coords[1] = rhs.coords[1];
    coords[2] = rhs.coords[2];
    return *this;

}

template<class T>
TypeVector<T> TypeVector<T>::operator+(const TypeVector<T>& rhs) {
    return TypeVector<T>(coords[0]+rhs.coords[0],
                          coords[1]+rhs.coords[1],
                          coords[2]+rhs.coords[2]);
}

template<class T>
TypeVector<T> TypeVector<T>::operator-(const TypeVector<T>& rhs) {
    return TypeVector<T>(coords[0]-rhs.coords[0],
                         coords[1]-rhs.coords[1],
                         coords[2]-rhs.coords[2]);
}

template<class T>
T TypeVector<T>::operator*(const TypeVector<T>& rhs) {
    return coords[0]*rhs.coords[0]+
           coords[1]*rhs.coords[1]+
           coords[2]*rhs.coords[2];
}

template<class T>
TypeVector<T> TypeVector<T>::operator*(const T factor) {
    return TypeVector<T>(coords[0]*factor,
                          coords[1]*factor,
                          coords[2]*factor);
}

template<class T>
TypeVector<T> TypeVector<T>::operator/(const T factor) {
    return TypeVector<T>(coords[0]/factor,
                          coords[1]/factor,
                          coords[2]/factor);
}

template<class T>
TypeVector<T>& TypeVector<T>::operator+=(const TypeVector<T>& rhs) {
    coords[0]+=rhs.coords[0];
    coords[1]+=rhs.coords[1];
    coords[2]+=rhs.coords[2];
    return *this;
}

template<class T>
TypeVector<T>& TypeVector<T>::operator-=(const TypeVector<T>& rhs) {
    coords[0]-=rhs.coords[0];
    coords[1]-=rhs.coords[1];
    coords[2]-=rhs.coords[2];
    return *this;
}

template<class T>
TypeVector<T>& TypeVector<T>::operator*=(const T factor) {
    coords[0]*=factor;
    coords[1]*=factor;
    coords[2]*=factor;
    return *this;
}

template<class T>
TypeVector<T>& TypeVector<T>::operator/=(const T factor) {
    coords[0]/=factor;
    coords[1]/=factor;
    coords[2]/=factor;
    return *this;
}

template<class T>
T& TypeVector<T>::operator() (const unsigned i) {
    //@TODO this function still incomplete
    //Note that: you can use assert to terminate the if i > 2
    return coords[i];
}

template<class T>
const T& TypeVector<T>::operator() (const unsigned i) const {
    //@TODO this function still incomplete
    //Note that: you can use assert to terminate the if i > 2
    return coords[i];
}

template<class T>
bool TypeVector<T>::operator==(const TypeVector<T>& rhs) {
    return (coords[0] == rhs.coords[0] &&
            coords[1] == rhs.coords[1] &&
            coords[2] == rhs.coords[2]);
}

template<class T>
bool TypeVector<T>::operator>(const TypeVector<T>& rhs) {
    for (unsigned i = 0; i<3; i++) {
        if((*this)(i)>rhs(i))return true;
        if((*this)(i)<rhs(i))return false;
    }
    return false;
}

template<class T>
bool TypeVector<T>::operator>=(const TypeVector<T>& rhs) {
    for (unsigned i = 0; i<3; i++) {
        if((*this)(i)>rhs(i))return true;
        if((*this)(i)<rhs(i))return false;
    }
    return true;
}


template<class T>
bool TypeVector<T>::operator<(const TypeVector<T>& rhs) {
    for (unsigned i = 0; i<3; i++) {
        if((*this)(i)<rhs(i))return true;
        if((*this)(i)>rhs(i))return false;
    }
    return false;
}

template<class T>
bool TypeVector<T>::operator<=(const TypeVector<T>& rhs) {
    for (unsigned i = 0; i<3; i++) {
        if((*this)(i)<rhs(i))return true;
        if((*this)(i)>rhs(i))return false;
    }
    return true;
}

template<class T>
bool TypeVector<T>::operator!=(const TypeVector<T>& rhs) {
    return (coords[0] != rhs.coords[0] ||
            coords[1] != rhs.coords[1] ||
            coords[2] != rhs.coords[2]);
}

template<class T>
TypeVector<T> TypeVector<T>::cross(const TypeVector<T>& rhs) {
    return TypeVector<T>((*this)(1)*rhs(2)-(*this)(2)*rhs(1),
                         (*this)(2)*rhs(0)-(*this)(0)*rhs(2),
                         (*this)(0)*rhs(1)-(*this)(1)*rhs(0));
}

template<class T>
TypeVector<T> TypeVector<T>::plus(const T x, const T y, const T z) {
    this->coords[0]*= x;
    this->coords[1]*= y;
    this->coords[2]*= z;
}

template<class T>
TypeVector<T> TypeVector<T>::unit() {
    T nm = this->norm();
    return TypeVector<T>((*this)(0)/nm,
                         (*this)(1)/nm,
                         (*this)(2)/nm);
}

template<class T>
T TypeVector<T>::norm() {
    return sqrt(this->norm_sq());
}

template<class T>
T TypeVector<T>::norm_sq() {
    return (*this)(0)*(*this)(0)+
           (*this)(1)*(*this)(1)+
           (*this)(2)*(*this)(2);
}

template<class T>
void TypeVector<T>::assign(const TypeVector<T>& rhs) {
    //assign
    coords[0] = rhs.coords[0];
    coords[1] = rhs.coords[1];
    coords[2] = rhs.coords[2];

}

template<class T>
void TypeVector<T>::add(const TypeVector<T>& rhs) {
    *this += rhs;
}

template<class T>
void TypeVector<T>::subtract(const TypeVector<T>& rhs) {
    *this -= rhs;
}

template<class T>
ostream& TypeVector<T>::print(ostream& out) {
    out << coords[0]  << " " << coords[1]  << " " << coords[2] << " ";
    return out;
}

template<class T>
void TypeVector<T>::translate(T x, T y, T z) {
    *this += TypeVector<T>(x,y,z);
}

template<class T>
TypeVector<T> TypeVector<T>::rotate(T& angle, TypeVector<T>& axis)
{
    T costheta = cos(angle);
    T sintheta = sin(angle);
    T xrot, yrot, zrot;
    xrot = this->coords[0]*(costheta+ pow(axis(0),2)*(1-costheta)) +
           this->coords[1]*(axis(0)*axis(1)*(1-costheta) - axis(2)*sintheta) +
           this->coords[2]*(axis(0)*axis(2)*(1-costheta) + axis(1)*sintheta);
    yrot = this->coords[1]*(costheta+ pow(axis(1),2)*(1-costheta)) +
           this->coords[0]*(axis(1)*axis(0)*(1-costheta) + axis(2)*sintheta) +
           this->coords[2]*(axis(1)*axis(2)*(1-costheta) - axis(0)*sintheta);
    zrot = this->coords[2]*(costheta+ pow(axis(2),2)*(1-costheta)) +
           this->coords[0]*(axis(2)*axis(0)*(1-costheta) - axis(1)*sintheta) +
           this->coords[1]*(axis(2)*axis(1)*(1-costheta) + axis(0)*sintheta);

    return TypeVector<T>(xrot, yrot, zrot);
}
#endif // TypeVector_H
