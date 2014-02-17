#ifndef DECOMPRESSFILE_H_INCLUDED
#define DECOMPRESSFILE_H_INCLUDED
#include <fstream>
#include <iostream>

using namespace std;

typedef unsigned char uchar;

bool isEmpty(ifstream& file)
{
    file.seekg(0, ios::beg);
    size_t beg = file.tellg();

    file.seekg(0, ios::end);
    size_t end = file.tellg();

    file.seekg(0, ios::beg);
    return (end - beg) == 0;
}

Node* BuildHuffmanTree(CompressedNode* leaves, int numbOfLeaves)
{
    MinHeap<Freq> heap;
    for(int i = 0 ; i < numbOfLeaves ; ++i)
    {
        Node* node = new Node;
        node->ch = leaves[i].ch;
        node->freq = leaves[i].freq;
        Freq f(node);
        heap.push(f);
    }

    delete [] leaves;

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
    return f.node;
}

void WriteInFile(const char* filepath, HuffmanTree& tree, uchar* data, int codeSize)
{
    Node* node = tree.getRoot();

    ofstream file(filepath);
    if(!file)
        throw "Cannot open file !";

    for(int i = 0 ; i < codeSize ; ++i)
    {
        if(node->isLeaf())
        {
            file << node->ch;
            node = tree.getRoot();
        }
        if((data[i / 8] >> (8 - (i % 8) - 1) & 1) == 0)
          node = node->left;

        else node = node->right;
    }

    file.close();

}

void Decompress(const char* filepath)
{
    ifstream file(filepath, ios::binary);

    if(!file)
        throw "Cannot open file !";

    if(isEmpty(file))
        throw "Empty file !";

    int numbOfLeaves;
    file.read((char*) &numbOfLeaves, sizeof(int));

    CompressedNode* leaves = new CompressedNode [numbOfLeaves];
    file.read((char*)leaves, numbOfLeaves * sizeof(CompressedNode));

    Node* node = BuildHuffmanTree(leaves, numbOfLeaves);
    HuffmanTree tree(node);

    int codeSize;
    file.read((char*) &codeSize, sizeof(int));

    uchar* data = new uchar [codeSize / 8 + 1];
    file.read((char*)data, (codeSize / 8 + 1) * sizeof(uchar));

    WriteInFile("Decompressed", tree, data, codeSize);
}


#endif // DECOMPRESSFILE_H_INCLUDED
