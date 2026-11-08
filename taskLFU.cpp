#include <iostream>
#include <string>
#include <sstream>
#include "structures/lfuCache.h"

using namespace std;

void printHelp() {
    cout << "LFU Cache Manager" << endl;
    cout << "Available commands:" << endl;
    cout << "  SET <key> <value>  - add or update a key-value pair" << endl;
    cout << "  GET <key>          - get value by key (or -1 if not found)" << endl;
    cout << "  CAP                - show current cache capacity" << endl;
    cout << "  HELP               - show this message" << endl;
    cout << "  EXIT               - quit the program" << endl << endl;
}

int main() {
    int cap;
    cout << "Enter cache capacity: ";
    if (!(cin >> cap) || cap <= 0) {
        cout << "Invalid capacity. Exiting." << endl;
        return 1;
    }
    cin.ignore();

    LFUCache cache(cap);
    cout << "Cache initialized with capacity " << cap << "." << endl;
    printHelp();

    string line;
    while (true) {
        cout << "> ";
        if (!getline(cin, line)) break;
        if (line.empty()) continue;

        istringstream iss(line);
        string cmd;
        if (!(iss >> cmd)) continue;

        for (char& c : cmd) c = toupper(c);

        if (cmd == "EXIT") {
            cout << "Hooray!!" << endl;
            break;
        } else if (cmd == "HELP") {
            printHelp();
        } else if (cmd == "CAP") {
            cout << "Current capacity: " << cap << endl;
        } else if (cmd == "SET") {
            int key, value;
            if (iss >> key >> value) {
                cache.put(key, value);
                cout << "Set [" << key << "] = " << value << endl;
            } else {
                cout << "Error: usage is SET <key> <value>" << endl;
            }
        } else if (cmd == "GET") {
            int key;
            if (iss >> key) {
                int res = cache.get(key);
                if (res == -1) {
                    cout << "-> -1 (not found)" << endl;
                } else {
                    cout << "-> " << res << endl;
                }
            } else {
                cout << "Error: usage is GET <key>" << endl;
            }
        } else {
            cout << "Unknown command. Type HELP." << endl;
        }
    }

    return 0;
}