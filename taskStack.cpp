#include <iostream>
#include <string>
#include <sstream>
#include "structures/stack.h"

using namespace std;

int main() {
    string input;
    string choice;
    
    while (true) {
        cout << "Enter the expression separated by spaces:";
        getline(cin, input);
    
        Stack stack;
        stringstream ss(input);
        string token;
        bool error = false;
    
        while (ss >> token) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                string op1Str, op2Str;
                if (stack.isEmpty()) { error = true; break;}
                stack.pop(op1Str);

                if (stack.isEmpty()) { error = true; break;}
                stack.pop(op2Str);
            
                int op1 = stoi(op1Str);
                int op2 = stoi(op2Str);
                int res = 0;
            
                if (token == "+") res = op2 + op1;
                else if (token == "-") res = op2 - op1;
                else if (token == "*") res = op2 * op1;
                else if (token == "/") {
                    if (op1 == 0) {
                        cout << "Ошибка: деление на ноль!" << endl;
                        error = true;
                        break;
                    }
                    res = op2 / op1;
                }
                stack.push(to_string(res));
            } else {
                stack.push(token);
            }
        }

        if (!error && !stack.isEmpty()) {
            string result;
            stack.pop(result);
            if (stack.isEmpty()) {
                cout << "Result: " << result << endl;
            }
            else {
                cout << "Expression has extra operandes.";
            }
        } else if (error) {
            cout << "Expression doesn't have enough operandes." << endl;
        }

        cout << "Continue?? (y/n) : ";
        getline(cin, choice);
        
        if (choice == "n") break;
    }
    cout << "Hooray!";
    return 0;
}