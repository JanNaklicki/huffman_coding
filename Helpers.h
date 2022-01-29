#ifndef  HELPERS_H
#define HELPERS_H
#endif // ! HELPERS_H

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <fstream>
#include <bitset>
#include <cstdlib>
#include <string>
using namespace std;

int validate_input_arguments(int argc, vector<string> &arg);

void setPathByFlag(string& flag, string& path, string& input_path, string& output_path, string& dic_path, string& mode);

/** @struct WezelDrzewa
* @brief Struktura używana przy tworzeniu drzewa, przechowuje znak oraz prawdopodobieństwo jego wystąpienia w tekście. 
*
*/
struct WezelDrzewa
{
    /**
     * @brief rodzic węzła
     * 
     */
    struct WezelDrzewa* parent = NULL;
    /**
     * @brief lewe dziecko
     * 
     */
    struct WezelDrzewa * left = NULL;
    /**
     * @brief prawe dziecko
     * 
     */
    struct WezelDrzewa * right = NULL;
    /**
     * @brief znak 
     * 
     */
    string ch;
    double probability = NULL;
};

/**
 * Funkcja przyjmuje oktet, który zamienia z wartości binarnej na wartość dziesiętną. 
 * 
 * @param in 8 bitów zapisane jako string
 * @return int 
 */
int binary_to_decimal(string& in);

/**
 *  Funkcja zamienia liczbę z zapisu dziesiętnego na binarny.
 * 
 * @param in liczba do zamiany
 * @return string zwraca liczbę zapisaną binarnie
 */
string decimal_to_binary(int in);
/**
 *  Funkcja dzieli podany napis na dwie części po napotkaniu znaku spacji. 
 * 
 * @param napis wejściowy string zawierający dwie wartości oddzielone spacją
 * @return pair<string, char> zwraca dwie wartości: kod huffmana, znak ASCII zapisany jako int
 */
pair<string, char> split_string(string napis);
/**
 *  Funkcja pomagająca przy sortoaniu węzłów drzewa znajdujących się w wektorze porównująć prawdopodobieństwo.
 * 
 * @param a pierwsz węzeł drzewa
 * @param b drgi węzeł drzewa
 * @return true zwraca prawdę jeżeli prawdopodobieństwo zawarte w węźłe a jest większe
 * @return false 
 * @see WezelDrzewa
 */
bool compare_by_prob(const WezelDrzewa& a, const WezelDrzewa& b);
/**
 * Funkcja zapisuje wystąpienia znaków do mapy, aby na końcu podzielić ilość wystąpień znaku przez ilość wszystkich znaków w tekście. Otrzymujemy w ten sposób prawdopodobieństwo wystąpienia znaku.
 * 
 * @param filename nazwa pliku, z którego chcemy wczytać dane
 * @return map<char, double> mapa zawierająca znaki z prawdopodobieństwem ich wysąpienia
 */
map<char, double> calculate_probability(string inputname);

/**
 *  Struktura WezelDrzewa jest używana do tworzenia drzewa binarnego. 
 *  WezelDrzewa oprócz standardowych wartości, zawiera również wartość ch oraz probability, które kolejno oznaczają znak, oraz jego prawdopodobieństwo wystąpienia w tekście.
 */


/**
 * Funkcja reukrencyjnie przechodzi po drzewie tworząc kody huffmana dla poszczególnych znaków. Gdy nie ma możliwości przejścia do kolejnych potomków, utworzony kod(w zapisie binarnym) zostaje dodany jako element mapy, wraz ze znakiem, dla którego kod utworzono.
 * 
 * @param tree gotowe drzewo utworzone przez funkcje create_tree()
 * @param dictionary mapa do której mają zostać zapisane znaki oraz ich kody
 * @param prevstring zmienna pomocnicza, do które podczas rekurencji doklejane są zera i jedynki
 * @see create_tree()
 */
void create_dictionary(WezelDrzewa* tree, map<char, string>& dictionary, string prevstring);
/**
 * Funkcja wypisująca słownik(mapę) utworzony przez create_dictionary() do pliku.
 * 
 * @param m mapa z której pobieramy wartości
 * @param filename nazwa pliku 
 * @param zeros_added ilość zer dodana do ostatniego oktetu
 */
