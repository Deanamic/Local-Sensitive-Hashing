#include "JaccardAhoCorasick.h"

JaccardAhoCorasick::JaccardAhoCorasick(vector<vector<string>> docShingles, vector<string> docs):document(docs) {
  ACTrie = vector<AhoCorasick>(int(docShingles.size()));
  for(int i = 0; i < (int)docShingles.size(); ++i) {
    ACTrie[i] = AhoCorasick(docShingles[i], AlphaSize);
  }
}

double JaccardAhoCorasick::getJaccard(int doc1Idx, int doc2Idx) {
  int cnt = ACTrie[doc1Idx].findMatches(document[doc2Idx]);
  return cnt/double(ACTrie[doc1Idx].getNumWords() + ACTrie[doc2Idx].getNumWords() - cnt);
}
