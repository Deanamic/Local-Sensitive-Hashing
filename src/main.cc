#include <iostream>
#include <fstream>
#include <set>
#include "Parser.h"
#include "AhoCorasick.h"
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
    cout << AC1.findMatches(s) << endl;
    cout << AC2.findMatches(s1) << endl;
    set<string> S;
    for(auto c : v) S.insert(c);
    int cnt = 0;
    for(auto c : v1) if(S.count(c)) {
        cout << c << endl;
        ++cnt;
    }
    cout << cnt << endl;
    return 0;
}
