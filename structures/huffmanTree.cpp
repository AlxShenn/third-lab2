#include "huffmanTree.h"
#include <vector>

HuffmanCoder::HuffmanCoder() : root(nullptr) {}

HuffmanCoder::~HuffmanCoder() {
    deleteTree(root);
}

void HuffmanCoder::deleteTree(HuffmanNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// Поиск индекса символа в нашем Array
int findCharIndex(const Array& arr, char c) {
    for (size_t i = 0; i < arr.length(); ++i) {
        if (arr.get(i)[0] == c) return (int)i;
    }
    return -1;
}

void HuffmanCoder::generateCodes(HuffmanNode* node, string code) {
    if (!node) return;

    if (!node->left && !node->right) {
        chars.addEnd(string(1, node->ch));
        codes.addEnd(code);
    }

    generateCodes(node->left, code + "0");
    generateCodes(node->right, code + "1");
}

void HuffmanCoder::buildTree(const string& text) {
    deleteTree(root);
    root = nullptr;
    chars = Array();
    codes = Array();

    if (text.empty()) return;

    Array uniqueChars;
    vector<int> freqs;

    for (char c : text) {
        int idx = findCharIndex(uniqueChars, c);
        if (idx == -1) {
            uniqueChars.addEnd(string(1, c));
            freqs.push_back(1);
        } else {
            freqs[idx]++;
        }
    }

    vector<HuffmanNode*> nodes;
    for (size_t i = 0; i < uniqueChars.length(); ++i) {
        nodes.push_back(new HuffmanNode(uniqueChars.get(i)[0], freqs[i]));
    }

    while (nodes.size() > 1) {
        int min1 = 0;
        int min2 = 1;

        if (nodes[min1]->freq > nodes[min2]->freq) swap(min1, min2);

        for (size_t i = 2; i < nodes.size(); ++i) {
            if (nodes[i]->freq < nodes[min1]->freq) {
                min2 = min1;
                min1 = i;
            } else if (nodes[i]->freq < nodes[min2]->freq) {
                min2 = i;
            }
        }

        HuffmanNode* left = nodes[min1];
        HuffmanNode* right = nodes[min2];

        HuffmanNode* parent = new HuffmanNode('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;


        if (min1 > min2) swap(min1, min2);
        nodes.erase(nodes.begin() + min2);
        nodes.erase(nodes.begin() + min1);
        
        nodes.push_back(parent);
    }

    if (!nodes.empty()) {
        root = nodes[0];
        generateCodes(root, "");
    }
}

string HuffmanCoder::encode(const string& text) {
    string encoded = "";
    for (char c : text) {
        int idx = findCharIndex(chars, c);
        if (idx != -1) {
            encoded += codes.get(idx);
        }
    }
    return encoded;
}

string HuffmanCoder::decode(const string& encodedText) {
    if (!root) return "";
    
    string decoded = "";
    HuffmanNode* current = root;
    
    for (char bit : encodedText) {
        if (bit == '0') current = current->left;
        else current = current->right;

        if (!current->left && !current->right) {
            decoded += current->ch;
            current = root;
        }
    }
    return decoded;
}

void HuffmanCoder::printCodes() const {
    for (size_t i = 0; i < chars.length(); ++i) {
        cout << "'" << chars.get(i) << "': " << codes.get(i) << endl;
    }
}