template <typename K, typename V>
void output_dictionary(map<K, V> const& m, string dicfile, int zeros_added);
/**
 *  Funkcja tworzy drzewo binarne. W pierwszym kroku wartości z mapy utworzonej przez calculate_probability() zamieniane są na WezelDrzewa i wkładane do wektora. Następnie wykorzustjąć węzły zawarte w wektorze zaczynamy budować drzewo. Bierzemy dwa elementy o najmniejszym prawdopodobieństwie i przypisujemy je do nowego WezelDrzewa jako jego dzieci. Następnie sortujemy wektor korzystając z compare_by_prob(). Te dwa korki powtarzamy, aż w wektorze zostanie nam jeden element, który będzie gotowym drzewem huffmana.
 * 
 * @param chars_with_prob mapa zawierająca znaki z prawdopodobieństwem wystąpienia w tekście
 * @return WezelDrzewa gotowe drzewo huffmana
 */
WezelDrzewa create_tree(map<char, double> chars_with_prob);
/**
 * Funkcja koduje dane z pliku wejściowego używając słownika stworzonego przez create_dictionary(). Po zakodowaniu wszystkich znaków sprawdza czy ilość zer i jedynek jest podzielna przez 8. Jeżeli nie to doklejamy odpowiednią ilość zer na koniec kodu.
 * 
 * @param dictionary słownik utworzony przez create_dictionary()
 * @param filename nazwa pliku
 * @return pair<string, int> para zawierająca zakodowany tekst oraz ilość zer dodanych do ostatniego oktetu
 */
pair<string, int> coded_message(map<char, string> dictionary, string inputfile);
/**
 * Funkcja przyjmuje zakodowaną wiadomość jako string. Następnie w pętli będziemy w pętli dzielić tekst na oktety, które zostaną zapisane jako znaki wpliku wyjściowym(.bin).
 * Do zamiany oktetu na char używamy binary_to_decimal()
 * @param huffman_coded_string zakodowane dane wejściowe w postaci zer i jedynek
 * @param filename nazwa pliku, do którego będziemy zapisywać dane w postaci binarnej
 */
void output_to_binary(string huffman_coded_string, string outputfile);
/**
 * Funckja wczytuje pierwszą linijkę z pliku, w której zapisano ilość zer dodaną do ostatniego oktetu wiadmości. Następnie wczytujemy kolejne linijki zawierjące znaki(zapiasne jako int) oraz ich odpowiedniki w kodzie huffmana. Te wartości wstawiamy do mapy, która będzie użyta do odkodowania danych.
 * 
 * @param dicFile nazwa pliku słownika
 * @return pair<map<string, char>, int> para zawierająca gotowy słownik, oraz liczbę zer dodaną do ostatnie oktetu 
 */
pair<map<string, char>, int> load_dic_file(string dicFile);
/**
 * Funkcja wczytuje po osiem bitów z pliku binarnego jako char. Następnie przy użyciu decimal_to_binary() chary zamieniane są na zera i jedynki i doklejone do stringa decodedmessage. W kolejnym kroku przy pomocy słownika decoDic dekodujemy zawartość decoded message i wypisujemy do pliku wyjściowego jako zdekompresowane dane.
 * 
 * @param decoDic słownik utworzony przez load_dic_file()  
 * @param number_of_zeros_to_remove ilość zer do usunięcia z ostatniego oktetu
 * @param inputname nazwa zkompresowanego pliku 
 * @param outputname nazwa pliku po dekompresji
 */
void decode_from_binary_to_text(map<string, char> decoDic, int number_of_zeros_to_remove, string inputname, string outputname);

/**
 * Funkcja kompresująca zawartość pliku. Tworzony jest zkompresowany plik, oraz słownik, który jest wymagany do dekompresji.
 * 
 * @param inputname nazwa pliku do kompresji
 * @param outputname nazwa pliku po kompresji
 * @param dicfile nazwa słownika
 */
void HuffmanEncode(string inputname, string outputname, string dicfile);
/**
 * Funkcja dekopresująca dane z podanego pliku. Żeby skorzystać z tej funkcji musimy podać nazwę pliku do dekompresji, oraz nazwę pliku zawierającego słownik.
 * 
 * @param inputname nazwa pliku do dekompresji
 * @param outputname nazwa pliku po dekompresji
 * @param dictionary nazwa pliku zawierająca słownik
 */
void HuffmanDecode(string inputname, string outputname, string dictionary);