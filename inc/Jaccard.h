#ifndef JACCARD_H
#define JACCARD_H
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;
class Jaccard {
public:
  Jaccard(vector<vector<string>> docShingles);
  double getJaccard(int doc1Idx, int doc2Idx);
private:
  vector<vector<string>> shingles;
};

#endif
