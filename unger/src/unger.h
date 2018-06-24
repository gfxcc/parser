//
// Created by Yong Cao at Dec/22/2017
//
//

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <stdio.h>
#include "ascii_tree.h"


using std::string;
using std::vector;
using std::unordered_map;
using AsciiTree::Tree;
using AsciiTree::Node;


class Parser {

public:

    Parser(const string& grammar);
    bool parse(const string& pattern, const string& input);

    void print_grammar() {
        printf("-----grammar------\n");
        for (auto& rule : grammar_) {
            for (auto& right : rule.second) {
                printf("%c -> %s\n", rule.first, right.c_str());
            }
        }
    }

private:
    bool parse(const string& pattern, const string& input, Node* node);
    unordered_map<char, vector<string>> grammar_;
    Tree ptree_;
};

class Rule {
public:
    char left;
    vector<char> right;

};
