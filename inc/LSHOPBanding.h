#ifndef LSHOPBANDING_H
#define LSHOPBANDING_H
#include "OnePermutationHash.h"
#include <set>

class LSHOPBanding : OnePermutationHash {
public:
  LSHOPBanding(vector<vector<string>> shinglesMatrix, int k, int l);
  vector <pair<int,int>> getSimilarDocuments(double threshold);
  double getJaccard(int doc1Idx, int doc2Idx);
private:
  vector<pair<int, int> > getCandidatesLSH(int bandWidth);
  int numPerm;
  int calculateBandWidth(double threshold);
  int hashVector(int docIdx, int init, int fin, int value, int mod);
};

#endif
