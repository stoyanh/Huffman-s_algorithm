#ifndef COMPRESSFILE_H_INCLUDED
#define COMPRESSFILE_H_INCLUDED
#include "HuffmanTree.h"
#include <iostream>
#include <cstring>


void concatenateCodes(ifstream& file, CharCode& result, HuffmanTree& tree)
{
    file.clear();
    file.seekg(0, ios::beg);

    while(!file.eof())
    {
        char symbol;
        file.get(symbol);
        result += tree.generateCode((uchar)symbol);
    }
}

void writeLeavesInFile(ofstream& file, Node* node)
{
    if(node == NULL)
        return;

    if(node->isLeaf())
    {
        CompressedNode tmp;
        tmp.ch = node->ch;
        tmp.freq = node->freq;
        file.write((const char*)&tmp, sizeof(tmp));
        return;
    }

    writeLeavesInFile(file, node->left);
    writeLeavesInFile(file, node->right);
}

void writeArrayInFile(ofstream& file, uchar* array, int codeSize)
{
    file.write((const char*) &codeSize, sizeof(int));
    file.write((const char*)array, (codeSize / 8 + 1) * sizeof(uchar));
}

void writeBinaryFile(const char* filename, HuffmanTree& tree, uchar* info, int codeSize)
{
    ofstream file(filename, ios::binary);
    if(!file)
        throw "Cannot create result file!";

    int numbOfLeaves = tree.getNumbOfLeaves();

    file.write((const char*) &numbOfLeaves, sizeof(int));
    writeLeavesInFile(file, tree.getRoot());
    writeArrayInFile(file, info, codeSize);

    file.close();

}

void Compress(const char* filepath)
{
    ifstream file(filepath);
    if(!file)
        throw "Cannot open file !";

    HuffmanTree tree(file);

    CharCode result;
    concatenateCodes(file, result, tree);

    int codeSize = result.getSize();
    const int arrSize = codeSize / 8 + 1;


    uchar data[arrSize];
    memset(data, 0, arrSize);

    /// fill array with bits
    size_t index = 0;
    char* code = (char*) result.getCode();

    for( ; *code ; ++code , ++index)
        data[index / 8] = data[index / 8] | ( ((*code) - '0') << (8 - index % 8 - 1));

     writeBinaryFile("compressed", tree, data, codeSize);


}



#endif // COMPRESSFILE_H_INCLUDED
