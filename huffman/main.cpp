#include <iostream>
#include <fstream>
#include "MinHeap.h"
#include "HuffmanTree.h"
#include "CompressFile.h"
#include <ctime>

using namespace std;

int main()
{
    const clock_t begin_time = clock();
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
    std::cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC;
    return 0;
}
