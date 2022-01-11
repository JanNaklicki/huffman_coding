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
map<char, string> slownik;

string napis = "123456789";
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

void writeBinaryTree(WezelDrzewa *p, ostream &out, string prevstring)
{
    if (p)
    {
        if (int(p->ch[0]) != 0)
        {
            cout << "asci number: " << int(p->ch[0]) << " kod do znaku " << prevstring << "   Znak: " << p->ch << endl;
            slownik.insert(std::pair<char, string>(char(p->ch[0]), prevstring));
        }

        writeBinaryTree(p->left, out, prevstring + "0");
        writeBinaryTree(p->right, out, prevstring + "1");
    }
}

template <typename K, typename V>
void print_map(std::map<K, V> const &m)
{
    for (auto const &pair : m)
    {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

int main()
{
    ofstream plik;
    // WezelDrzewa *n, *x, *r;
    map<char, double> dane;
    vector<WezelDrzewa> elementyDoUtworzeniaDrzewa;

    plik.open("test.txt");

    sort(napis.begin(), napis.end());
    for (int i = 0; i < napis.length(); i++)
    {
        dane[napis[i]]++;
    }
    for (auto &it : dane)
    {
        dane[it.first] = it.second / napis.length();
    }
    for (auto const &pair : dane)
    {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
        WezelDrzewa x;
        x.left = NULL;
        x.right = NULL;
        x.ch = pair.first;
        x.probability = pair.second;
        elementyDoUtworzeniaDrzewa.push_back(x);
    }
    cout << endl;
    cout << endl;
    sort(elementyDoUtworzeniaDrzewa.begin(), elementyDoUtworzeniaDrzewa.end(), compareByProb);

    for (int i = 0; i < elementyDoUtworzeniaDrzewa.size(); i++)
    {
        cout << elementyDoUtworzeniaDrzewa[i].probability << endl;
    }

    cout << endl;
    cout << endl;

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
    writeBinaryTree(kopia, plik, "");
    // print_map(dane);
    plik.close();
    return 1;
}
