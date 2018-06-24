//
// Created by Yong Cao @ 06/16/2018
//

#ifndef INCLUDE_BUPARSING_PARSER_H
#define INCLUDE_BUPARSING_PARSER_H

#include <string>
#include <iostream>
#include <unordered_map>

namespace BUParsing {

class State;

class Parser {
  public:
    //
    // Constructors
    //
    Parser(const std::string& configPath);

    //
    // Modifiers
    //
    std::vector<State> parse(const std::string& input);

    // print rules
    std::ostream& print(std::ostream& os) const;

  private:
    std::unordered_map<std::string, char> d_rules;
    char d_terminal;
};

inline
std::ostream& operator<<(std::ostream& os, const Parser& parser) {
    return parser.print(os);
}

} // namespace BUParsing

#endif

