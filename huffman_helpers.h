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
    // result.append(8 - temp.size(), '0');
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
void output_dictionary(std::map<K, V> const &m, string filename, int zeros_added)
{
    ofstream plik;
    plik.open(filename + "_s.txt");
    plik << zeros_added << '\n';
    for (auto const &pair : m)
    {
        plik << int(pair.first) << " " << pair.second << '\n';
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

void createDictionary(WezelDrzewa *p, string prevstring = "", map<char, string> &slownik)
{
    if (p)
    {
        if (int(p->ch[0]) != 0)
        {
            slownik.insert(std::pair<char, string>(char(p->ch[0]), prevstring));
        }
        createDictionary(p->left, prevstring + "0");
        createDictionary(p->right, prevstring + "1");
    }
}

map<char, double> calculate_probability(string filename)
{
    int number_of_characters = 0;
    string line;
    map<char, double> dane;
    ifstream infile(filename + ".txt");
    while (getline(infile, line))
    {
        number_of_characters += line.length();
        for (int i = 0; i < line.length(); i++)
        {
            dane[line[i]]++;
        }
    }
    infile.close();
    //Calculate porbbability
    for (auto &it : dane)
    {
        dane[it.first] = it.second / number_of_characters;
    }
    return dane;
}

WezelDrzewa create_tree(map<char, double> chars_with_prob)
{
    vector<WezelDrzewa> elementyDoUtworzeniaDrzewa;
    for (auto const &pair : chars_with_prob)
    {
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
        WezelDrzewa *node1 = new WezelDrzewa(elementyDoUtworzeniaDrzewa.back());
        elementyDoUtworzeniaDrzewa.pop_back();
        WezelDrzewa *node2 = new WezelDrzewa(elementyDoUtworzeniaDrzewa.back());
        elementyDoUtworzeniaDrzewa.pop_back();

        WezelDrzewa x;
        x.ch = "";
        x.probability = node1->probability + node2->probability;
        if (node1->probability < node2->probability)
        {
            x.left = node1;
            x.right = node2;
        }
        else
        {
            x.left = node2;
            x.right = node1;
        }
        elementyDoUtworzeniaDrzewa.push_back(x);
        sort(elementyDoUtworzeniaDrzewa.begin(), elementyDoUtworzeniaDrzewa.end(), compareByProb);
    }
    return elementyDoUtworzeniaDrzewa.back();
}

pair<string, int> coded_message(map<char, string> dictionary, string filename)
{
    string huffman_coded_string = "";
    ifstream file(filename + ".txt");
    string line;
    while (getline(file, line))
    {
        for (int i = 0; i < line.length(); i++)
        {
            huffman_coded_string += dictionary[line[i]];
        }
    }
    file.close();

    int number_added_zeros = 8 - huffman_coded_string.length() % 8;
    if (number_added_zeros != 0)
    {
        for (int i = 0; i < number_added_zeros; i++)
        {
            huffman_coded_string += "0";
        }
    }
    pair<string, int> result(huffman_coded_string, number_added_zeros);
    return result;
}

void output_to_binary(string huffman_coded_string, string filename)
{
    string in = "";
    string part_of_string = "";
    ofstream compressed(filename + "_c.bin", ios::binary);
    for (int i = 1; i <= huffman_coded_string.length(); i++)
    {
        if (part_of_string.length() == 7)
        {
            part_of_string += huffman_coded_string[i - 1];
            in += (char)binary_to_decimal(part_of_string);
            part_of_string = "";
        }
        else
        {
            part_of_string += huffman_coded_string[i - 1];
        }
    }
    compressed.write(in.c_str(), in.size());
    compressed.close();
}