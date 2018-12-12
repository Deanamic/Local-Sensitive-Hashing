#ifndef __PARSER_H
#define __PARSER_H

#include <fstream>
#include <ctype.h>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Parser {
public:
    Parser(string archivo);
    void parse();
    vector<string> getKShingles(int k);
    string getDocument();
    bool getParseado();

private:
    string document;
    string archivo;
    bool parseado;
};

#endif
