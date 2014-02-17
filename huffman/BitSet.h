#ifndef BITSET_H_INCLUDED
#define BITSET_H_INCLUDED
#include <iostream>
#include <cstring>
#include "CharCode.h"

typedef unsigned char uchar;


class BitSet
{
public:
    BitSet(size_t = 2);
    BitSet(const BitSet&);
    ~BitSet();
    BitSet& operator=(const BitSet&);
    BitSet& operator+=(const CharCode&);
    size_t getCurrentIndex()const { return this->currentIndex; }
    const uchar* getData()const { return this->data; }

    void set(size_t);
    void clear(size_t);

    void resize();
private:
    uchar* data;
    size_t size;
    size_t currentIndex;
};

#endif // BITSET_H_INCLUDED
