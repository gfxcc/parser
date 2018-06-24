//
// Created by Yong Cao at Dec/22/2017
//
#include "unger.h"
#include <fstream>
#include <queue>

using namespace std;

Parser::Parser(const string& grammar) {

    ifstream file(grammar);
    string line;

    while (getline(file, line)) {
        grammar_[line[0]].push_back(line.substr(5));
    }

}

bool Parser::parse(const string& pattern, const string& input) {

    printf("ROOT:%s\n", pattern.c_str());
    printf("input:%s\n", input.c_str());
    ptree_.reset();
    ptree_.set_root(pattern);
    bool rc = parse(pattern, input, ptree_.get_root());
    ptree_.print_tree();
    return rc;
}

// dfs
bool Parser::parse(const string& pattern, const string& input, Node* node) {

    if (pattern == input && pattern.size() == 1) {
        //node->children.push_back(make_shared<Node>(pattern));
        return true;
    }

    if (pattern.size() > input.size())
        return false;
    if (pattern.size() == 1) {
        for (auto& input_left : grammar_[pattern[0]]) {
            node->children.push_back(make_shared<Node>(input_left));
            if (parse(input_left, input, node->children.back().get())) {
                return true;
            }
            node->children.pop_back();
        }
        return false;
    }

    for (int len = 1; len < input.size(); len++) {
        string pattern_left = pattern.substr(0, 1), pattern_remain = pattern.substr(1);
        string input_left = input.substr(0, len), input_remain = input.substr(len);

        node->children.push_back(make_shared<Node>(pattern_left));
        auto ptr_left = node->children.back().get();
        auto ptr_right = node;

        if (pattern_remain.size() == 1) {
            node->children.push_back(make_shared<Node>(pattern_remain));
            ptr_right = node->children.back().get();
        }
        if (parse(pattern_left, input_left, ptr_left) &&
                parse(pattern_remain, input_remain, ptr_right)) {
            return true;
        }
        if (pattern_remain.size() == 1) {
            node->children.pop_back();
        }
        node->children.pop_back();
    }


    return false;
}
