#include "huffman_helpers.h"
void HuffmanDecode(string decFile, string dicFile)
{
    pair<string, char> dane;
    map<string, char> decoDic;
    map<string, char>::iterator it;

    ifstream dict(dicFile + ".txt");
    string line;
    int number_of_zeros_to_remove;
    getline(dict, line);
    string number = "";
    number.push_back(line[0]);
    number_of_zeros_to_remove = stoi(number);
    getline(dict, line);
    int number_of_bytes = stoi(line);
    while (getline(dict, line))
    {
        decoDic.insert(pair<string, char>(splitString(line).first, splitString(line).second));
    }
    dict.close();
    // tu działa

    ifstream codedmessage(decFile + ".bin", ifstream::in);
    string decodedmessage = "";
    vector<unsigned char> text;
    unsigned char textseg;
    codedmessage.read(reinterpret_cast<char *>(&textseg), 1);
    while (!codedmessage.eof())
    {
        text.push_back(textseg);
        codedmessage.read(reinterpret_cast<char *>(&textseg), 1);
    }
    for (int i = 0; i < text.size(); i++)
    {
        decodedmessage += decimal_to_binary(text[i]);
    }

    ofstream decoded_message_file(decFile + "_d.txt");
    string ciag = "";
    for (int i = 0; i < decodedmessage.length() - number_of_zeros_to_remove; i++)
    {
        ciag += decodedmessage[i];
        it = decoDic.find(ciag);
        if (it != decoDic.end())
        {
            decoded_message_file << it->second;
            // cout << ciag << " ";
            ciag = "";
        }
    }
    decoded_message_file.close();
    codedmessage.close();
}
    map<char, string> slownik;
int main(int argc, char **argv)
{
    if(argc != 4)
    {
        cout<< "huffman_decoding d file dictionary";
    }
    else
    {
        HuffmanDecode(argv[2], argv[3]);
    }
}