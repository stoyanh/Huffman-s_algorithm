#include <iostream>
#include <fstream>
#include "HuffmanTree.h"
#include "MinHeap.h"
#include "DecompressFile.h"

using namespace std;

int main()
{
    const char* filepath = "/media/8A6C59386C591FED/C++_programs/SDP/project/Huffman-s_algorithm/huffman/compressed";
    try
    {
        Decompress(filepath);
    }
    catch(const char* str)
    {
        cout << str << endl;
    }
    catch(bad_alloc)
    {
        cout << "Cannot allocate memmory !";
    }
    return 0;
}
