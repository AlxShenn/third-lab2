#include "storage.h"
#include <fstream>
#include <sstream>

using namespace std;

void SaveSets(const string& filename, map<string, HashSet<string>*>& sets) {
    ofstream f(filename);
    if (!f) return;

    for (auto& pair : sets) {
        string name = pair.first;
        HashSet<string>* s = pair.second;
        vector<string> elements = s->getAll();
        for (const string& val : elements) {
            f << name << " " << val << "\n";
        }
    }
}

void LoadSets(const string& filename, map<string, HashSet<string>*>& sets) {
    ifstream f(filename);
    if (!f) return;

    string setName, val;
    while (f >> setName >> val) {
        if (sets.find(setName) == sets.end()) {
            sets[setName] = new HashSet<string>();
        }
        sets[setName]->add(val);
    }
}