#ifndef MINHEAP_H_INCLUDED
#define MINHEAP_H_INCLUDED

#include <iostream>

template<typename T>
class MinHeap
{
public:
    MinHeap(size_t = 10);
    MinHeap<T>& operator=(const MinHeap<T>&);
    MinHeap(const MinHeap<T>&);
    ~MinHeap();

    void push(const T&);
    bool pop(T&);
    bool isFull()const;
    size_t getSize()const;
    void print()const;
private:
    void copy(const MinHeap<T>&);
    void resize(size_t);
    void swap(T& el1, T& el2);
    size_t lesser(size_t, size_t)const;

    T* elements;
    size_t size;
    size_t elementsCount;

};

template <typename T>
MinHeap<T>::MinHeap(size_t size)
{
    this->elements = new T [size];
    this->size = size;
    this->elementsCount = 0;
}

template <typename T>
MinHeap<T>::~MinHeap()
{
    delete [] elements;
    this->elementsCount = 0;
}

template <typename T>
MinHeap<T>::MinHeap(const MinHeap<T>& source)
{
    this->copy(source);
}

template <typename T>
MinHeap<T>& MinHeap<T>::operator=(const MinHeap<T>& source)
{
    if(this != &source)
    {
        this->copy(source);
    }
    return *this;
}

template <typename T>
void MinHeap<T>::copy(const MinHeap<T>& source)
{
    delete [] elements;
    this->size = source.size;

    this->elements = new T [this->size];

    for(size_t i = 1 ; i <= source.elementsCount ; ++i)
        this->elements[i] = source.elements[i];

    this->elementsCount = source.elementsCount;
}

template <typename T>
bool MinHeap<T>::isFull()const
{
    return this->elementsCount == this->size - 1;
}

template <typename T>
size_t MinHeap<T>::getSize()const
{
    return this->elementsCount;
}

template <typename T>
void MinHeap<T>::resize(size_t newSize)
{
    T* tmp = new T[newSize];

    for(size_t i = 1 ; i <= this->elementsCount ; ++i)
        tmp[i] = this->elements[i];

    delete [] this->elements;

    this->elements = tmp;
    this->size = newSize;
}

template <typename T>
void MinHeap<T>::swap(T& el1, T& el2)
{
    T tmp = el2;
    el2 = el1;
    el1 = tmp;
}

template <typename T>
void MinHeap<T>::push(const T& el)
{
    if(this->isFull())
        this->resize(this->size * 2);

    this->elements[++this->elementsCount] = el;

    size_t index = this->elementsCount;

    while(index / 2 && this->elements[index] < this->elements[index / 2])
    {
        this->swap(this->elements[index], this->elements[index / 2]);
        index = index / 2;
    }

}

template <typename T>
size_t MinHeap<T>::lesser(size_t index1, size_t index2)const
{
    if(index1 > this->elementsCount || index2 > this->elementsCount)
    {
        size_t index = index1 > this->elementsCount ? index2 : index1;
        return index > this->elementsCount ? 0 : index;
    }

    return this->elements[index1] < this->elements[index2] ? index1 : index2;
}

template <typename T>
bool MinHeap<T>::pop(T& el)
{
    if(!this->getSize())
        return false;

    el = this->elements[1];
    this->elements[1] = this->elements[this->elementsCount--];

    if(this->elementsCount < this->size / 4)
       this->resize(this->size / 2);

    size_t index = 1;
    while(1)
    {
        size_t tmp = lesser(index * 2 , index * 2 + 1);
        if(!tmp)
            break;

        if(this->elements[index] > this->elements[tmp])
            this->swap(this->elements[index] , this->elements[tmp]);
        else break;

        index = tmp;
    }
    return true;
}

template <typename T>
void MinHeap<T>::print()const
{
    for(size_t i = 1 ; i <= this->elementsCount ; ++i)
        std::cout << this->elements[i] << " ";
    std::cout << std::endl;
}
#endif // MINHEAP_H_INCLUDED
