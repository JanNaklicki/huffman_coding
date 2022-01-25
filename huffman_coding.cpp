#include "huffman_helpers.h"

void HuffmanEncode(string filename)
{
    int input_length = 0;
    map<char, double> dane;
    vector<WezelDrzewa> elementyDoUtworzeniaDrzewa;
    string line;
    string compressed_string = "";
    ifstream infile(filename + ".txt");
    map<char, string> slownik;
    //Put input characters into map
    while (getline(infile, line))
    {
        input_length += line.length();
        for (int i = 0; i < line.length(); i++)
        {
            dane[line[i]]++;
        }
    }
    //Calculate porbbability
    for (auto &it : dane)
    {
        dane[it.first] = it.second / input_length;
    }
    //Convert characters with prob to tree nodes
    for (auto const &pair : dane)
    {
        // std::cout << "{" << pair.first << ": " << pair.second << "}\n";
        WezelDrzewa x;
        x.left = NULL;
        x.right = NULL;
        x.ch = pair.first;
        x.probability = pair.second;
        elementyDoUtworzeniaDrzewa.push_back(x);
    }
    //Create tree from nodes
    while (elementyDoUtworzeniaDrzewa.size() > 1)
    {
        WezelDrzewa *kopia = new WezelDrzewa;
        *kopia = elementyDoUtworzeniaDrzewa.back();
        elementyDoUtworzeniaDrzewa.pop_back();
        WezelDrzewa *kopia2 = new WezelDrzewa;
        *kopia2 = elementyDoUtworzeniaDrzewa.back();
        elementyDoUtworzeniaDrzewa.pop_back();

        WezelDrzewa x;
        x.ch = "";
        x.probability = kopia->probability + kopia2->probability;
        if (kopia->probability < kopia2->probability)
        {
            x.left = kopia;
            x.right = kopia2;
        }
        else
        {
            x.left = kopia2;
            x.right = kopia;
        }
        elementyDoUtworzeniaDrzewa.push_back(x);
        sort(elementyDoUtworzeniaDrzewa.begin(), elementyDoUtworzeniaDrzewa.end(), compareByProb);
    }
    WezelDrzewa *kopia = new WezelDrzewa;
    *kopia = elementyDoUtworzeniaDrzewa.back();
    // Create dictionary
    createDictionary(kopia);
    // Compress message
    ifstream file(filename + ".txt");
    while (getline(file, line))
    {
        input_length += line.length();
        for (int i = 0; i < line.length(); i++)
        {
            compressed_string += slownik[line[i]];
        }
    }
    file.close();
    int added_zeros = 8 - compressed_string.length() % 8;
    // cout << added_zeros << endl;
    if (added_zeros != 0)
    {
        for (int i = 0; i < added_zeros; i++)
        {
            compressed_string += "0";
        }
    }
    string in = "";
    string part_of_string = "";
    // cout << compressed_string << endl;
    ofstream compressed(filename + "_c.bin", ios::binary);
    for (int i = 1; i <= compressed_string.length(); i++)
    {
        if (part_of_string.length() == 7)
        {
            part_of_string += compressed_string[i - 1];
            // bitset<8> bits(part_of_string);
            // cout << part_of_string.length() << "  " << part_of_string << " " << bits << "  " << compressed_string.length() << " " << i << endl;
            in += (char)binary_to_decimal(part_of_string);
            part_of_string = "";
        }
        else
        {
            part_of_string += compressed_string[i - 1];
            // cout << part_of_string << endl;
        }
    }
    compressed.write(in.c_str(), in.size());
    cout << in;
    int number_of_bytes = compressed_string.length() / 8;
    compressed.close();
    writeDic(slownik, filename, added_zeros, number_of_bytes);
}

int main(int argc, char **argv)
{
     if(argc != 3)
    {
        cout<< "huffman_decoding e file";
    }
    else
    {
        HuffmanEncode(argv[2]);
    }
    return 1;
}