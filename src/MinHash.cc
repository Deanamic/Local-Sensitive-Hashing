#include "MinHash.h"
#include "PolyHash.h"
#include <iostream>
#include <set>
#include <math.h>
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

int MinHash::calculateBandWidth(double threshold){
	double margin = 0.1;
	if (threshold < margin) {
		cout << "threshold too low" << endl;
		return 1;
	}
	for (int bandWidth = 1; bandWidth < numPerm; bandWidth++){
		double value = pow(1.0/double(numPerm/bandWidth),1.0/double(bandWidth));
		if (value > threshold - margin) return bandWidth;
	}
	return 1;
}

vector < pair < int , int > > MinHash::getSimilarDocuments(double threshold){
	int bandWidth = calculateBandWidth(threshold);
	cout << "BandWidth = " << bandWidth << endl;
	auto candidates = getCandidatesLSH(bandWidth);
	vector < pair < int, int > > similar;
	for (auto s : candidates){
		if (getJaccard(s.first, s.second)) similar.push_back(s);
	}
	return similar;
}

double MinHash::getJaccard(int docIdx1, int docIdx2) {
  int cnt = 0;
  for(int i = 0; i < numPerm; ++i) if(signatureMatrix[i][docIdx1] == signatureMatrix[i][docIdx2]) ++cnt;
  return cnt/double(numPerm);
}

int MinHash::hashVector(int docIdx, int init, int fin, int value, int mod){
	vector<int> v(fin-init);
	for (int i = init; i < fin; i++) v[i-init] = signatureMatrix[i][docIdx];
	PolyHash P = PolyHash(v,mod);
	return P.evaluate(value);
}

vector<pair<int, int> > MinHash::getCandidatesLSH(int bandWidth){
	set < pair < int , int > > candidates1;
	int numBands = numPerm/bandWidth;
	for (int i = 0; i < numBands; ++i){
		vector < vector < int > > v (7919);
		for (int j = 0; j < numDoc; ++j){
			int hash = hashVector(j,i*bandWidth, (i+1)*bandWidth, 107, 7919);
			for (int t = 0; t<(int)v[hash].size(); ++t){
				candidates1.insert({min(v[hash][t], j), max(v[hash][t], j)});
			}
			v[hash].push_back(j);
		}
	}
	vector < pair < int , int > > candidates;
	for (auto t : candidates1) candidates.push_back(t);
	return candidates;
}
