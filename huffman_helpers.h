#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <queue>
#include <utility>
#include <fstream>
#include <bitset>
#include <cstdlib>
#include <string>
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
