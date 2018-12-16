#include <iostream>
#include <fstream>
#include <set>
#include <cmath>
#include <chrono>
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

void test(int num, string nombreTest) {
  vector<Parser> docParser(num);
  vector<string> docs(num);
  vector<vector<string>> Kshingles(num);
  for(int i = 0; i < num; ++i) {
    string curDoc = nombreTest + to_string(i);
    docParser[i] = Parser(curDoc);
    docs[i] = docParser[i].getDocument();
    Kshingles[i] = docParser[i].getKShingles(7);
  }
  auto t = clock();
  Jaccard J(Kshingles);
  auto t1 = clock();
  J.getAllPairsJaccard();
  cout << "JACCARD CONSTRUCCIÓN: " << double(t1 - t)/CLOCKS_PER_SEC << endl;
  cout << "JACCARD RECORRIDO: " << double(clock() - t1)/CLOCKS_PER_SEC << endl;
  t = clock();
  JaccardAhoCorasick JAC(Kshingles, docs);
  t1 = clock();
  JAC.getAllPairsJaccard();
  cout << "JACCARDAHOCORASICK CONSTRUCCIÓN: " << double(t1 - t)/CLOCKS_PER_SEC << endl;
  cout << "JACCARDAHOCORASICK RECORRIDO: " << double(clock() - t1)/CLOCKS_PER_SEC << endl;
  t = clock();
  MinHash M(Kshingles, 100);
  t1 = clock();
  for(int i = 0; i < num; ++i)
    for(int j = i + 1; j < num; ++j)
      M.getJaccard(i,j);
  cout << "Minhash CONSTRUCCIÓN: " << double(t1 - t)/CLOCKS_PER_SEC << endl;
  cout << "Minhash RECORRIDO: " << double(clock() - t1)/CLOCKS_PER_SEC << endl;
  double count = 0;
  double sum = 0;
  for(int i = 0; i < num; ++i)
    for(int j = i + 1; j < num; ++j) {
      count++;
      double dif = JAC.getJaccard(i, j) - M.getJaccard(i,j);
      sum += dif*dif;
    }
  cout << "ERROR Minhash" << sqrt(sum)/count << endl;
  t = clock();
  OnePermutationHash OPH(Kshingles, 5, 2);
  t1 = clock();
  for(int i = 0; i < num; ++i)
    for(int j = i + 1; j < num; ++j)
      OPH.getJaccard(i,j);
  cout << "OPH CONSTRUCCIÓN: " << double(t1 - t)/CLOCKS_PER_SEC << endl;
  cout << "OPH RECORRIDO: " << double(clock() - t1)/CLOCKS_PER_SEC << endl;
  count = 0;
  sum = 0;
  for(int i = 0; i < num; ++i)
    for(int j = i + 1; j < num; ++j) {
      count++;
      double dif = JAC.getJaccard(i, j) - OPH.getJaccard(i,j);
      sum += dif*dif;
    }
  cout << "ERROR Minhash" << sqrt(sum)/count << endl;
}

int main(int argc, char *argv[]) {
  Testcnn(10);
  test(400, "./data/TestAumentarNumTexto/Test4/Test4.dat");
}
