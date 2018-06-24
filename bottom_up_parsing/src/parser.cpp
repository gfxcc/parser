//
// Created by Yong Cao @ 06/16/2018
//

#include "parser.h"
#include "state.h"

#include <fstream>
#include <cassert>
#include <ctype.h>
#include <vector>
#include <memory>

using namespace std;

namespace {

// INPUT: P -> abc
// OUTPUT: 0 if success
//        non-0 if failed

int loadRuleFromLine(char* left, string* right, const string& line)
{
    assert(isupper(line[0]));

    *left = line[0];
    *right = line.substr(5);
    return 0;
}

} // anonymous namespace

namespace BUParsing {

Parser::Parser(const std::string& configPath)
{
    ifstream s(configPath);
    string line;

    // first line in config file only contains terminal symbol
    assert(getline(s, line));
    // terminal symbol is single character
    assert(line.size() == 1);
    d_terminal = line[0];

    while (getline(s, line)) {
        char left;
        string right;
        assert(0 == loadRuleFromLine(&left, &right, line));

        // let us suppose right will be unique
        d_rules[right] = left;
    }
}


std::vector<State> Parser::parse(const std::string& input)
{
    vector<State> solutions;

    unique_ptr<vector<State>> states = make_unique<vector<State>>();
    unique_ptr<vector<State>> nextLeve = make_unique<vector<State>>();
    // construct first state
    states->emplace_back(input);

    auto iter = states->begin();
    while (iter != states->end()) {
        if (iter->finish(d_terminal)) {
            solutions.push_back(*iter);
        } else {
            if (iter->shift()) {
                auto potentialStates = iter->reduce(d_rules);
                for_each(potentialStates.begin(), potentialStates.end(),
                        [&nextLeve](auto& state) {
                            nextLeve->push_back(state);
                        });
            }
        }

        // reach the end of current level
        // reset states to next level
        if (++iter == states->end()) {
            states->clear();
            states.swap(nextLeve);
            iter = states->begin();
        }
    }

    return solutions;
}


std::ostream& Parser::print(std::ostream& os) const
{
    os << d_terminal << endl;
    for_each(d_rules.cbegin(), d_rules.cend(), [&os](auto& value) {
                os << value.second << " -> " << value.first << endl;
            });
    return os;
}

} // namespace BUParsing

