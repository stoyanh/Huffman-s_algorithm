#include "HuffmanTree.h"
#include "MinHeap.h"


bool Freq::operator<(const Freq& right)const
{
    return this->node->freq < right.node->freq;
}

bool Freq::operator>(const Freq& right)const
{
    return this->node->freq > right.node->freq;
}

HuffmanTree::HuffmanTree(ifstream& file)
{
    ulong symbols[256];
    for(size_t i = 0 ; i < 256 ; ++i)
        symbols[i] = 0;

    while(!file.eof())
    {
        char ch;
        file.get(ch);
        ++symbols[(int)ch];
    }

   MinHeap<Freq> heap;
   for(size_t i = 0 ; i < 256 ; ++i)
   {
       if(symbols[i])
       {
           Node* node = new Node;
           node->freq = symbols[i];
           node->ch = (uchar)i;
           //cout << i << " " << symbols[i] << endl;
           Freq f(node);
           heap.push(f);
       }
   }

   if(!heap.getSize())
   {
       file.close();
       throw "Empty file!";
   }

   while(heap.getSize() != 1)
   {
       Freq f1;
       heap.pop(f1);

       Freq f2;
       heap.pop(f2);

       Freq result;
       Node* newNode = new Node;
       newNode->freq = f1.node->freq + f2.node->freq;
       newNode->left = f1.node;
       newNode->right = f2.node;

       result.node = newNode;
       heap.push(result);
   }

   Freq f;
   heap.pop(f);
   this->root = f.node;
}

HuffmanTree::~HuffmanTree()
{
    this->DeleteTree(this->root);
}

HuffmanTree::HuffmanTree(const HuffmanTree& source)
{
    this->CopyTree(this->root, source.root);
}

HuffmanTree::HuffmanTree(Node* node)
{
    this->root = node;
}

HuffmanTree& HuffmanTree::operator=(const HuffmanTree& source)
{
    if(this != &source)
    {
        this->DeleteTree(this->root);
        this->CopyTree(this->root, source.root);
    }
    return *this;
}

void HuffmanTree::CopyTree(Node*& node, Node* source)
{
    if(source == NULL)
     return;

    node = new Node;
    node->ch = source->freq;
    node->freq = source->freq;

    this->CopyTree(node->left, source->left);
    this->CopyTree(node->right, source->right);

}

void HuffmanTree::DeleteTree(Node*& node)
{
    if(node == NULL)
        return;

    this->DeleteTree(node->left);
    this->DeleteTree(node->right);

    delete node;
    node = NULL;
}

bool HuffmanTree::containsChar(Node* node, uchar symbol)const
{
    if(!node)
        return false;
    if(node->isLeaf() && node->ch == symbol)
        return true;
    if(node->isLeaf() && node->ch != symbol)
        return false;
    if(this->containsChar(node->left, symbol))
        return true;
    else return this->containsChar(node->right, symbol);
}

CharCode HuffmanTree::generateCode(uchar symbol)const
{
   return this->generateCode(this->root, symbol);
}

CharCode HuffmanTree::generateCode(Node* node, uchar symbol)const
{
    if(node->isLeaf())
       return "";

   if(this->containsChar(node->left, symbol))
        return "0" + this->generateCode(node->left, symbol);

   else return "1" + this->generateCode(node->right, symbol);
}

size_t HuffmanTree::getNumbOfLeaves()const
{
    return this->getNumbOfLeaves(this->root);
}

size_t HuffmanTree::getNumbOfLeaves(Node* node)const
{
    if(node == NULL)
        return 0;

    if(node->isLeaf())
        return 1;

    return this->getNumbOfLeaves(node->left) + this->getNumbOfLeaves(node->right);

}