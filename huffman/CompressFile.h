#ifndef COMPRESSFILE_H_INCLUDED
#define COMPRESSFILE_H_INCLUDED
#include "HuffmanTree.h"
#include <iostream>
#include <cstring>
#include "BitSet.h"


void FillBitSet(ifstream& file, BitSet& result, HuffmanTree& tree)
{
    file.clear();
    file.seekg(0, ios::beg);
    CharCode allreadyKnown[256];
    while(!file.eof())
    {
        char symbol;
        file.get(symbol);
        if(allreadyKnown[(int)symbol].getSize())
            result += allreadyKnown[(int)symbol];
        else
        {
            tree.generateCode(symbol, allreadyKnown[(int)symbol]);
            result += allreadyKnown[(int)symbol];
        }
    }
}

void writeLeavesInFile(ofstream& file, HuffmanTree& tree)
{
    Node** leaves = tree.getLeaves();
    for(size_t i = 0 ; i < 256 ; ++i)
    {
        if(leaves[i] != NULL)
        {
            CompressedNode tmp;
            tmp.ch = leaves[i]->ch;
            tmp.freq = leaves[i]->freq;
            file.write((const char*) &tmp, sizeof(CompressedNode));
        }
    }
}

void writeArrayInFile(ofstream& file,const BitSet& result)
{
    int codeSize = result.getCurrentIndex();
    const uchar* data = result.getData();
    file.write((const char*) &codeSize, sizeof(int));
    file.write((const char*)data, (codeSize / 8 + 1) * sizeof(uchar));
}

void writeBinaryFile(const char* filename, HuffmanTree& tree, BitSet& result)
{
    ofstream file(filename, ios::binary);
    if(!file)
        throw "Cannot create result file!";

    int numbOfLeaves = tree.getNumbOfLeaves();

    file.write((const char*) &numbOfLeaves, sizeof(int));
    writeLeavesInFile(file, tree);
    writeArrayInFile(file, result);

    file.close();

}


void Compress(const char* filepath)
{
    ifstream file(filepath);
    if(!file)
        throw "Cannot open file !";

    HuffmanTree tree(file);

    BitSet result;
    FillBitSet(file, result, tree);

    writeBinaryFile("compressed", tree, result);
}



#endif // COMPRESSFILE_H_INCLUDED
