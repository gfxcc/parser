#ifndef INCLUDE_ACS_STATE
#define INCLUDE_ACS_STATE

#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
namespace ACS {

using std::string;
using std::vector;

class State {
public:
    //
    // CONSTRUCTORS
    //

    // name need in alphabetical order
    State(const string& name);

    //
    // ACCESSORS
    //
    const string& name() const;
    bool isTerminal() const;
    const State* nextState(char c) const;

    //
    // MANIPULATORS
    //
    // current State -- (c) --> next state
    void addPath(char c, const State* state);
    void isTerminal(bool isTerminal);

private:
    string d_name;
    bool d_isTerminal;
    vector<const State*> d_next;
};

inline
State::State(const string& name)
: d_name(name)
, d_isTerminal(false)
, d_next(128, nullptr)
{
    std::sort(d_name.begin(), d_name.end());
    assert(d_name == name);
}

//
// ACCESSORS
//
inline
const string& State::name() const
{
    return d_name;
}

inline
bool State::isTerminal() const
{
    return d_isTerminal;
}

inline
const State* State::nextState(char c) const
{
    return d_next[c];
}

//
// MANIPULATORS
//
inline
void State::addPath(char c, const State* state)
{
    assert(nullptr != state);
    d_next[c] = state;
}

inline
void State::isTerminal(bool isTerminal)
{
    d_isTerminal = isTerminal;
}


} // namespace ACS
#endif

