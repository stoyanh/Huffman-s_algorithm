#include <iostream>
#include <fstream>
#include "MinHeap.h"
#include "HuffmanTree.h"
#include "CompressFile.h"


using namespace std;

int main()
{
    const char* filepath = "/media/8A6C59386C591FED/C++_programs/SDP/project/Huffman-s_algorithm/text";
    //cin.getline(filepath,99);

    try
    {
        Compress(filepath);
    }
    catch(const char* str)
    {
        cout << str << endl;
    }
    catch(bad_alloc)
    {
        cout << "Cannot allocate memory !" << endl;
    }

    return 0;
}
