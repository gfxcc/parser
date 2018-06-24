//
// Created by Yong Cao # 06/16/2018
//

#include "state.h"



using namespace std;
namespace BUParsing {

State::State(const std::string& input)
: d_pattern(input)
, d_gapIndex(0)
{}


bool State::shift() noexcept
{
    if (d_gapIndex >= d_pattern.size()) {
        return false;
    }
    ++d_gapIndex;
    return true;
}


vector<State> State::reduce(const std::unordered_map<std::string, char>& rules) noexcept
{
    vector<State> nextStates;
    //    |
    // aaaaabcd
    for (size_t len = 1; len <= d_gapIndex; ++len) {
        string candidate = d_pattern.substr(d_gapIndex - len, len);
        unordered_map<string, char>::const_iterator rule = rules.find(candidate);
        if (rule != rules.end()) {
            // can reduce
            // copy , log changes
            State newState = *this;
            newState.d_pattern = d_pattern.substr(0, d_gapIndex - len) + rule->second
                                 + d_pattern.substr(d_gapIndex);
            newState.d_gapIndex = d_gapIndex - len;
            newState.addHistory(d_pattern, rule);
            nextStates.push_back(newState);
        }
    }
    nextStates.push_back(*this);
    return nextStates;
}


void State::addHistory(const std::string& prevPattern, std::unordered_map<std::string, char>::const_iterator& rule)
{
    d_histories.push_back({prevPattern, string(1, rule->second) + " -> " + rule->first});
}



std::ostream& State::print(std::ostream& os) const
{
    for_each(d_histories.cbegin(), d_histories.cend(), [&os](auto& history) {
            os << history.first << " --(" << history.second << ")-- ";
            });
    os << d_pattern << endl;
    return os;
}


} // namespace BUParsing
