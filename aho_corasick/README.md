# aho corasick algorithm

[WIKI](https://en.wikipedia.org/wiki/Aho–Corasick_algorithm)

In computer science, the Aho–Corasick algorithm is a string searching algorithm invented by Alfred V. Aho and Margaret J. Corasick.

This is a simple C++ implementation.

## Algorithm

For each pattern, we will build a NFA (nondeterministic finite automaton) first.

Then, convert that NFA into DFA (deterministic finite automaton)

That DFA will be used to search pattern in string.

