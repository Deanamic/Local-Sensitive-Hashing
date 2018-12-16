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

void TestNews(int shinglesize) {
  const int numDocs = 19;
  vector<Parser> docParser(numDocs);
  vector<string> docs(numDocs);
  vector<vector<string>> Kshingles(numDocs);
  for(int i = 0; i < numDocs; ++i) {
    string curDoc = "./data/News/News.dat" + to_string(i+1);
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
    for(int j = 0; j < i; ++j) {
      cout << fixed << setprecision(5) << v1[i][j] << ' ';
    }
    cout << endl;
  }
}

void TestShuffle(int shinglesize) {
  const int numDocs = 20;
  vector<Parser> docParser(numDocs);
  vector<string> docs(numDocs);
  vector<vector<string>> Kshingles(numDocs);
  for(int i = 0; i < numDocs; ++i) {
    string curDoc = "./data/ShuffleTest/ShuffleTest.dat" + to_string(i+1);
    docParser[i] = Parser(curDoc);
    docs[i] = docParser[i].getDocument();
    Kshingles[i] = docParser[i].getKShingles(shinglesize);
  }
  JaccardAhoCorasick JAC(Kshingles, docs);
  for(int i = 0; i < numDocs; ++i) {
    for(int j = i + 1; j < numDocs; ++j) {
      cout << fixed << setprecision(5) << JAC.getJaccard(i,j) << ' ';
    }
    cout << endl;
  }
  MinHash M(Kshingles, 10);
  OnePermutationHash OPH(Kshingles, 3, 2);
  LSHBanding LSH(Kshingles, 20);
  LSHOPBanding LSHOP(Kshingles, 4, 10);

  cout << "Test de Precision del Minhash" << endl;
  cout << "Con 10 Permutaciones" << endl;
  double sum = 0;
  int cnt = 0;
  for(int i = 0; i < numDocs; ++i) {
    for(int j = i + 1; j < numDocs; ++j) {
      cnt++;
      double dif = JAC.getJaccard(i, j) - M.getJaccard(i,j);
      sum += dif*dif;
    }
  }
  cout << "Error medio cuadratico: " << sqrt(sum)/cnt << endl << endl;

  cout << endl;
  cout << "Test de Precision del OnePermutationhash" << endl;
  cout << "Con 3 grupos y 2 permutaciones" << endl;
  sum = 0;
  cnt = 0;
  for(int i = 0; i < numDocs; ++i) {
    for(int j = i + 1; j < numDocs; ++j) {
      cnt++;
      double dif = JAC.getJaccard(i, j) - OPH.getJaccard(i,j);
      sum += dif*dif;
    }
  }
  cout << "Error medio cuadratico: " << sqrt(sum)/cnt << endl;
  cout << endl;
  cout << "Test de falsos positivos y falsos negativos con distintos threshholds utilizando Banding y Minhash" << endl;
  cout << "Con 10 Permutaciones" << endl;
  for(int I = 1; I < 10; ++I) {
    double threshhold = I * 0.1;
    int FalseP = 0, FalseN = 0;
    int RealAns = 0;
    auto cand = LSH.getSimilarDocuments(threshhold);
    for(pair<int,int> p : cand) {
      if(JAC.getJaccard(p.first, p.second) < threshhold) FalseP++;
    }
    for(int i = 0; i < numDocs; ++i) {
      for(int j = i + 1; j < numDocs; ++j) {
        if(JAC.getJaccard(i, j) > threshhold) ++RealAns;
      }
    }
    FalseN = RealAns - (cand.size() - FalseP);
    int TrueP = cand.size() - FalseP - FalseN;
    cout << "Con threshhold: " << threshhold << ", Obtenemos " << FalseP << " Falsos Positivos y " << FalseN << " Falsos Negativos y " << TrueP << " Positivos verdaderos" << endl;
    if(cand.size() > 0) cout << double(cand.size() - FalseN - FalseP)/(cand.size()) << "% de acierto\n";
  }

  cout << endl;
  cout << "Test de falsos positivos y falsos negativos con distintos threshholds utilizando Banding y OnePermutationhash" << endl;
  cout << "Con 3 grupos y 2 permutaciones" << endl;
  for(int I = 1; I < 10; ++I) {
    double threshhold = I * 0.1;
    int FalseP = 0, FalseN = 0;
    int RealAns = 0;
    auto cand = LSHOP.getSimilarDocuments(threshhold);
    for(pair<int,int> p : cand) {
      if(JAC.getJaccard(p.first, p.second) < threshhold) FalseP++;
    }
    for(int i = 0; i < numDocs; ++i) {
      for(int j = i + 1; j < numDocs; ++j) {
        if(JAC.getJaccard(i, j) > threshhold) ++RealAns;
      }
    }
    FalseN = RealAns - (cand.size() - FalseP);
    int TrueP = cand.size() - FalseP - FalseN;
    cout << "Con threshhold: " << threshhold << ", Obtenemos " << FalseP << " Falsos Positivos y " << FalseN << " Falsos Negativos y " << TrueP << " Positivos verdaderos" << endl;
    if(cand.size() > 0) cout << double(cand.size() - FalseN - FalseP)/(cand.size()) << "% de acierto\n";
  }
  cout << endl;
}

void test(int num, int shinglesize, string nombreTest) {
  vector<Parser> docParser(num);
  vector<string> docs(num);
  vector<vector<string>> Kshingles(num);
  for(int i = 0; i < num; ++i) {
    string curDoc = nombreTest + to_string(i+1);
    docParser[i] = Parser(curDoc);
    docs[i] = docParser[i].getDocument();
    Kshingles[i] = docParser[i].getKShingles(shinglesize);
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
  TestShuffle(5);
  // TestNews(6);
  //test(400, 7, "./data/TestAumentarNumTexto/Test4/Test4.dat");
}
