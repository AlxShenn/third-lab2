#include "storage.h"
#include <fstream>
#include <sstream>

using namespace std;

void SaveSets(const string& filename, Slist& sets) {
    ofstream f(filename);
    if (!f) return;
    SlistNode* current = sets.head;
    while (current != nullptr) {
        string name = current->text;
        HashSet<string>* s = current->set;
        
        if (s != nullptr) {
            size_t count = s->getSize();
            string* elements = s->getAll();
            
            for (size_t i = 0; i < count; ++i) {
                f << name << " " << elements[i] << "\n";
            }
            
            delete[] elements;
        }
        current = current->next;
    }
}

void LoadSets(const string& filename, Slist& sets) {
    ifstream f(filename);
    if (!f) return;

    string setName, val;
    while (f >> setName >> val) {
        HashSet<string>* s = FGetOrCreateSet(sets, setName);
        s->add(val);
    }
}