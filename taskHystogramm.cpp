#include <iostream>
#include <string>
#include "structures/array.h"

using namespace std;

int utf8CharLen(unsigned char c) {
    if (c < 0x80) return 1;
    if ((c & 0xE0) == 0xC0) return 2;
    if ((c & 0xF0) == 0xE0) return 3;
    if ((c & 0xF8) == 0xF0) return 4;
    return 1;
}

int main() {
    Array uniqueChars;
    int* counts = nullptr;
    size_t uniqueCount = 0;
    size_t countsCapacity = 0;

    cout << "Enter your text: ";
    string text;
    getline(cin, text);

    size_t i = 0;
    while (i < text.size()) {
        int len = utf8CharLen((unsigned char)text[i]);
        if (i + len > text.size()) len = 1;
        string ch = text.substr(i, len);
        i += len;

        if (ch == " " || ch == "\n" || ch == "\r") continue;

        bool found = false;
        for (size_t k = 0; k < uniqueCount; ++k) {
            if (uniqueChars.get(k) == ch) {
                counts[k]++;
                found = true;
                break;
            }
        }

        if (!found) {
            uniqueChars.addEnd(ch);

            if (uniqueCount == countsCapacity) {
                size_t newCap = (countsCapacity == 0) ? 4 : countsCapacity * 2;
                int* newCounts = new int[newCap];
                for (size_t k = 0; k < uniqueCount; ++k) newCounts[k] = counts[k];
                delete[] counts;
                counts = newCounts;
                countsCapacity = newCap;
            }
            counts[uniqueCount] = 1;
            uniqueCount++;
        }
    }

    if (uniqueCount == 0) {
        cout << "No characters to display." << endl;
        delete[] counts;
        return 0;
    }

    for (size_t a = 1; a < uniqueCount; ++a) {
        string keyCh = uniqueChars.get(a);
        int keyCnt = counts[a];
        size_t b = a;
        while (b > 0 && uniqueChars.get(b - 1) > keyCh) {
            uniqueChars.set(b, uniqueChars.get(b - 1));
            counts[b] = counts[b - 1];
            b--;
        }
        uniqueChars.set(b, keyCh);
        counts[b] = keyCnt;
    }

    int maxHeight = 0;
    for (size_t k = 0; k < uniqueCount; ++k) {
        if (counts[k] > maxHeight) maxHeight = counts[k];
    }

    for (int h = maxHeight; h > 0; --h) {
        for (size_t k = 0; k < uniqueCount; ++k) {
            cout << (counts[k] >= h ? "#" : " ");
        }
        cout << "\n";
    }

    for (size_t k = 0; k < uniqueCount; ++k) {
        cout << uniqueChars.get(k);
    }
    cout << "\n";

    delete[] counts;
    return 0;
}