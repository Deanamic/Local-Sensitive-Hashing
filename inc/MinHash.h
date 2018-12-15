#ifndef MINHASH_H
#define MINHASH_H

#include <vector>
#include <string>
#include <unordered_set>
#include <math.h>
#include "PolyHash.h"
using namespace std;

class MinHash {
public:
  MinHash(vector<vector<string>> shinglesMatrix, int r);
  double getJaccard(int docIdx1, int docIdx2);
protected:
  int numDoc;
  int numPerm;
  vector<vector<int> > signatureMatrix;
};

#endif
