#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <cctype>

#include "structures/hashset.h"
#include "structures/storage.h"

using namespace std;

void printHelp() {
    cout << "=== Hash Set Manager ===" << endl;
    cout << "Available commands:" << endl;
    cout << "  SETADD <set_name> <value>  - add element to set" << endl;
    cout << "  SETDEL <set_name> <value>  - remove element from set" << endl;
    cout << "  SET_AT <set_name> <value>  - check if element is in set" << endl;
    cout << "  HELP                       - show this message" << endl;
    cout << "  EXIT                       - save and quit" << endl;
    cout << "Example: SETADD set1 apple" << endl;
    cout << "=========================" << endl;
}

int main(int argc, char* argv[]) {
    string file = "data.txt";
    string query = "";

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) {
            file = argv[++i];
        } else if (arg == "--query" && i + 1 < argc) {
            query = argv[++i];
        }
    }
    
    map<string, HashSet<string>*> sets;
    LoadSets(file, sets);

    // Single query mode
    if (!query.empty()) {
        istringstream iss(query);
        string cmd, setName, val;
        if (iss >> cmd >> setName >> val) {
            if (sets.find(setName) == sets.end()) {
                sets[setName] = new HashSet<string>();
            }
            HashSet<string>* s = sets[setName];
            
            if (cmd == "SETADD") {
                s->add(val);
                cout << "Added " << val << " to " << setName << endl;
            } else if (cmd == "SETDEL") {
                if (s->remove(val)) cout << "Deleted " << val << " from " << setName << endl;
                else cout << "Not found " << val << " in " << setName << endl;
            } else if (cmd == "SET_AT") {
                if (s->contains(val)) cout << "Yes, " << val << " is in " << setName << endl;
                else cout << "No, " << val << " is not in " << setName << endl;
            } else {
                cout << "Unknown command: " << cmd << endl;
            }
        } else {
            cout << "Invalid query format. Use: SETADD <name> <value>" << endl;
        }
    } 
    // Interactive mode
    else {
        printHelp();
        
        string line;
        while (true) {
            cout << "> ";
            if (!getline(cin, line)) break; 
            
            if (line.empty()) continue;
            
            istringstream iss(line);
            string cmd, setName, val;
            if (!(iss >> cmd)) continue;
            
            // Convert command to uppercase
            for (char& c : cmd) c = toupper(c);
            
            if (cmd == "EXIT") {
                break;
            } else if (cmd == "HELP") {
                printHelp();
                continue;
            }
            
            if (!(iss >> setName >> val)) {
                cout << "Error: invalid command format. Type HELP." << endl;
                continue;
            }
            
            if (sets.find(setName) == sets.end()) {
                sets[setName] = new HashSet<string>();
            }
            HashSet<string>* s = sets[setName];
            
            if (cmd == "SETADD") {
                s->add(val);
                cout << "Added " << val << " to " << setName << endl;
            } else if (cmd == "SETDEL") {
                if (s->remove(val)) cout << "Deleted " << val << " from " << setName << endl;
                else cout << "Not found " << val << " in " << setName << endl;
            } else if (cmd == "SET_AT") {
                if (s->contains(val)) cout << "Yes, " << val << " is in " << setName << endl;
                else cout << "No, " << val << " is not in " << setName << endl;
            } else {
                cout << "Unknown command: " << cmd << ". Type HELP." << endl;
            }
        }
    }
    
    SaveSets(file, sets);

    for (auto& pair : sets) {
        delete pair.second;
    }
    
    cout << "Saved to " << file << ". Exiting." << endl;
    return 0;
}