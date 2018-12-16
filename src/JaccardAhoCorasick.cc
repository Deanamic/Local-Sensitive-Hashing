#include "JaccardAhoCorasick.h"

JaccardAhoCorasick::JaccardAhoCorasick(vector<vector<string>>& docShingles, vector<string>& docs):document(docs), numDoc(docs.size()) {
  ACTrie = vector<AhoCorasick>(int(docShingles.size()));
  for(int i = 0; i < (int)docShingles.size(); ++i) {
    ACTrie[i] = AhoCorasick(docShingles[i], AlphaSize);
  }
}

double JaccardAhoCorasick::getJaccard(int doc1Idx, int doc2Idx) {
  int cnt;
  if(document[doc1Idx].size() < document[doc2Idx].size()) cnt = ACTrie[doc1Idx].findMatches(document[doc2Idx]);
  else cnt = ACTrie[doc2Idx].findMatches(document[doc1Idx]);
  return cnt/double(ACTrie[doc1Idx].getNumWords() + ACTrie[doc2Idx].getNumWords() - cnt);
}

vector<vector<double>> JaccardAhoCorasick::getAllPairsJaccard() {
  vector<vector<double>> ans(numDoc, vector<double>(numDoc,0));
  for(int i = 0; i < numDoc; ++i) {
    for(int j = i + 1; j < numDoc; ++j) {
      ans[i][j] = ans[j][i] = getJaccard(i,j);
    }
  }
  return ans;
}
