#ifndef BINSEARCHTREE_H_INCLUDED
#define BINSEARCHTREE_H_INCLUDED
#include <iostream>

extern CompressedNode;

class BinSearchTree
{
public:
    BinSearchTree():node(NULL){};
    ~BinSearchTree();
    BinSearchTree(const BinSearchTree&);
    BinSearchTree& operator=(const BinSearchTree&);
    void Insert(char, ulong);
    bool contains(char)const;
private:
    void DeleteTree(CompressedNode*&);
    void CopyTree(CompressedNode*&, CompressedNode*);
    CompressedNode* node;
};

BinSearchTree::BinSearchTree(const BinSearchTree& source)
{

}

#endif // BINSEARCHTREE_H_INCLUDED
