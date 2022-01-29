#include "Helpers.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    string input_path, output_path, dic_path, mode;
    vector<string> arg(argv, argv + argc);

    
    if (validate_input_arguments(argc, arg) == -1) {
        return 0;
    }
    
    setPathByFlag(arg[1], arg[2], input_path, output_path, dic_path, mode);
    setPathByFlag(arg[3], arg[4], input_path, output_path, dic_path, mode);
    setPathByFlag(arg[5], arg[6], input_path, output_path, dic_path, mode);
    setPathByFlag(arg[7], arg[8], input_path, output_path, dic_path, mode);

   
    if (mode == "k")
    {
        HuffmanEncode(input_path, output_path, dic_path);
    }
    else if(mode == "d")
    {
        HuffmanDecode(input_path, output_path, dic_path);
    }
    else
    {
        cout << "==============================================================================="<< endl;
        cout << "Use correct format" << endl;
        cout << "For compressing data use:"<<endl;
        cout << "huffman-coding -i input_filename -o output_filename -s dictionary_filename -t k"<<endl;
        cout << "For decompressing data use:"<<endl;
        cout << "huffman-coding -i input_filename -o output_filename -s dictionary_filename -t d"<<endl;
        cout << "==============================================================================" << endl;
    }
    return 1;
}
