#ifndef  _DICTIONARY_H_
#define  _DICTIONARY_H_

#include  <iostream>
#include  <vector>
#include  <list>
#include  <algorithm>
#include  <string>
#include  <stdlib.h>
#include <cstring>

#include  "hashset.h"
#include  "hashset.cpp"

using namespace std;

class hash_function {
public:

    unsigned int operator()(const string &s) const
    {
        return hash(s);
    }

    unsigned int hash(const string &s) const;

private:
// Copied from Murmur3.
    const unsigned int c1 = 0xcc9e2d51;
    const unsigned int c2 = 0x1b873593;
    unsigned int just42(unsigned int val) const
    {
        return val ^ ((unsigned long long)(val) >> 42);
    }
};

class equality {
public:
    equality() {}

    bool operator()(const string &A, const string &B) const
    {
        return (A == B);
    }
};

class Dictionary : public HashSet<string, hash_function, equality> {

    // Complete definition
public:
    Dictionary(string filename);

};

#endif // _DICTIONARY_H_
