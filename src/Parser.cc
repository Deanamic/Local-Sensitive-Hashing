#include "Parser.h"
using namespace std;

Parser::Parser(string s) :archivo(s), parseado(false){}

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
                else if ('0' <= c and c <= '9') {
                    document += c;
                }
                else if(document.size() > 0 && document.back() != ' ') document += ' ';
            }
            if(document.size() > 0 and document.back() != ' ') document += ' ';
        }
    }
    else throw runtime_error("File does not exist");
    ficheroEntrada.close();
    while(document.back() == ' ') document.pop_back();
    parseado = true;
}

string Parser::getDocument() {
    if (not parseado) parse();
    return document;
}

vector<string> Parser::getDocumentShuffle(vector<int> seeds) {
    if (not parseado) parse();
    vector <string> doc;
    
    string aux;
    for (int i = 0; i < (int)document.size(); ++i) {
		if (document[i] != ' ') aux.push_back(document[i]);
		else {
			doc.push_back(aux);
			aux = "";
		}
	}
	doc.push_back(aux);
	
	
	vector<string> result;
	for (int i = 0; i < (int)seeds.size(); ++i) {
		srand(seeds[i]);
		random_shuffle(doc.begin(), doc.end());
		string shuffleDoc = doc[0];
		for (int j = 1; j < (int)doc.size(); ++j) {
			shuffleDoc = shuffleDoc + ' ' + doc[j];
		}
		result.push_back(shuffleDoc);
		cout << shuffleDoc << endl;
	}
	
	return result;
}

bool Parser::getParseado() {
    return parseado;
}

vector<string> Parser::getKShingles(int k) {
    if (not parseado) parse();
    int n = document.size();
    cout << document << endl;
    if (k > 0 and n-k+1 > 0) {
        vector<string> kshingles(n-k+1);
        for (int i = 0; i < (int)kshingles.size(); ++i) {
            kshingles[i] = document.substr(i, k);
        }
        return kshingles;
    }
    throw runtime_error("Shingles size large than document size");
}
