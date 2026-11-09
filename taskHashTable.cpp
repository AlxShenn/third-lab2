#include <iostream>
#include <string>
#include "structures/hashSet.h"
#include "structures/cuckooHash.h"

using namespace std;

bool areIsomorphicChaining(const string& a, const string& b) {
    if (a.length() != b.length()) return false;

    HashSet<string> mapAB;
    HashSet<string> mapBA;

    for (size_t i = 0; i < a.length(); ++i) {
        string sA(1, a[i]);
        string sB(1, b[i]);
        
        string mapping = sA + "->" + sB;

        if (mapAB.contains(mapping)) {
            continue;
        }

        if (mapAB.contains(sA) || mapBA.contains(sB)) {
            return false;
        }

        mapAB.add(mapping);
        mapAB.add(sA);
        mapBA.add(sB);
    }
    return true;
}

bool areIsomorphicCuckoo(const string& a, const string& b) {
    if (a.length() != b.length()) return false;

    CuckooHash<string> mapAB;
    CuckooHash<string> mapBA;

    for (size_t i = 0; i < a.length(); ++i) {
        string sA(1, a[i]);
        string sB(1, b[i]);
        
        string mapping = sA + "->" + sB;

        if (mapAB.contains(mapping)) {
            continue;
        }
        
        if (mapAB.contains(sA) || mapBA.contains(sB)) {
            return false;
        }

        mapAB.add(mapping);
        mapAB.add(sA);
        mapBA.add(sB);
    }
    return true;
}

int main() {
    cout << " Isomorphic Strings " << endl;
    
    string a, b;
    cout << "Enter string A: ";
    cin >> a;
    cout << "Enter string B: ";
    cin >> b;

    cout << "\n--- Method 1: Chaining ---" << endl;
    if (areIsomorphicChaining(a, b)) {
        cout << "Result: ISOMORPHIC" << endl;
    } else {
        cout << "Result: NOT ISOMORPHIC" << endl;
    }

    cout << "\n--- Method 2: Cuckoo Hashing ---" << endl;
    if (areIsomorphicCuckoo(a, b)) {
        cout << "Result: ISOMORPHIC" << endl;
    } else {
        cout << "Result: NOT ISOMORPHIC" << endl;
    }

    return 0;
}