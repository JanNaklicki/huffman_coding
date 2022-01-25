#include "huffman_helpers.h"

void HuffmanEncode(string filename)
{
    map<char, double> chars_with_prob = calculate_probability(filename);
    WezelDrzewa *prepared_tree = new WezelDrzewa(create_tree(chars_with_prob)); // *tree_copy = create_tree(chars_with_prob);
    map<char, string> dictionary;
    createDictionary(prepared_tree, "", dictionary);
    pair<string, int> data_for_output = coded_message(dictionary, filename);
    output_to_binary(data_for_output.first, filename);
    output_dictionary(dictionary, filename, data_for_output.second);
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Use correct format" << endl;
        cout << "huffman_decoding e file_name";
    }
    else
    {
        HuffmanEncode(argv[2]);
    }
    return 1;
}