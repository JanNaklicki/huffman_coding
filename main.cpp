// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <utility>
using namespace std;

string b = "Litwo, Ojczyzno moja! ty jestes jak zdrowie; Ile cie trzeba cenic, ten tylko sie dowie,Kto cie straci�. Dzis pieknosc twa w ca�ej ozdobieWidze i opisuje, bo tesknie po tobie.Panno swieta, co Jasnej bronisz CzestochowyI w Ostrej swiecisz Bramie! Ty, co grod zamkowyNowogrodzki ochraniasz z jego wiernym ludem!Jak mnie dziecko do zdrowia powroci�as cudem(� Gdy od p�aczacej matki, pod Twoja opiekeOfiarowany martwa podnios�em powieke;I zaraz mog�em pieszo, do Twych swiatyn proguIsc za wrocone zycie podziekowac Bogu �)Tak nas powrocisz cudem na Ojczyzny �ono!...Tymczasem, przenos moja dusze utesknionaDo tych pagorkow lesnych, do tych �ak zielonych,Szeroko nad b�ekitnym Niemnem rozciagnionych;Do tych pol malowanych zbozem rozmaitem,Wyz�acanych pszenica, posrebrzanych zytem;Gdzie bursztynowy swierzop, gryka jak snieg bia�a,Gdzie panienskim rumiencem dziecielina pa�a,A wszystko przepasane jakby wstega, miedzaZielona, na niej zrzadka ciche grusze siedza.";
string napis = "Tessse ";


struct WezelDrzewa
{
    struct WezelDrzewa* parent, * left, * right;
    char ch;
    double probability;
};


template<typename K, typename V>
void print_map(std::map<K, V> const& m)
{
    for (auto const& pair : m) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}




int main()
{

    WezelDrzewa* n, * x, * r;
    map <char, double> dane;
    vector<WezelDrzewa> elementyDoPoloczenia;

    sort(napis.begin(), napis.end());
    int IloscLiter = napis.length();


    for (int i = 0; i < IloscLiter; i++)
    {
        dane[napis[i]]++;
    }
    for (auto& it : dane) {
        dane[it.first] = it.second / IloscLiter;
    }

    // Inicjujemy nowy korzen
    n = new WezelDrzewa;
    n->parent = n->left = n->right = NULL;
    n->ch = NULL;


    for (auto const& pair : dane) {

        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
        x = new WezelDrzewa;
        x->left = NULL;
        x->right = NULL;
        x->ch = pair.first;
        x->probability = pair.second;


        elementyDoPoloczenia.push_back(*x);
    }

    //cout << elementyDoPoloczenia.begin();
  
 //   print_map(dane);
 
    return 1;
}
