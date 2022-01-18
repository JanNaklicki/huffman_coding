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

using namespace std;
string napis = "cba";
map<char, string> slownik;
struct WezelDrzewa
{
    struct WezelDrzewa *parent, *left, *right;
    string ch;
    double probability;
};
bool compareByProb(const WezelDrzewa &a, const WezelDrzewa &b)
{
    return a.probability > b.probability;
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
template <typename K, typename V>
void print_map(std::map<K, V> const &m, string filename)
{
    ofstream plik;
    plik.open(filename + "_s.txt");
    for (auto const &pair : m)
    {
        plik << int(pair.first) << " " << pair.second << '\n';
        // std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
    plik.close();
}

void HuffmanEncode(string filename)
{
    int input_length = 0;
    map<char, double> dane;
    vector<WezelDrzewa> elementyDoUtworzeniaDrzewa;
    string line;
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
    ofstream compressed(filename + "_c.txt");
    ifstream file(filename + ".txt");
    while (getline(file, line))
    {
        input_length += line.length();
        for (int i = 0; i < line.length(); i++)
        {
            compressed << slownik[line[i]];
        }
    }
    compressed.close();
    file.close();
    print_map(slownik, filename);
}
void HuffmanDecode(string decFile, string dicFile)
{
    pair<string, char> dane;
    map<string, char> decoDic;
    map<string, char>::iterator it;

    ifstream dict(dicFile + ".txt");
    string line;
    while (getline(dict, line))
    {
        // cout << splitString(line).first << " " << splitString(line).second << endl;
        decoDic.insert(pair<string, char>(splitString(line).first, splitString(line).second));
    }
    dict.close();
    ifstream codedmessage(decFile + ".txt");
    ofstream decodedmessage(decFile + "_d.txt");
    while (getline(codedmessage, line))
    {
        string ciag = "";
        for (int i = 0; i < line.length(); i++)
        {
            ciag += line[i];
            it = decoDic.find(ciag);
            if (it != decoDic.end())
            {
                decodedmessage << it->second;
                ciag = "";
            }
        }
    }
    decodedmessage.close();
    codedmessage.close();
}
int main(int argc, char **argv)
{
    // HuffmanEncode();
    cout << argv[2];
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
