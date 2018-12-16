#ifndef JACCARD_H
#define JACCARD_H
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;
class Jaccard {
public:
  Jaccard(vector<vector<string>> docShingles);
  double getJaccard(int doc1Idx, int doc2Idx);
  vector<vector<double>> getAllPairsJaccard();
private:
  vector<unordered_set<string>> HT;
  vector<vector<string>> shingles;
  int numDoc;
};

#endif
