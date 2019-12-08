#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <set>
#include <iomanip> // setw
#include <iterator>


#include "dictionary.h"

using namespace std;

void lower(string &s);

string stripPunct(string &s);

void checkSpelling(ifstream &in, Dictionary &dict);


// program arguments to run, example: main.exe ../../res/wordlist.txt ../../res/test.txt
int main(int argc, char *argv[]) {

    // Output usage message if improper command line args were given.
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " wordlist_filename input_file\n";
        return EXIT_FAILURE;
    }

    ifstream inf(argv[2]);
    if (!inf) {
        cerr << "Could not open " << argv[2] << "\n";
        return EXIT_FAILURE;
    }

    // Read dictionary, but let user know what we are working on.
    cout << "Loading dictionary, this may take awhile...\n";

    Dictionary d(argv[1]);

    checkSpelling(inf, d);

    inf.close();

    return EXIT_SUCCESS;
}

void checkSpelling(ifstream &in, Dictionary &dict) {

    int line_number = 0;

    while (in) {
        line_number++;
        set<string> totest;
        string line;
        getline(in, line);

        stringstream ss(stringstream::in | stringstream::out);
        ss << line;

        string word, _word, __word;
        int len = 0;
        while (ss >> word) {
            set<string> correct;
            _word = word;

            stripPunct(_word);
            lower(_word);
            len = _word.length();
            if (dict.search(_word))
                continue;
            for (int i = 0; i < len; i++) {
                __word = _word.substr(0, i) + _word[(i + 1) % len] + word[i] +
                         _word.substr((i + 2) % len, len - i - 2 < 0 ? 0 : len - i - 2);
                if (dict.search(__word))
                    correct.insert(__word);
                __word = _word.substr(0, i) +
                         _word.substr((i + 1) % len, len - i - 1 < 0 ? 0 : len - i - 1);
                if (dict.search(__word))
                    correct.insert(__word);
                for (char c = 'a'; c <= 'z'; c++) {
                    __word = _word.substr(0, i) + c +
                             _word.substr((i + 1) % len, len - i - 1 < 0 ? 0 : len - i - 1);
                    if (dict.search(__word))
                        correct.insert(__word);
                    __word = _word.substr(0, i) + c + _word[i] +
                             _word.substr((i + 1) % len, len - i - 1 < 0 ? 0 : len - i - 1);
                    if (dict.search(__word))
                        correct.insert(__word);
                }
            }
            for (char c = 'a'; c <= 'z'; c++) {
                __word = _word + c;
                if (dict.search(__word))
                    correct.insert(__word);
            }
            cout << line_number << " " << _word << " ";
            std::copy(correct.begin(), correct.end(), std::ostream_iterator<string>(std::cout, ", "));
            cout << ".\n";
        }
    }
}

void lower(string &s) {

    // Ensures that a word is lowercase
    for (int i = 0; i < s.length(); i++)
        s[i] = tolower(s[i]);
}

string stripPunct(string &s) {

    // Remove any single trailing
    // punctuation character from a word.
    while (ispunct(s[s.length() - 1]))
        s = s.substr(0, s.length() - 1);
}
