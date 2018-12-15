#include <iostream>
#include <fstream>
#include <set>
#include "Parser.h"
#include "JaccardAhoCorasick.h"
#include "MinHash.h"
#include "Jaccard.h"
#include "LSHBanding.h"
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
    auto v1 = doc1.getKShingles(5);
    auto v2 = doc2.getKShingles(5);
    string s1 = doc1.getDocument();
    string s2 = doc2.getDocument();

    JaccardAhoCorasick JAC({v1,v2},{s1,s2});
    MinHash M({v1,v2}, 5000);
    LSHBanding LSH({v1,v2},5000);
    Jaccard J({v1,v2});
    cout << JAC.getJaccard(0,1) << endl;
    cout << J.getJaccard(0,1) << endl;
    cout << M.getJaccard(0,1) << endl;
    double threshold = 0.18;
    auto candidates = LSH.getSimilarDocuments(threshold);
    cout << "List of documents more similar than " << threshold << endl;
    for (pair<int,int>& p : candidates){
      cout << p .first << " " << p.second << ' ' << M.getJaccard(p.first, p.second) << endl;
    }
}
