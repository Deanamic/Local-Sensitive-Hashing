#include "MinHash.h"
#include <iostream>
#include <set>
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


vector<pair<int, int> > MinHash::getCandidatesLSH(int bandWidth){
	vector < pair < int , int > > candidates;
	if(numPerm%bandWidth != 0) {
		cout << "Band width should divide the number of permutations" << endl;
		cout << "bandWidth = " << bandWidth << ", numPerm = " << numPerm << endl;
		return candidates;
	}
	set < pair < int , int > > candidates1;
	int numBands = numPerm/bandWidth;
	for (int i = 0; i < numBands; ++i){
		vector < vector < int > > v (10^9 + 7);
		for (int j = 0; j < numDoc; ++j){
			int cont = 0;
			for (int t = i*bandWidth; t<(i+1)*bandWidth; ++t){
				cont += signatureMatrix[t][j];
				cont %= (10^9 + 7); 
			}
			for (int t = 0; t<(int)v[cont].size(); ++t){
				candidates1.insert({min(v[cont][t], numDoc), max(v[cont][t], numDoc)});
			}
		}
	}
	for (auto t : candidates1) candidates.push_back(t);
	return candidates;
}
