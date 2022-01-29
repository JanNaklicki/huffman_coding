#include "Helpers.h"
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <fstream>
#include <bitset>
#include <cstdlib>
#include <string>
#include <algorithm>
using namespace std;

map<char, string> dictionary;


int validate_input_arguments(int argc, vector<string> &arg) {
    if (argc == 1 || arg[1] == "-h" || arg[1] == "--help") {
        cout << "User manual\n"
                "Usage:\n"
                "   -i(--input) input_filename \n"
                "   -o(--output) output_filename\n"
                "   -s(--slownik) slownik_filename \n"
                "   -t(--tryb) k - kompresja, d - dekompresja \n"
                "All four arguments are necessary to run program. For compression output file type should be .bin and for decompresion input should be .bin\n";
        return -1;
    }
    if (argc > 1 && argc != 9) {
        cout << argc;
        cout << "The number of arguments is not equal 4. Type '-h' and check manual\n";
        return -1;
    }
    if (arg[1] == arg[3]) {
        cout << "Can't use the same flag two times. Type '-h' and check manual\n";
        return -1;
    }
    if (arg[2] == arg[4]) {
        cout << "Can't use the same file for input and output. Type '-h' and check manual\n";
        return -1;
    }
    return 0;
}

void setPathByFlag(string& flag, string& path, string& input_path, string& output_path, string& dic_path, string& mode) {
    if (flag == "-i" || flag == "--input") {
        input_path = path;
    }
    else if (flag == "-o" || flag == "--output") {
        output_path = path;
    }
    else if (flag == "-s" || flag == "--slownik") {
        dic_path = path;
    }
    else if (flag == "-t" || flag == "--tryb") {
        mode = path;
    }
    else {
        cout << "Unknown flag. Type '-h' and check manual\n";
    }
}


int binary_to_decimal(string& in)
{
    int result = 0;
    for (int i = 0; i < (int)in.size(); i++)
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
    result.append(8 - temp.size(), '0');
    for (int i = temp.size() - 1; i >= 0; i--)
    {
        result += temp[i];
    }
    return result;
}

pair<string, char> split_string(string napis)
{
    pair<string, char> wynik;
    string znak = "";
    string kod = "";
    bool space = false;
    for (int i = 0; i < (int)napis.length(); i++)
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
    return wynik;
}

bool compare_by_prob(const WezelDrzewa& a, const WezelDrzewa& b)
{
    return a.probability > b.probability;
}

map<char, double> calculate_probability(string inputname)
{
    int number_of_characters = 0;
    string line;
    map<char, double> dane;
    ifstream infile(inputname);
    while (getline(infile, line))
    {
        number_of_characters += line.length();
        for (int i = 0; i < (int)line.length(); i++)
        {
            dane[line[i]]++;
        }
        dane['\n']++;
    }
    infile.close();
    for (auto& it : dane)
    {
        dane[it.first] = it.second / number_of_characters;
    }
    return dane;
}

void create_dictionary(WezelDrzewa* tree, map<char, string>& dictionary, string prevstring)
{
    if (tree)
    {
        if (int(tree->ch[0]) != 0)
        {
            dictionary.insert(std::pair<char, string>(char(tree->ch[0]), prevstring));
        }
        create_dictionary(tree->left, dictionary, prevstring + "0");
        create_dictionary(tree->right, dictionary, prevstring + "1");
    }
}

template <typename K, typename V>
void output_dictionary(map<K, V> const& m, string dicfile, int zeros_added)
{
    ofstream plik;
    plik.open(dicfile);
    plik << zeros_added << '\n';
    for (auto const& pair : m)
    {
        plik << int(pair.first) << " " << pair.second << '\n';
    }
    plik.close();
}

WezelDrzewa create_tree(map<char, double> chars_with_prob)
{
    vector<WezelDrzewa> elementyDoUtworzeniaDrzewa;
    for (auto const& pair : chars_with_prob)
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
        WezelDrzewa* node1 = new WezelDrzewa(elementyDoUtworzeniaDrzewa.back());
        elementyDoUtworzeniaDrzewa.pop_back();
        WezelDrzewa* node2 = new WezelDrzewa(elementyDoUtworzeniaDrzewa.back());
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
        sort(elementyDoUtworzeniaDrzewa.begin(), elementyDoUtworzeniaDrzewa.end(), compare_by_prob);
    }
    return elementyDoUtworzeniaDrzewa.back();
}

pair<string, int> coded_message(map<char, string> dictionary, string inputfile)
{
    string huffman_coded_string = "";
    ifstream file(inputfile);
    string line;
    while (getline(file, line))
    {
        for (int i = 0; i < (int)line.length(); i++)
        {
            huffman_coded_string += dictionary[line[i]];
        }
        huffman_coded_string += dictionary['\n'];
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

void output_to_binary(string huffman_coded_string, string outputfile)
{
    string in = "";
    string part_of_string = "";
    ofstream compressed(outputfile, ios::binary);
    for (int i = 1; i <= (int)huffman_coded_string.length(); i++)
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


// Decoding
pair<map<string, char>, int> load_dic_file(string dicFile)
{
    map<string, char> decoDic;
    string line, number = "";

    ifstream dict(dicFile);
    getline(dict, line);
    number.push_back(line[0]);

    int number_of_zeros_to_remove = stoi(number);

    while (getline(dict, line))
    {
        decoDic.insert(pair<string, char>(split_string(line).first, split_string(line).second));
    }
    dict.close();
    pair<map<string, char>, int> res(decoDic, number_of_zeros_to_remove);
    return res;
}

void decode_from_binary_to_text(map<string, char> decoDic, int number_of_zeros_to_remove, string inputname, string outputname)
{

    ifstream codedmessage(inputname, ifstream::in | ios::binary);
    string decodedmessage = "";
    vector<unsigned char> text;
    unsigned char textseg;
    codedmessage.read(reinterpret_cast<char*>(&textseg), 1);
    while (!codedmessage.eof())
    {
        text.push_back(textseg);
        codedmessage.read(reinterpret_cast<char*>(&textseg), 1);
    }
    codedmessage.close();
    for (int i = 0; i < (int)text.size(); i++)
    {
        decodedmessage += decimal_to_binary(text[i]);
    }

    ofstream decoded_message_file(outputname);
    string ciag = "";
    map<string, char>::iterator it;
    for (int i = 0; i < (int)decodedmessage.length() - number_of_zeros_to_remove; i++)
    {
        ciag += decodedmessage[i];
        it = decoDic.find(ciag);
        if (it != decoDic.end())
        {
            decoded_message_file << it->second;
            ciag = "";
        }
    }
    decoded_message_file.close();
   
}

void HuffmanEncode(string inputname, string outputname, string dicfile)
{
    map<char, double> chars_with_prob = calculate_probability(inputname);
    WezelDrzewa* prepared_tree = new WezelDrzewa(create_tree(chars_with_prob));
    map<char, string> dictionary;

    create_dictionary(prepared_tree, dictionary, "");
    pair<string, int> data_for_output = coded_message(dictionary, inputname);

    output_to_binary(data_for_output.first, outputname);
    output_dictionary(dictionary, dicfile, data_for_output.second);
}

void HuffmanDecode(string inputname, string outputname, string dictionary)
{
    pair<map<string, char>, int> dictionary_data = load_dic_file(dictionary);
    decode_from_binary_to_text(dictionary_data.first, dictionary_data.second, inputname ,outputname);
}
