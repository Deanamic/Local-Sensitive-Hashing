#include "LSHBanding.h"

LSHBanding::LSHBanding(vector<vector<string>> shinglesMatrix, int r) : MinHash(shinglesMatrix,r) {}

int LSHBanding::calculateBandWidth(double threshold){
	double margin = 0.05;
	if (threshold < margin) {
		return -1;
	}
	for (int bandWidth = 1; bandWidth < numPerm; bandWidth++){
		double value = pow(1.0/double(numPerm/bandWidth),1.0/double(bandWidth));
		if (value > threshold - margin) return bandWidth;
	}
	return 1;
}

int LSHBanding::hashVector(int docIdx, int init, int fin, int value, int mod){
	vector<int> v(fin-init);
	for (int i = init; i < fin; i++) v[i-init] = signatureMatrix[i][docIdx];
	PolyHash P = PolyHash(v,mod);
	return P.evaluate(value);
}

vector<pair<int,int>> LSHBanding::getCandidatesLSH(int bandWidth){
	set<pair<int,int>> candidates1;
	int numBands = numPerm/bandWidth;
	for (int i = 0; i < numBands; ++i){
		unordered_map < int, vector <int> > v;
		for (int j = 0; j < numDoc; ++j){
			int hash = hashVector(j,i*bandWidth, (i+1)*bandWidth, 7919, 1e9 + 7);
			for (int t = 0; t<(int)v[hash].size(); ++t){
				candidates1.insert({min(v[hash][t], j), max(v[hash][t], j)});
			}
			v[hash].push_back(j);
		}
	}
	vector <pair<int,int>> candidates;
	for (auto t : candidates1) candidates.push_back(t);
	return candidates;
}

vector <pair<int,int>> LSHBanding::getSimilarDocuments(double threshold){
	int bandWidth = calculateBandWidth(threshold);
	return getCandidatesLSH(bandWidth);
}

double LSHBanding::getJaccard(int doc1Idx, int doc2Idx) {
  return MinHash::getJaccard(doc1Idx, doc2Idx);
}
