#ifndef  _DICTIONARY_H_
#define  _DICTIONARY_H_

#include  <iostream>
#include  <vector>
#include  <list>
#include  <algorithm>
#include  <string>
#include  <stdlib.h>

#include  "hashset.h"
#include  "hashset.cpp"

using namespace std;

class hash_function {
public:

    unsigned int operator()(const string& s) const
    {
        return hash(s);
    }

    unsigned int hash(const string& s) const
    {
        unsigned int h = 0;
        size_t n = s.length();
        unsigned int* a = new unsigned int[n];
        unsigned int b = 0;
        unsigned int c = 0xe6546b64;
        for (size_t i = 0; i < n; i++) 
        {
            signed char v = s[i];
            b = b * c1 + v;
            c ^= b;
            a[i] = c;
            h += a[i];
        }
        b = h;
        c = 0xe6546b64;
        signed char v, v1;
        for (size_t i = 3; i < n; i *= 2)
            for (size_t j = 0; j < n; j += i)
                for (size_t k = 0; k < i / 3; k++)
                {
                    v = a[(j * i + k) % n];
                    v1 = a[(j * i + (k + 1 + i / 6) % (i / 3)) % n];
                    b = b * c2 ^ v1 + v;
                    c ^= b;
                    a[(j * i + k) % n] ^= c;
                    h += a[(j * i + k) % n];
                }
        delete[] a;
        return h;
    }


private:
// Copied from Murmur3.
    const unsigned int c1 = 0xcc9e2d51;
    const unsigned int c2 = 0x1b873593;

};

class equality {
public:
    equality() {}

    bool operator()(const string& A, const string& B) const
    {
        return (A == B);
    }
};

class Dictionary : public HashSet<string, hash_function, equality>{

    // Complete definition
public:
    Dictionary(string filename)
    {
        ifstream in(filename);
        if (!in.is_open())
            throw std::invalid_argument("Could not open " + filename);
        string word;
        while (in >> word)
            insert(word);
        in.close();
    }

};

#endif // _DICTIONARY_H_
