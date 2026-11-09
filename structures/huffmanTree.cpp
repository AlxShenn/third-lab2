#include "huffmanTree.h"

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
    Array freqsStr;

    for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];
        int idx = findCharIndex(uniqueChars, c);
        if (idx == -1) {
            uniqueChars.addEnd(string(1, c));
            freqsStr.addEnd("1");
        } else {
            int currentFreq = stoi(freqsStr.get(idx));
            freqsStr.set(idx, to_string(currentFreq + 1));
        }
    }

    Array nodesPool;
    Dlist freqList;
    DInitialize(freqList);

    for (size_t i = 0; i < uniqueChars.length(); ++i) {
        HuffmanNode* newNode = new HuffmanNode(uniqueChars.get(i)[0], stoi(freqsStr.get(i)));
        nodesPool.addEnd(to_string(reinterpret_cast<uintptr_t>(newNode)));
        DPushTail(freqList, freqsStr.get(i));
    }

    while (freqList.head != nullptr && freqList.head->next != nullptr) {
        int min1Idx = -1, min2Idx = -1;
        int min1Freq = 1e9, min2Freq = 1e9;
        int currentIdx = 0;

        for (DlistNode* cur = freqList.head; cur != nullptr; cur = cur->next) {
            int f = stoi(cur->text);
            if (f < min1Freq) {
                min2Freq = min1Freq;
                min2Idx = min1Idx;
                min1Freq = f;
                min1Idx = currentIdx;
            } else if (f < min2Freq) {
                min2Freq = f;
                min2Idx = currentIdx;
            }
            currentIdx++;
        }

        HuffmanNode* node1 = reinterpret_cast<HuffmanNode*>(stoull(nodesPool.get(min1Idx)));
        HuffmanNode* node2 = reinterpret_cast<HuffmanNode*>(stoull(nodesPool.get(min2Idx)));

        HuffmanNode* parent = new HuffmanNode('\0', node1->freq + node2->freq);
        parent->left = node1;
        parent->right = node2;

        if (min1Idx > min2Idx) swap(min1Idx, min2Idx);
        
        nodesPool.set(min1Idx, "0");
        nodesPool.set(min2Idx, "0");

        DDeleteValue(freqList, to_string(node1->freq));
        DDeleteValue(freqList, to_string(node2->freq));

        nodesPool.addEnd(to_string(reinterpret_cast<uintptr_t>(parent)));
        DPushTail(freqList, to_string(parent->freq));
    }

    if (freqList.head != nullptr) {
        for (size_t i = 0; i < nodesPool.length(); ++i) {
            if (nodesPool.get(i) != "0") {
                root = reinterpret_cast<HuffmanNode*>(stoull(nodesPool.get(i)));
                break;
            }
        }
        if (root) {
            generateCodes(root, "");
        }
    }

    DFree(freqList);
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