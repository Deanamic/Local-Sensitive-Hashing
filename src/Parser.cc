#include "Parser.h"
using namespace std;

Parser::Parser(string s) :archivo(s){}

void Parser::parse() {
    if(document.size() > 0) return;
    fstream ficheroEntrada;
    ficheroEntrada.open(archivo.c_str() , ios::in);
    if (ficheroEntrada.is_open()) {
        string frase;
        while (ficheroEntrada >> frase) {
            for (int i = 0; i < (int)frase.size(); ++i) {
                char c = frase[i];
                if (isalpha(c)) {
                    document += tolower(c);
                }
                else if ('0' <= c and c <= ' ') {
                    document += c;
                }
                else if(document.size() > 0 && document.back() != ' ') document += ' ';
            }
            if(document.size() > 0 and document.back() != ' ') document += ' ';
        }
    }
    ficheroEntrada.close();
    parseado = true;
}

string Parser::getDocument() {
    if (not parseado) parse();
    return document.substr(0, int(document.size()-1));
}

bool Parser::getParseado() {
    return parseado;
}

vector<string> Parser::getKShingles(int k) {
    if (not parseado) parse();
    int n = document.size();
    if (k > 0 and n-k+1 > 0) {
        vector<string> kshingles(n-k+1);
        for (int i = 0; i < (int)kshingles.size(); ++i) {
            kshingles[i] = document.substr(i, k);
        }
        return kshingles;
    }
    throw runtime_error("Shingles size large than document size");
}