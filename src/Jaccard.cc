#include "Jaccard.h"

Jaccard::Jaccard(vector<vector<string>> docShingles):shingles(docShingles) {}

double Jaccard::getJaccard(int doc1Idx, int doc2Idx) {
  unordered_set<string> doc1Set, doc2Set;
  for(string& s : shingles[doc1Idx]) doc1Set.insert(s);
  for(string& s : shingles[doc2Idx]) doc2Set.insert(s);
  int cnt = 0;
  for(string s : doc1Set) if(doc2Set.count(s)) ++cnt;
  return cnt/double(int(doc1Set.size()) + int(doc2Set.size()) - cnt);
}
