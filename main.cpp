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

string napis = "Litwo, Ojczyzno moja! ty jestes jak zdrowie; Ile cie trzeba cenic, ten tylko sie dowie,Kto cie straci�. Dzis pieknosc twa w ca�ej ozdobieWidze i opisuje, bo tesknie po tobie.Panno swieta, co Jasnej bronisz CzestochowyI w Ostrej swiecisz Bramie! Ty, co grod zamkowyNowogrodzki ochraniasz z jego wiernym ludem!Jak mnie dziecko do zdrowia powroci�as cudem(� Gdy od p�aczacej matki, pod Twoja opiekeOfiarowany martwa podnios�em powieke;I zaraz mog�em pieszo, do Twych swiatyn proguIsc za wrocone zycie podziekowac Bogu �)Tak nas powrocisz cudem na Ojczyzny �ono!...Tymczasem, przenos moja dusze utesknionaDo tych pagorkow lesnych, do tych �ak zielonych,Szeroko nad b�ekitnym Niemnem rozciagnionych;Do tych pol malowanych zbozem rozmaitem,Wyz�acanych pszenica, posrebrzanych zytem;Gdzie bursztynowy swierzop, gryka jak snieg bia�a,Gdzie panienskim rumiencem dziecielina pa�a,A wszystko przepasane jakby wstega, miedzaZielona, na niej zrzadka ciche grusze siedza.";
string b = "Tessse ";



struct WezelDrzewa
{
    struct WezelDrzewa* parent, * left, * right;
    string ch;
    double probability;
};

bool compareByProb(const WezelDrzewa& a, const WezelDrzewa& b)
{
    return a.probability > b.probability;
}


void writeBinaryTree(WezelDrzewa* p, ostream& out, string prevstring) {
    if (!p) {
        out << prevstring;
    }
    else {
        //out << p->ch << " ";
        out << "0";
        writeBinaryTree(p->left, out, p->ch);
        out << "1";
        writeBinaryTree(p->right, out, p->ch);
    }
}

template<typename K, typename V>
void print_map(std::map<K, V> const& m)
{
    for (auto const& pair : m) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
} 


int main()
{
    ofstream plik;
    WezelDrzewa * n, * x, * r;
    map <char, double> dane;
    vector < WezelDrzewa > elementyDoUtworzeniaDrzewa;

    plik.open("test.txt");
    sort(napis.begin(), napis.end());
    for (int i = 0; i < napis.length(); i++)
    {
        dane[napis[i]]++;
    }
    for (auto& it : dane) {
        dane[it.first] = it.second / napis.length();
    }



    // Inicjujemy nowy korzen
    n = new WezelDrzewa;
    n->parent = n->left = n->right = NULL;
    n->ch = "";
    n->probability = 0;



    for (auto const& pair : dane) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
        x = new WezelDrzewa;
        x->left = NULL;
        x->right = NULL;
        x->ch = pair.first;
        x->probability = pair.second;
        elementyDoUtworzeniaDrzewa.push_back(*x);
    }
    cout << endl;
    cout << endl;
   
    sort(elementyDoUtworzeniaDrzewa.begin(), elementyDoUtworzeniaDrzewa.end(), compareByProb);
    
    for (int i = 0; i < elementyDoUtworzeniaDrzewa.size(); i++)
    {
        cout << elementyDoUtworzeniaDrzewa.back().probability<<endl;
        elementyDoUtworzeniaDrzewa.pop_back();
    }

    while (elementyDoUtworzeniaDrzewa.size() > 1)
    {
        WezelDrzewa* kopia = new WezelDrzewa;
        *kopia = elementyDoUtworzeniaDrzewa.back();
        elementyDoUtworzeniaDrzewa.pop_back();
        WezelDrzewa* kopia2 = new WezelDrzewa;
        *kopia2 = elementyDoUtworzeniaDrzewa.back();
        elementyDoUtworzeniaDrzewa.pop_back(); 
        x = new WezelDrzewa;
        x->ch = "";
        x->probability = kopia->probability + kopia2->probability;
        if (kopia->probability < kopia2->probability)
        {
            x->left = kopia;
            x->right = kopia2;
        }
        else
        {
            x->left = kopia2;
            x->right = kopia;
        }
        elementyDoUtworzeniaDrzewa.push_back(*x);
        sort(elementyDoUtworzeniaDrzewa.begin(), elementyDoUtworzeniaDrzewa.end(), compareByProb);
    }
    WezelDrzewa* kopia = new WezelDrzewa;
    *kopia = elementyDoUtworzeniaDrzewa.back();


    writeBinaryTree(kopia , plik, "");

    
  
 //   print_map(dane);
    plik.close();
    return 1;
}
