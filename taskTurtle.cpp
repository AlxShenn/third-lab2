#include <iostream>
#include "structures/hashset.h"

using namespace std;

int main() {
    int N;
    cout << "Enter number of turtles N: ";
    if (!(cin >> N)) return 0;

    HashSet<string> validClaims;

    cout << "Enter pairs (a_i b_i):" << endl;
    for (int i = 0; i < N; ++i) {
        int a, b;
        cin >> a >> b;

        if (a + b + 1 == N) {
            validClaims.add(to_string(a) + "_" + to_string(b));
        }
    }

    cout << "Max truthful turtles: " << validClaims.getSize() << endl;
    
    return 0;
}