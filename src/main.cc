#include <iostream>
#include <fstream>
#include <set>
#include <ctime>
#include "Parser.h"
#include "JaccardAhoCorasick.h"
#include "MinHash.h"
#include "Jaccard.h"
#include "LSHBanding.h"
#include "OnePermutationHash.h"
#include "LSHOPBanding.h"
using namespace std;

void Test5(int shinglesize) {
  vector<Parser> docParser(50);
  vector<string> docs(50);
  vector<vector<string>> Kshingles(50);
  for(int i = 0; i < 50; ++i) {
    string curDoc = "./data/Test5/Test5.dat" + to_string(i+1);
    docParser[i] = Parser(curDoc);
    docs[i] = docParser[i].getDocument();
    Kshingles[i] = docParser[i].getKShingles(shinglesize);
  }
  auto t = clock();
  JaccardAhoCorasick JAC(Kshingles, docs);
  for(int i = 0; i < 50; ++i) {
    for(int j = i + 1; j < 50; ++j) {
      JAC.getJaccard(i,j);
      //cout << JAC.getJaccard(i, j) << '\n';
    }
  }
  cout << "JACCARDAHOCORASICK CLOCK: " << double(clock() - t)/CLOCKS_PER_SEC << endl;
  t = clock();
  Jaccard J(Kshingles);
  for(int i = 0; i < 50; ++i) {
    for(int j = i + 1; j < 50; ++j) {
      J.getJaccard(i,j);
      //cout << J.getJaccard(i, j) << '\n';
    }
  }
  cout << "JACCARD CLOCK: " << double(clock() - t)/CLOCKS_PER_SEC << endl;
  for(int i = 0; i < 50; ++i) {
    for(int j = i + 1; j < 50; ++j) {
      if(JAC.getJaccard(i, j) - J.getJaccard(i,j) > 0.005) cout << "BUG" << endl;
    }
  }
  MinHash M(Kshingles, 100);
  LSHBanding LSH(Kshingles, 100);
  OnePermutationHash OPH(Kshingles, 10, 15);
  LSHOPBanding OPB(Kshingles, 50, 15);
}
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
  Test5(5);
  return 0;
  Parser doc1("./data/Test5.dat"), doc2("./data/Test6.dat");
  auto v1 = doc1.getKShingles(7);
  auto v2 = doc2.getKShingles(7);
  string s1 = doc1.getDocument();
  string s2 = doc2.getDocument();

  JaccardAhoCorasick JAC({v1,v2},{s1,s2});
  MinHash M({v1,v2}, 100);
  LSHBanding LSH({v1,v2}, 5000);
  OnePermutationHash OPH({v1,v2}, 50, 15);
  LSHOPBanding OPB({v1,v2},50,15);
  Jaccard J({v1,v2});
  cout << JAC.getJaccard(0,1) << endl;
  cout << J.getJaccard(0,1) << endl;
  cout << M.getJaccard(0,1) << endl;
  cout << OPH.getJaccard(0,1) << endl;
  double threshold = 0.3;
  auto candidates = LSH.getSimilarDocuments(threshold);
  cout << "List of documents more similar than " << threshold << endl;
  for (pair<int,int>& p : candidates){
    cout << p .first << " " << p.second << ' ' << LSH.getJaccard(p.first, p.second) << endl;
  }
  candidates = OPB.getSimilarDocuments(threshold);
  cout << "List of documents more similar than " << threshold << endl;
  for (pair<int,int>& p : candidates){
    cout << p .first << " " << p.second << ' ' << OPB.getJaccard(p.first, p.second) << endl;
  }
}
