#ifndef MINHASH_H
#define MINHASH_H
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

class MinHash {
public:
  MinHash(vector<vector<string>> Shingles, int r);
  bool hasSignature(int r);
  int getSignatureIndex(int i);
private:
  int rows;
  vector<vector<int>> signatureMatrix;
};

#endif
