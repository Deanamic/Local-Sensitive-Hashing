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
  //random_shuffle(shingles.begin(), shingles.end());
  signatureMatrix.assign(numTables*numBins, vector<int>(numDoc, -1));
  int numWords = universalShingleSet.size();
  for(int h = 0; h < numTables; ++h) {
    int curOffSet = 0;
    for(int i = 0; i < numBins; ++i) {
      int curIdx = h*numBins + i;
      int binSize = (numWords+i)/numBins;
      long long mod = PolyHash::getPrimeMod(binSize);
      PolyHash perm(i*i + 1133*h, 1, mod);
      for(int j = 0; j < numDoc; ++j) {
        for(int it = 0; signatureMatrix[curIdx][j] == -1 && it < mod; ++it) {
          int curPos = perm.evaluate(it);
          if(curPos < binSize && foundShingles[j].count(shingles[curOffSet + curPos])) signatureMatrix[curIdx][j] = it;
        }
      }
      curOffSet += binSize;
    }
  }
}

double OnePermutationHash::getJaccard(int docIdx1, int docIdx2) {
  int cnt = 0;
  for(int i = 0; i < numTables; ++i) {
    for(int j = 0; j < numBins; ++j) {
      int curIdx = i*numBins + j;
      if(signatureMatrix[curIdx][docIdx1] == signatureMatrix[curIdx][docIdx2]) ++cnt;
    }
  }
  return cnt/double(numBins*numTables);
}

