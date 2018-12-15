#ifndef __PARSER_H
#define __PARSER_H

#include <fstream>
#include <ctype.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

class Parser {
public:
    Parser(string archivo);
    void parse();
    vector<string> getKShingles(int k);
    string getDocument();
    vector<string> getDocumentShuffle(vector<int> seeds);
    bool getParseado();

private:
    string document;
    string archivo;
    bool parseado;
};

#endif
