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

void Testcnn(int shinglesize) {
  const int numDocs = 199;
  vector<Parser> docParser(numDocs);
  vector<string> docs(numDocs);
  vector<vector<string>> Kshingles(numDocs);
  for(int i = 0; i < numDocs; ++i) {
    string curDoc = "./data/CNN/cnn/cnn.dat" + to_string(i+1);
    docParser[i] = Parser(curDoc);
    docs[i] = docParser[i].getDocument();
    Kshingles[i] = docParser[i].getKShingles(shinglesize);
  }
  Jaccard J(Kshingles);
  auto t = clock();
  auto v2 = J.getAllPairsJaccard();
  cout << "JACCARD CLOCK: " << double(clock() - t)/CLOCKS_PER_SEC << endl;
  JaccardAhoCorasick JAC(Kshingles, docs);
  t = clock();
  auto v1 = JAC.getAllPairsJaccard();
  cout << "JACCARDAHOCORASICK CLOCK: " << double(clock() - t)/CLOCKS_PER_SEC << endl;
  for(int i = 0; i < numDocs; ++i) {
    for(int j = i + 1; j < numDocs; ++j) {
      if(abs(v1[i][j] - v2[i][j]) > 0.005) cout << "BUG" << endl;
      if(v1[i][j] > 0.2) cout << v1[i][j] << '\n';
    }
  }
}
int main(int argc, char *argv[]) {
  Testcnn(10);
  return 0;
}
