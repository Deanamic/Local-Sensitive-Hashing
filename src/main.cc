#include <iostream>
#include <fstream>
#include <set>
#include <cmath>
#include <chrono>
#include <assert.h>
#include "Parser.h"
#include "JaccardAhoCorasick.h"
#include "MinHash.h"
#include "Jaccard.h"
#include "LSHBanding.h"
#include "OnePermutationHash.h"
#include "LSHOPBanding.h"
using namespace std;

//Test para comprovar que los métodos para calcular Jaccard son correctos
void TestNews(int shinglesize) {
  cout << endl << "TestNews" << endl;
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
  JaccardAhoCorasick JAC(Kshingles, docs);
  for(int i = 0; i < numDocs; ++i) {
    for(int j = 0; j < i; ++j) {
      cout << fixed << setprecision(5) << JAC.getJaccard(i,j) << ' ';
      assert(abs(J.getJaccard(i,j) - JAC.getJaccard(i,j)) < 0.01);
    }
    cout << endl;
  }
}

//Calcula la precision de MinHashm, OPHash, LSHBanding y LSHOPBanding
//Con 20 documentos formado por la permutacion de 20 palabras
void TestShuffle(int shinglesize) {
  cout << endl << "TestShuffle" << endl;
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
    for(int j = 0; j < i; ++j) {
      cout << fixed << setprecision(5) << JAC.getJaccard(i,j) << ' ';
    }
    cout << endl;
  }
  MinHash M(Kshingles, 10);
  OnePermutationHash OPH(Kshingles, 3, 2);
  LSHBanding LSH(Kshingles, 30);
  LSHOPBanding LSHOP(Kshingles, 5, 10);

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
    cout << "Con threshhold: " << threshhold << ", Obtenemos " << FalseP << " Falsos Positivos y " << FalseN << " Falsos Negativos y " << TrueP << " Positivos verdaderos y " << RealAns << " Positivos Totales" << endl;
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
    cout << "Con threshhold: " << threshhold << ", Obtenemos " << FalseP << " Falsos Positivos y " << FalseN << " Falsos Negativos y " << TrueP << " Positivos verdaderos y " << RealAns << " Positivos Totales" << endl;
  }
  cout << endl;
}

