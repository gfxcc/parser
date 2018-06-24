# Bottom Up Parsing

## Chapter 7.1  

Simple C++ implementation of BFS based bottom up parser

## Usage

```bash

» ./bin/buttomUpParser ../data/rules.dat
S
S -> aaa
S -> Sab
S -> aSb

input: aaaab
2 valid solutions found
aaaab --(S -> aaa)-- Sab --(S -> Sab)-- S

aaaab --(S -> aaa)-- aSb --(S -> aSb)-- S

-------------------

```
