#include <iostream>
#include <fstream>
#include <string>
//#include <tkIntXlibDecls.h>
#include "dictionary.h"


Dictionary::Dictionary(string filename)
{
    ifstream in(filename);
    if (!in)
        throw std::invalid_argument("Could not open " + filename);
    string word;
    while (in >> word)
        insert(word);
}

unsigned int hash_function::hash(const string& s) const
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
        h += just42(a[i]);
    }
    b = h;
    c = 0xe6546b64;
    for (size_t i = 3; i < n; i *= 2)
        for (size_t j = 0; j < n; j += i)
            for (size_t k = 0; k < i / 3; k++)
            {
                signed char v = a[j * i + k];
                signed char v1 = a[j * i + (k + 1 + i / 6) % (i / 3)];
                b = b * c2 ^ v1 + v;
                c ^= b;
                a[j * i + k] ^= c;
                h -= just42(a[j * i + k]);
            }
    delete[]a;
    return just42(h);
}