// Realiza el mismo test que TestShuffle eliminando ciertos couts
// añadiendo los otros dos algoritmos
// y midiendo tiempos de construcción y recorrido.
void TestShuffle2(int shinglesize) {
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
  auto t = clock();
  auto t1 = clock();

  t = clock();
  Jaccard J(Kshingles);
  t1 = clock();
  for(int i = 0; i < numDocs; ++i)
    for(int j = i + 1; j < numDocs; ++j)
      J.getJaccard(i,j);
  cout << "JACCARD CONSTRUCCIÓN: " << double(t1 - t)/CLOCKS_PER_SEC << endl;
  cout << "JACCARD RECORRIDO: " << double(clock() - t1)/CLOCKS_PER_SEC << endl;

  t = clock();
  JaccardAhoCorasick JAC(Kshingles, docs);
  t1 = clock();
  for(int i = 0; i < numDocs; ++i)
    for(int j = i + 1; j < numDocs; ++j)
      JAC.getJaccard(i,j);
  cout << "JACCARDAHOCORASICK CONSTRUCCIÓN: " << double(t1 - t)/CLOCKS_PER_SEC << endl;
  cout << "JACCARDAHOCORASICK RECORRIDO: " << double(clock() - t1)/CLOCKS_PER_SEC << endl;

  t = clock();
  MinHash M(Kshingles, 10);
  t1 = clock();
  for(int i = 0; i < numDocs; ++i)
    for(int j = i + 1; j < numDocs; ++j)
      M.getJaccard(i,j);
  cout << "MINHASH CONSTRUCCIÓN: " << double(t1 - t)/CLOCKS_PER_SEC << endl;
  cout << "MINHASH RECORRIDO: " << double(clock() - t1)/CLOCKS_PER_SEC << endl;

  t = clock();
  OnePermutationHash OPH(Kshingles, 3, 2);
  t1 = clock();
  for(int i = 0; i < numDocs; ++i)
    for(int j = i + 1; j < numDocs; ++j)
      OPH.getJaccard(i,j);
  cout << "OPH CONSTRUCCIÓN: " << double(t1 - t)/CLOCKS_PER_SEC << endl;
  cout << "OPH RECORRIDO: " << double(clock() - t1)/CLOCKS_PER_SEC << endl;

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
  t = clock();
  LSHBanding LSH(Kshingles, 20);
  t1 = clock();
  cout << "LSHBanding CONSTRUCCIÓN: " << double(t1 - t)/CLOCKS_PER_SEC << endl;
  for(int I = 1; I < 10; ++I) {
    double threshhold = I * 0.1;
    int FalseP = 0, FalseN = 0;
    int RealAns = 0;
    t1 = clock();
    auto cand = LSH.getSimilarDocuments(threshhold);
    cout << "LSHBanding RECORRIDO: " << double(clock() - t1)/CLOCKS_PER_SEC << endl;
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
  t = clock();
  LSHOPBanding LSHOP(Kshingles, 4, 10);
  t1 = clock();
  cout << "LSHBanding CONSTRUCCIÓN: " << double(t1 - t)/CLOCKS_PER_SEC << endl;
  for(int I = 1; I < 10; ++I) {
    double threshhold = I * 0.1;
    int FalseP = 0, FalseN = 0;
    int RealAns = 0;
    t1 = clock();
    auto cand = LSH.getSimilarDocuments(threshhold);
    cout << "LSHBanding RECORRIDO: " << double(clock() - t1)/CLOCKS_PER_SEC << endl;
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


// Subtest de testGlobal
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

// Realiza el experimento 1:
// Mide tiempos de los algoritmos que hallan Jaccard aumentando palabras o documentos
void testGlobal() {
  cout << "Aumenta numero de documentos " << endl;
  test(50, 7, "./data/TestAumentarTexto/Test1/Test1.dat");
  test(100, 7, "./data/TestAumentarTexto/Test2/Test2.dat");
  test(200, 7, "./data/TestAumentarTexto/Test3/Test3.dat");
  test(400, 7, "./data/TestAumentarTexto/Test4/Test4.dat");

  cout << "Aumenta numero de palabras " << endl;
  test(50, 7, "./data/TestAumentarNumTexto/Test1/Test4.dat");
  test(50, 7, "./data/TestAumentarNumTexto/Test2/Test4.dat");
  test(50, 7, "./data/TestAumentarNumTexto/Test3/Test4.dat");
  test(50, 7, "./data/TestAumentarNumTexto/Test4/Test4.dat");

}

void Driver() {
  string fileName;
  cout << "Indique la carpeta, y el nombre base de los archivos (suponemos que todos los ficheros tienen nombre+numero de 0 a Maxnum" << endl;
  cin >> fileName;
  cout << "Indique el numero de archivos con este nombre base" << endl;
  int num;
  cin >> num;
  cout << "Indique el tamano de los shingles" << endl;
  int shinglesize;
  cin >> shinglesize;
  vector<Parser> docParser(num);
  vector<string> docs(num);
  vector<vector<string>> Kshingles(num);
  for(int i = 0; i < num; ++i) {
    string curDoc = fileName + to_string(i);
    docParser[i] = Parser(curDoc);
    docs[i] = docParser[i].getDocument();
    Kshingles[i] = docParser[i].getKShingles(shinglesize);
  }
  Jaccard J(Kshingles);
  JaccardAhoCorasick JAC(Kshingles, docs);
  MinHash M(Kshingles, 1000);
  OnePermutationHash OPH(Kshingles, 5, 100);


  cout << "Indique el numero de los dos archivos que quiere comparar" << endl;
  int x, y;
  while(cin >> x >> y) {
    if(min(x,y) < 0 || max(x,y) >= num) cout << "Indices invalidos" << endl;
    else {
      cout << fixed << setprecision(5) << "Utilizando tablas de Hash: " << J.getJaccard(x,y) << "| Utilizando Aho-Corasick: " << JAC.getJaccard(x,y) << "| Utilizando MinHash: " << M.getJaccard(x,y) << "| Utilizando One Permutation Hash: " << OPH.getJaccard(x,y) << endl;
    }
  }
}
int main(int argc, char *argv[]) {
  /*
  TestShuffle2(5);
  TestNews(6);
  testGlobal();
  */
  Driver();
}
