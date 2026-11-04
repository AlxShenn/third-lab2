#include <iostream>
#include <string>
#include "structures/huffmanTree.h"

using namespace std;

int main() {
    cout << "Huffman Algorithm" << endl;
    
    string text;
    cout << "Enter string to encode: ";
    getline(cin, text);

    if (text.empty()) {
        cout << "Empty string." << endl;
        return 0;
    }

    HuffmanCoder coder;

    coder.buildTree(text);

    cout << "\n Codes Table " << endl;
    coder.printCodes();

    string encoded = coder.encode(text);
    cout << "\nEncoded string:\n" << encoded << endl;

    string decoded = coder.decode(encoded);
    cout << "\nDecoded string:\n" << decoded << endl;

    if (decoded == text) {
        cout << "\n Decoded text matches the original!" << endl;
    } else {
        cout << "\n Decoded text does NOT match!" << endl;
    }

    return 0;
}