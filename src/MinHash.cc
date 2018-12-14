#include "MinHash.h"
#include <bits/stdc++.h>
MinHash::MinHash(vector<vector<string>> shinglesMatrix, int r) : numDoc(shinglesMatrix.size()), numPerm(r){
  vector<unordered_set<string>> foundShingles(numDoc);
  vector<string> shingles;
  unordered_set<string> universalShingleSet;
  for(int i = 0; i < numDoc; ++i) {
    for(string& s : shinglesMatrix[i]) {
      foundShingles[i].insert(s);
      universalShingleSet.insert(s);
    }
  }
  for(string s : universalShingleSet) shingles.push_back(s);
  signatureMatrix.resize(r, vector<int>(numDoc));
  long long mod = PolyHash::getPrimeMod(shingles.size());
  for(int i = 0; i < r; ++i) {
    PolyHash perm(i, 1, mod);
    for(int j = 0; j < numDoc; ++j) {
      int it = 0;
      while(perm.evaluate(it) >= (int)shingles.size() or foundShingles[j].count(shingles[perm.evaluate(it)]) == 0) {
        ++it;
      }
      signatureMatrix[i][j] = it;
    }
  }
}

int MinHash::getSignatureAtIndex(int docIdx, int i) {
    return signatureMatrix[i][docIdx];
}

double MinHash::getJaccard(int docIdx1, int docIdx2) {
  int cnt = 0;
  for(int i = 0; i < numPerm; ++i) if(getSignatureAtIndex(docIdx1, i) == getSignatureAtIndex(docIdx2, i)) ++cnt;
  return cnt/double(numPerm);
}

