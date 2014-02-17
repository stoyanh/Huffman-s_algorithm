#ifndef CHARCODE_H_INCLUDED
#define CHARCODE_H_INCLUDED
#include <iostream>



class CharCode
{
    friend CharCode operator+(const CharCode&, const CharCode&);
public:
    CharCode(size_t = 0);
    CharCode(const char*);
    CharCode(const CharCode&);
    ~CharCode();
    CharCode& operator=(const CharCode&);
    CharCode& operator+=(const CharCode&);
    const char* getCode()const {return code;}
    size_t getSize()const { return this->currentCount; }
private:
    char symbol;
    char* code;
    size_t size;
    size_t currentCount;
};

#endif // CHARCODE_H_INCLUDED