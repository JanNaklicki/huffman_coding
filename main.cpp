// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <queue>
#include <utility>
#include <fstream>
#include <bitset>

using namespace std;
int binary_to_decimal(string &in)
{
    int result = 0;
    for (int i = 0; i < in.size(); i++)
        result = result * 2 + in[i] - '0';
    return result;
}
string decimal_to_binary(int in)
{
    string temp = "";
    string result = "";
    while (in)
    {
        temp += ('0' + in % 2);
        in /= 2;
    }
    result.append(8 - temp.size(), '0'); //append '0' ahead to let the result become fixed length of 8
    for (int i = temp.size() - 1; i >= 0; i--)
    {
        result += temp[i];
    }
    return result;
}
map<char, string> slownik;
struct WezelDrzewa
{
    struct WezelDrzewa *parent, *left, *right;
    string ch;
    double probability;
};
template <typename K, typename V>
void writeDic(std::map<K, V> const &m, string filename, int zeros_added, int number_of_bytes)
{
    // TODO: add number of zeros added
    ofstream plik;
    plik.open(filename + "_s.txt");
    plik << zeros_added << '\n';
    plik << number_of_bytes << '\n';
    for (auto const &pair : m)
    {
        plik << int(pair.first) << " " << pair.second << '\n';
        // std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
    plik.close();
}
pair<string, char> splitString(string napis)
{
    pair<string, char> wynik;
    string znak;
    string kod;
    bool space = false;
    for (int i = 0; i < napis.length(); i++)
    {
        if (napis[i] == ' ')
        {
            space = true;
            continue;
        }
        if (!space)
        {
            znak += napis[i];
        }
        else
        {
            kod += napis[i];
        }
    }
    wynik.second = char(stoi(znak));
    wynik.first = kod;
    // cout << wynik.first << endl;
    // cout << kod;
    return wynik;
}
bool compareByProb(const WezelDrzewa &a, const WezelDrzewa &b)
{
    return a.probability > b.probability;
}
void createDictionary(WezelDrzewa *p, string prevstring = "")
{
    if (p)
    {
        if (int(p->ch[0]) != 0)
        {
            // cout << "asci number: " << int(p->ch[0]) << " kod do znaku " << prevstring << "   Znak: " << p->ch << endl;
            slownik.insert(std::pair<char, string>(char(p->ch[0]), prevstring));
        }
        createDictionary(p->left, prevstring + "0");
        createDictionary(p->right, prevstring + "1");
    }
}
void HuffmanEncode(string filename)
{
    int input_length = 0;
    map<char, double> dane;
    vector<WezelDrzewa> elementyDoUtworzeniaDrzewa;
    string line;
    string compressed_string = "";
    ifstream infile(filename + ".txt");
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
void HuffmanDecode(string decFile, string dicFile)
{
    pair<string, char> dane;
    map<string, char> decoDic;
    map<string, char>::iterator it;

    ifstream dict(dicFile + ".txt");
    string line;
    int number_of_zeros_to_remove;
    getline(dict, line);
    string number = "";
    number.push_back(line[0]);
    number_of_zeros_to_remove = stoi(number);
    getline(dict, line);
    int number_of_bytes = stoi(line);
    while (getline(dict, line))
    {
        decoDic.insert(pair<string, char>(splitString(line).first, splitString(line).second));
    }
    dict.close();
    // tu działa

    ifstream codedmessage(decFile + ".bin", ifstream::in);
    string decodedmessage = "";
    vector<unsigned char> text;
    unsigned char textseg;
    codedmessage.read(reinterpret_cast<char *>(&textseg), 1);
    while (!codedmessage.eof())
    {
        text.push_back(textseg);
        codedmessage.read(reinterpret_cast<char *>(&textseg), 1);
    }
    for (int i = 0; i < text.size(); i++)
    {
        decodedmessage += decimal_to_binary(text[i]);
    }

    ofstream decoded_message_file(decFile + "_d.txt");
    string ciag = "";
    for (int i = 0; i < decodedmessage.length() - number_of_zeros_to_remove; i++)
    {
        ciag += decodedmessage[i];
        it = decoDic.find(ciag);
        if (it != decoDic.end())
        {
            decoded_message_file << it->second;
            // cout << ciag << " ";
            ciag = "";
        }
    }
    decoded_message_file.close();
    codedmessage.close();
}
int main(int argc, char **argv)
{
    // HuffmanEncode();
    if (*argv[1] == 'e' && argc == 3)
    {
        HuffmanEncode(argv[2]);
    }
    else if (*argv[1] == 'd' && argc == 4)
        HuffmanDecode(argv[2], argv[3]);
    else
    {
        cout << "Podaj poprawne parametry" << '\n';
        cout << "Kompresja: e nazwa_pilku" << '\n';
        cout << "Dekompresja: d nazwa_pliku nazwa_slownika";
    }

    return 1;
}
