#ifndef MINHASH_H
#define MINHASH_H

#include <vector>
#include <string>
#include <unordered_set>
#include "PolyHash.h"
using namespace std;

class MinHash {
public:
  MinHash(vector<vector<string>> shinglesMatrix, int r);
  vector < pair < int, int > > getSimilarDocuments(double threshold);
private:
  int numDoc;
  int numPerm;
  vector<vector<int> > signatureMatrix;
  vector<pair<int, int> > getCandidatesLSH(int bandWidth);
  double getJaccard(int docIdx1, int docIdx2);
  int calculateBandWidth(double threshold);
  int hashVector(int docIdx, int init, int fin, int value, int mod);
};

#endif
