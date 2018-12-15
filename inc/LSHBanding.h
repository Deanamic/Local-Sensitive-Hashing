#ifndef LSHBANDING_H
#define LSHBANDING_H
#include "MinHash.h"
#include <set>

class LSHBanding : MinHash {
public:
  LSHBanding(vector<vector<string>> shinglesMatrix, int r);
  vector <pair<int,int>> getSimilarDocuments(double threshold);
  double getJaccard(int doc1Idx, int doc2Idx);
private:
  vector<pair<int, int> > getCandidatesLSH(int bandWidth);
  int calculateBandWidth(double threshold);
  int hashVector(int docIdx, int init, int fin, int value, int mod);
};

#endif
