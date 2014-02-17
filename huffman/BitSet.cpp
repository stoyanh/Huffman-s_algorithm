#include "BitSet.h"


BitSet::BitSet(size_t size)
{
    this->data = new uchar[size];
    memset(data, 0, size);
    this->size = size;
    this->currentIndex = 0;
}

BitSet::BitSet(const BitSet& source)
{
    this->size = source.size;
    this->data = new uchar[this->size];
    memcpy(this->data, source.data, this->size);
    this->currentIndex = source.currentIndex;
}

BitSet::~BitSet()
{
    delete [] this->data;
    this->size = 0;
}

BitSet& BitSet::operator=(const BitSet& source)
{
    if(this != &source)
    {
        delete [] this->data;
        this->size = source.size;
        this->data = new uchar[this->size];
        memcpy(this->data, source.data, this->size);
        this->currentIndex = source.currentIndex;
    }
    return *this;
}

void BitSet::set(size_t index)
{
    if(index / 8 == this->size)
        this->resize();
    this->data[index / 8] |= (1 << (8 - index % 8 - 1));
}

void BitSet::clear(size_t index)
{
    if(index / 8 == this->size)
        this->resize();
    this->data[index / 8] &= ~(1 << (8 - index % 8 - 1));
}

void BitSet::resize()
{
    uchar* tmp = new uchar[this->size * 2];
    memset(tmp, 0, this->size * 2);
    memcpy(tmp, this->data, this->size);

    this->size = this->size * 2;
    delete [] this->data;

    this->data = tmp;
}

BitSet& BitSet::operator+=(const CharCode& ch)
{
    char* code = (char*)ch.getCode();
    for( ;*code ; ++code, ++this->currentIndex)
    {
        if(*code - '0')
            this->set(this->currentIndex);
        else this->clear(this->currentIndex);
    }

    return *this;
}
