#include <iostream>
#include <sstream>
#include <string>
#include <cctype>

#include "structures/hashSet.h"
#include "structures/slist.h" 
#include "structures/storage.h"

using namespace std;

void printHelp() {
    cout << " Hash Set " << endl;
    cout << "Available commands:" << endl;
    cout << "  SETADD <set_name> <value>  - add element to set" << endl;
    cout << "  SETDEL <set_name> <value>  - remove element from set" << endl;
    cout << "  SET_AT <set_name> <value>  - check if element is in set" << endl;
    cout << "  HELP                       - show this message" << endl;
    cout << "  EXIT                       - save and quit" << endl;
    cout << "Example: SETADD set1 apple" << endl << endl;
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
    
    Slist sets;
    FInitializeSlist(sets);
    
    LoadSets(file, sets);

    if (!query.empty()) {
        istringstream iss(query);
        string cmd, setName, val;
        if (iss >> cmd >> setName >> val) {
            HashSet<string>* s = FGetOrCreateSet(sets, setName);
            
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

            for (size_t i = 0; i < cmd.length(); ++i) {
                cmd[i] = toupper(cmd[i]);
            }
            
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
            
            HashSet<string>* s = FGetOrCreateSet(sets, setName);
            
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
    FFree(sets);
    
    cout << "Saved to " << file << ". Exiting. Hooray!" << endl;
    return 0;
}