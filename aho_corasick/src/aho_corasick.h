#ifndef INCLUDE_ACS_AHOCORASICK
#define INCLUDE_ACS_AHOCORASICK

#include <string>
#include <unordered_map>
#include <memory>
#include <utility>
#include <cassert>
#include "state.h"

namespace ACS {

using std::string;

const int PATTERN_SIZE_MAX = 26;
const char START_STATE_NAME = 'A';

class ACSearch {
public:
    //
    // CREATORS
    //
    ACSearch(const string& pattern);
    // pattern must be less than 26 characters

    //
    // ACCESSORS
    //

    int match(const string& source) const;
    // return index of first match.
    // will return -1 if does not found any match
private:

    void buildNFA();
    void buildDFA();

    // pattern need search
    string d_pattern;

    std::unique_ptr<State> d_NFA_root;
    std::unique_ptr<State> d_DFA_root;
};

inline
ACSearch::ACSearch(const string& pattern)
: d_pattern(pattern)
{
    assert(pattern.size() < 26);
    buildNFA();
    buildDFA();
}

} // namespace ACS

#endif // INCLUDE_ACS_AHOCORASICK
