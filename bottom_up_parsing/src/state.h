//
// Created By Yong Cao @ 06/16/1028
//

#ifndef INCLUDE_BUPARSING_STATE_H
#define INCLUDE_BUPARSING_STATE_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

namespace BUParsing {
class State {
  public:

    //
    // Constructors
    //

    // construct an empty state
    State(const std::string& input);


    //
    // Modifiers
    //

    // shift one character from rest of string to stack
    // OUTPUT: 'false' if can not shift anymore. (reach the end of sting)
    //         'true' if shift success
    bool shift() noexcept;

    // try to reduce current stack and return potential states
    // OUTPUT: potential next states
    std::vector<State> reduce(const std::unordered_map<std::string, char>& rules) noexcept;

    void addHistory(const std::string& prevPattern, std::unordered_map<std::string, char>::const_iterator& rule);

    //
    // Accessors
    //
    // print transform history
    std::ostream& print(std::ostream& os) const;

    bool finish(char terminal) const;

  private:
    std::string d_pattern;
    size_t d_gapIndex;
    std::vector<std::pair<std::string, std::string>> d_histories;
};

inline
std::ostream& operator<<(std::ostream& os, const State& state)
{
    return state.print(os);
}

inline
bool State::finish(char terminal) const
{
    return d_pattern == std::string(1, terminal);
}

} // namespace BUParsing

#endif

