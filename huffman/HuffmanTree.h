#ifndef HUFFMANTREE_H_INCLUDED
#define HUFFMANTREE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include "CharCode.h"

using namespace std;

typedef unsigned long ulong;
typedef unsigned char uchar;

struct Node
{
    char ch;
    Node* left;
    Node* right;
    ulong freq;

    bool isLeaf()const { return left == NULL && right == NULL ;}
    Node():left(NULL),right(NULL){}
};

struct Freq
{
    Node* node;

    Freq(Node* node = NULL):node(node){}
    bool operator<(const Freq&)const;
    bool operator>(const Freq&)const;
};

struct CompressedNode
{
    char ch;
    ulong freq;
};


class HuffmanTree
{
public:
    HuffmanTree(ifstream&);
    HuffmanTree(Node*);
    HuffmanTree(const HuffmanTree&);
    ~HuffmanTree();
    HuffmanTree& operator=(const HuffmanTree&);
    Node* getRoot()const{ return this->root;}
    size_t getNumbOfLeaves()const;

    void generateCode(char,CharCode&)const;
private:
    size_t getNumbOfLeaves(Node*)const;
    void generateCode(Node*, char, CharCode&)const;
    bool containsChar(Node*, char symbol)const;
    void CopyTree(Node*&,Node*);
    void DeleteTree(Node*&);

    Node* root;
};

#endif // HUFFMANTREE_H_INCLUDED
