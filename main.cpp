// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <utility>


using namespace std;
template < class T > class lstdTreeNode
{
public:
	lstdTreeNode()
	{

	}

	lstdTreeNode(const T& t)
	{
		this->t = t;
	}

	virtual ~lstdTreeNode()
	{

	}

	void addChild(const T& t)
	{
		this->children.push_back(lstdTreeNode(t));
	}

	// remove a child by value, note: if the node has multiple children with the same value, this will only delete the first child
	void removeChild(const T& t)
	{
		for (unsigned int i = 0; i < this->children.size(); ++i)
		{
			if (this->children.at(i).t == t)
			{
				this->children.erase(this->children.begin() + i);
				return;
			}
		}
	}

	void removeChildByIndex(const int index)
	{
		this->children.erase(this->children.begin() + index);
	}

	void setValue(const T& t)
	{
		this->t = t;
	}

	T& getValue()
	{
		return this->t;
	}

	const T& getValue() const
	{
		return this->t;
	}

	std::vector< lstdTreeNode >& getChildren()
	{
		return this->children;
	}

	const std::vector< lstdTreeNode >& getChildren() const
	{
		return this->children;
	}

	// the type has to have an overloaded std::ostream << operator for print to work
	void print(const int depth = 0) const
	{
		for (int i = 0; i < depth; ++i)
		{
			if (i != depth - 1) std::cout << "    ";
			else std::cout << "|-- ";
		}
		std::cout << this->t << std::endl;
		for (unsigned int i = 0; i < this->children.size(); ++i)
		{
			this->children.at(i).print(depth + 1);
		}
	}

private:
	T t;
	std::vector< lstdTreeNode > children;
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
    string b = "Litwo, Ojczyzno moja! ty jestes jak zdrowie; Ile cie trzeba cenic, ten tylko sie dowie,Kto cie stracił. Dzis pieknosc twa w całej ozdobieWidze i opisuje, bo tesknie po tobie.Panno swieta, co Jasnej bronisz CzestochowyI w Ostrej swiecisz Bramie! Ty, co grod zamkowyNowogrodzki ochraniasz z jego wiernym ludem!Jak mnie dziecko do zdrowia powrociłas cudem(— Gdy od płaczacej matki, pod Twoja opiekeOfiarowany martwa podniosłem powieke;I zaraz mogłem pieszo, do Twych swiatyn proguIsc za wrocone zycie podziekowac Bogu —)Tak nas powrocisz cudem na Ojczyzny łono!...Tymczasem, przenos moja dusze utesknionaDo tych pagorkow lesnych, do tych łak zielonych,Szeroko nad błekitnym Niemnem rozciagnionych;Do tych pol malowanych zbozem rozmaitem,Wyzłacanych pszenica, posrebrzanych zytem;Gdzie bursztynowy swierzop, gryka jak snieg biała,Gdzie panienskim rumiencem dziecielina pała,A wszystko przepasane jakby wstega, miedzaZielona, na niej zrzadka ciche grusze siedza.";
    string a = "Tessse ";
    cout << a << '\n';
    sort(a.begin(),a.end());
    int aLen = a.length();
    map <char, double> dane;
    
    double suma = 0;
    for (int i = 0; i < aLen; i++)
    {
        dane[a[i]]++;
    }
    for (auto& it : dane) {
        dane[it.first] = it.second / aLen;
    }
    cout << endl << endl << suma << endl << endl;
    print_map(dane);

	// TODO użyć par do reprezentacji gałęzi drzewa

	lstdTreeNode <map<char, double> > tree(dane);
	

	//tree.print();



    return 1;
}
