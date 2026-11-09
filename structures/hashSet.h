#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <string>
#include "array.h" 
#include "dlist.h"

using namespace std;

struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char character, int frequency) 
        : ch(character), freq(frequency), left(nullptr), right(nullptr) {}
};

class HuffmanCoder {
private:
    HuffmanNode* root;
    Array chars;
    Array codes;

    void generateCodes(HuffmanNode* node, string code);
    void deleteTree(HuffmanNode* node);

public:
    HuffmanCoder();
    ~HuffmanCoder();

    void buildTree(const string& text);
    string encode(const string& text);
    string decode(const string& encodedText);
    void printCodes() const;
};

#endif