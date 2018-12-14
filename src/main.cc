#include <iostream>
#include <fstream>
#include <set>
#include "Parser.h"
#include "AhoCorasick.h"
#include "MinHash.h"
using namespace std;

int main(int argc, char *argv[]) {
  /*
    string nombre;
    if(argc!=2) {
        cout << "Dime el nombre de la familia de fichero (sin .txt): ";
        getline(cin,nombre);
    }
    else nombre = argv[1];
    nombre += ".txt"; */
    //canvi
    Parser doc1("./data/Test1.dat"), doc2("./data/Test2.dat");
    auto v = doc1.getKShingles(5);
    auto v1 = doc2.getKShingles(5);
    AhoCorasick AC1(v, 'z' - 'a' + 12), AC2(v1, 'z' - 'a' + 12);
    string s = doc2.getDocument(), s1 = doc1.getDocument();
    cout << AC1.findMatches(s)/double(AC1.getNumWords() + AC2.getNumWords() - AC1.findMatches(s)) << endl;
    cout << AC1.findMatches(s) << endl;
    cout << AC2.findMatches(s1) << endl;
    MinHash M({v,v1}, 1000);
    cout << M.getJaccard(0, 1) << endl;



    set<string> seric;
    for (int i = 0; i < (int)v.size(); i++) {
        seric.insert(v[i]);
    }
    int cont = 0;
    set<string>smiguel;
    for (int i = 0; i < (int)v1.size(); i++) {
        smiguel.insert(v1[i]);
    }

    for (string s : smiguel) if (seric.count(s)) ++cont;
    for (int i = 0; i < (int)v1.size(); i++) {
        seric.insert(v1[i]);
    }
    cout << double(cont)/double(seric.size()) << endl;
    return 0;
}
