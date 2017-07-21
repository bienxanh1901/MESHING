#ifndef ARRAYTEMPLATE_H_INCLUDED
#define ARRAYTEMPLATE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <assert.h>

using namespace std;

template<class T>
class Array {
    public:
        Array(unsigned = 0);
        Array(unsigned, T*);
        Array(const Array<T> &);
        Array(Array<T>*);
        virtual ~Array();

        void reSize(unsigned);
        unsigned getSize();
        void insert(unsigned, T);
        T get(unsigned);
        T* getAddress();
        Array<T>& operator=(const Array<T> &);
        T& operator[] (unsigned);
        bool operator==(const Array<T>&);
        bool operator!=(const Array<T>&);
        istream& read(istream&);
    protected:
        unsigned size;
        T *array;
        friend istream& operator>>(istream& in, Array& arr) {
            return arr.read(in);
        }
    private:
        void allocate();
        void free();
};

//
template<class T>
Array<T>::Array(unsigned n) {

    this->size = n;
    if(this->size != 0) this->allocate();
}

//
template<class T>
Array<T>::Array(unsigned n, T* arr) {

    this->size = n;
    if(this->size != 0) {
        this->allocate();
        for(unsigned i = 0; i < this->size; i++) {
            *(this->array + i) = *(arr + i);
        }
    }

}

//
template<class T>
Array<T>::Array(const Array<T> & arr) {

    if(arr.size != 0) {
        this->size = arr.size;
        this->allocate();
        for(unsigned i = 0; i < this->size; i++) {
            *(this->array + i) = *(arr.array + i);
        }
    }

}


//
template<class T>
Array<T>::Array(Array<T>* arr) {

    if(arr->size != 0) {
        this->size = arr->size;
        this->allocate();
        for(unsigned i = 0; i < this->size; i++) {
            *(this->array + i) = *(arr->array + i);
        }
    }

}


//
template<class T>
Array<T>::~Array() {

    if(this->array != NULL) this->free();
}

//
template<class T>
void Array<T>::reSize(unsigned newSize) {

    this->size = newSize;
    if(this->array != NULL) this->free();
    if(this->size != 0) this->allocate();

}

//
template<class T>
unsigned Array<T>::getSize() { return this->size;}

//
template<class T>
void Array<T>::insert(unsigned position, T value) {
    assert(this->size != 0);
    if(position < this->size) *(this->array + position) = value;
}

//
template<class T>
T Array<T>::get(unsigned position) {
    assert(this->size != 0);
    if(position < this->size) return *(this->array + position);
}

//
template<class T>
T* Array<T>::getAddress() {

    if(this->array != NULL) return this->array;
}

//
template<class T>
Array<T>& Array<T>::operator=(const Array<T> & arr) {

    if(arr.size != 0) {
        this->size = arr.size;
        if(this->array != NULL) this->free();
        this->allocate();
        for(unsigned i = 0; i < this->size; i++) {
            *(this->array + i) = *(arr.array + i);
        }
    }
    return *this;
}

//
template<class T>
T& Array<T>::operator[] (unsigned position) {

    assert(this->size != 0 && position < this->size);
    return *(this->array + position);
}

//
template<class T>
bool Array<T>::operator==(const Array<T>& arr) {

    if(this->size != arr.size) return false;
    else {
        for(unsigned i = 0; i < this->size; i++) {
            if(*(this->array + i) != *(arr.array + i)) return false;
        }
    }
    return true;
}

//
template<class T>
bool Array<T>::operator!=(const Array<T>& arr) {

    if(this->size != arr.size) return true;
    else {

        for(unsigned i = 0; i < this->size; i++) {
            if(*(this->array + i) != *(arr.array + i)) return true;
        }
    }
    return false;
}


//
template<class T>
void Array<T>::allocate() {

    this->array = new T[this->size];
}

//
template<class T>
void Array<T>::free() {

     delete[] this->array;
}

template<class T>
istream& Array<T>::read(istream& in) {

    for(unsigned i = 0; i < this->size; i++) {

        in >> this->array[i];

    }
    return in;
}
#endif // ARRAYTEMPLATE_H_INCLUDED
