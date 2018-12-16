#include "OnePermutationHash.h"

OnePermutationHash::OnePermutationHash(vector<vector<string>> shinglesMatrix, int k, int l) : numDoc(shinglesMatrix.size()), numBins(k), numTables(l){
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
  signatureMatrix.assign(numTables*numBins, vector<int>(numDoc, -1));
  int numWords = universalShingleSet.size();
  vector<int> perm(numWords);
  iota(perm.begin(), perm.end(), 0);
  for(int h = 0; h < numTables; ++h) {
    random_shuffle(perm.begin(), perm.end());
    int curOffSet = 0;
    for(int i = 0; i < numBins; ++i) {
      int curIdx = numBins * h + i;
      int binSize = (numWords+i)/numBins;
      for(int j = 0; j < numDoc; ++j) {
        int it = curOffSet;
        for(; signatureMatrix[curIdx][j] == -1 && it < curOffSet + binSize; ++it) {
          int curPos = perm[it];
          if(curPos < numWords && foundShingles[j].count(shingles[curPos])) signatureMatrix[curIdx][j] = it;
        }
      }
      curOffSet += binSize;
    }
  }
}

double OnePermutationHash::getJaccard(int docIdx1, int docIdx2) {
  int cnt = 0;
  for(int i = 0; i < numTables; ++i) {
    int curIdx = i*numBins;
    for(int j = 0; j < numBins; ++j, ++curIdx) {
      if(signatureMatrix[curIdx][docIdx1] == signatureMatrix[curIdx][docIdx2]) ++cnt;
    }
  }
  return cnt/double(numBins*numTables);
}

