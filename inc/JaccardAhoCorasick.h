#ifndef JACCARDAHOCORASICK_H
#define JACCARDAHOCORASICK_H
#include <vector>
#include <string>
#include "AhoCorasick.h"
using namespace std;
class JaccardAhoCorasick{
public:
  JaccardAhoCorasick(vector<vector<string>>& docShingles, vector<string>& docs);
  double getJaccard(int doc1Idx, int doc2Idx);
  vector<vector<double>> getAllPairsJaccard();
private:
  vector<AhoCorasick> ACTrie;
  vector<string> document;
  int numDoc;
  static const int AlphaSize = ('z' - 'a' + 1) + (10) + 1;
};

#endif
