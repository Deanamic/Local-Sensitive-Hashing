#include "Jaccard.h"

Jaccard::Jaccard(vector<vector<string>> docShingles):HT(docShingles.size()), shingles(docShingles), numDoc(docShingles.size()) {
  for(int i = 0; i < numDoc; ++i) {
    for(string& s : shingles[i]) HT[i].insert(s);
  }
}

double Jaccard::getJaccard(int doc1Idx, int doc2Idx) {
  int cnt = 0;
  for(string s : HT[doc1Idx]) if(HT[doc2Idx].count(s)) ++cnt;
  return cnt/double(int(HT[doc1Idx].size()) + int(HT[doc2Idx].size()) - cnt);
}

vector<vector<double>> Jaccard::getAllPairsJaccard() {
  vector<vector<double>> ans(numDoc, vector<double>(numDoc,0));
  for(int i = 0; i < numDoc; ++i) {
    for(int j = i + 1; j < numDoc; ++j) {
      ans[i][j] = ans[j][i] = getJaccard(i,j);
    }
  }
  return ans;
}
