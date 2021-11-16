#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    string a = "Litwo, Ojczyzno moja! ty jestes jak zdrowie;Ile cie trzeba cenic, ten tylko sie dowie,Kto cie stracił. Dzis pieknosc twa w całej ozdobieWidze i opisuje, bo tesknie po tobie.Panno swieta, co Jasnej bronisz CzestochowyI w Ostrej swiecisz Bramie! Ty, co grod zamkowyNowogrodzki ochraniasz z jego wiernym ludem!Jak mnie dziecko do zdrowia powrociłas cudem(— Gdy od płaczacej matki, pod Twoja opiekeOfiarowany martwa podniosłem powieke;I zaraz mogłem pieszo, do Twych swiatyn proguIsc za wrocone zycie podziekowac Bogu —)Tak nas powrocisz cudem na Ojczyzny łono!...Tymczasem, przenos moja dusze utesknionaDo tych pagorkow lesnych, do tych łak zielonych,Szeroko nad błekitnym Niemnem rozciagnionych;Do tych pol malowanych zbozem rozmaitem,Wyzłacanych pszenica, posrebrzanych zytem;Gdzie bursztynowy swierzop, gryka jak snieg biała,Gdzie panienskim rumiencem dziecielina pała,A wszystko przepasane jakby wstega, miedzaZielona, na niej zrzadka ciche grusze siedza.";
    cout << a << '\n';
    sort(a.begin(),a.end());
    


    int aLen = a.length();
    vector < pair <int, char>> dane;
    dane.push_back(make_pair(1, a[0]));

    for (int i = 1; i < aLen; i++)
    {
        if (dane.back().second == a[i])
        {
            dane.back().first++;
        }
        else
        {
            dane.push_back(make_pair(1, a[i]));
        }
    }
    double suma = 0;
    sort(dane.begin(), dane.end());
    for (int i = 0; i < dane.size(); i++)
    {
        cout << dane.at(i).first << " " << "'"<< dane.at(i).second <<"'" << " Prawdopodobienstwo: " << dane.at(i).first / double(aLen) << '\n';
        suma += dane.at(i).first / double(aLen);
    }
    cout << '\n' << "Checksum " << suma<<'\n';
     


    return 1;
}