#ifndef MINHASH_H
#define MINHASH_H

#include <vector>
#include <string>
#include <unordered_set>
#include "PolyHash.h"
using namespace std;

class MinHash {
public:
  MinHash(vector<vector<string>> shinglesMatrix, int r);
  int getSignatureAtIndex(int docIdx, int i);
  double getJaccard(int docIdx1, int docIdx2);
private:
  int numDoc;
  int numPerm;
  vector<vector<int>> signatureMatrix;
};

#endif
