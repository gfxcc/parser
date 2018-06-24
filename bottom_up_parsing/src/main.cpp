#include "parser.h"
#include "state.h"

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;
using namespace BUParsing;

int main() {

    Parser parser("./bin/rules.txt");
    cout << parser << endl;

    string input;
    while (true) {
        cout << "input: ";
        cin >> input;

        auto parseStates = parser.parse(input);
        cout << parseStates.size() << " valid solutions found" << endl;
        for_each(parseStates.cbegin(), parseStates.cend(), [&](const State& state) {
                    cout << state << endl;
                });
        cout << "-------------------" << endl;
    }

    return 0;
}
