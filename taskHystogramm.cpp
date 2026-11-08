#include <iostream>
#include <string>
#include "structures/array.h"

using namespace std;

int main() {
    Array uniqueChars;
    
    cout << "Enter your text: ";
    string text;
    getline(cin, text);
    
    int counts[128] = {0};
    
    for (char c : text) {
        if (c != ' ' && c != '\n' && c != '\r') {
            int code = (int)c;
            if (counts[code] == 0) {
                uniqueChars.addEnd(string(1, c));
            }
            counts[code]++;
        }
    }
    
    if (uniqueChars.length() == 0) {
        cout << "No characters to display." << endl;
        return 0;
    }
    
    int maxHeight = 0;
    for (size_t i = 0; i < uniqueChars.length(); ++i) {
        char c = uniqueChars.get(i)[0];
        if (counts[(int)c] > maxHeight) {
            maxHeight = counts[(int)c];
        }
    }
    
    for (int h = maxHeight; h > 0; --h) {
        for (size_t i = 0; i < uniqueChars.length(); ++i) {
            char c = uniqueChars.get(i)[0];
            if (counts[(int)c] >= h) {
                cout << "#";
            } else {
                cout << " ";
            }
        }
        cout << "\n";
    }
    
    for (size_t i = 0; i < uniqueChars.length(); ++i) {
        cout << uniqueChars.get(i);
    }
    cout << "\n";
    
    return 0;
}