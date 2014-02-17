#include "CharCode.h"
#include <cstring>
CharCode::CharCode(size_t size)
{
    this->code = new char[size + 1];
    this->size = size;
    this->currentCount = 0;

    this->code[this->currentCount] = '\0';
}

CharCode::CharCode(const CharCode& source)
{
    this->size = source.size;

    this->code = new char [this->size + 1];
    strcpy(this->code, source.code);

    this->currentCount = source.currentCount;
}

CharCode::CharCode(const char* str)
{
    this->code = new char [strlen(str) + 1];

    strcpy(this->code,str);
    this->size = strlen(str);
    this->currentCount = this->size;
}

CharCode::~CharCode()
{
    delete [] this->code;
    this->currentCount = 0;
    this->size = 0;
}

CharCode& CharCode::operator=(const CharCode& source)
{
    if(this != &source)
    {
        delete [] this->code;

        this->size = source.size;

        this->code = new char [this->size + 1];
        strcpy(this->code, source.code);

        this->currentCount = source.currentCount;
    }
    return *this;
}

CharCode operator+(const CharCode& left, const CharCode& right)
{
    char* tmp = new char [left.size + right.size + 1];

    strcpy(tmp, left.code);
    strcat(tmp, right.code);

    return CharCode(tmp);
}

CharCode& CharCode::operator+=(const CharCode& right)
{
    *this = *this + right;
    return *this;
}

