#ifndef ONEPERMUTATIONHASH_H
#define ONEPERMUTATIONHASH_H

#include <vector>
#include <string>
#include <unordered_set>
#include <bits/stdc++.h>
#include <math.h>
#include "PolyHash.h"
using namespace std;

class OnePermutationHash {
public:
  OnePermutationHash(vector<vector<string>> shinglesMatrix, int k, int l);
  double getJaccard(int docIdx1, int docIdx2);
protected:
  int numDoc;
  int numBins;
  int numTables;
  vector<vector<int>> signatureMatrix;
};

#endif
