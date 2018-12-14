#ifndef POLYHASH_H
#define POLYHASH_H

#include <vector>
#include <random>
using namespace std;

class PolyHash {
public:
  PolyHash(int seed, int gr, long long mod);
  long long evaluate(long long x);
  static long long getPrimeMod(long long n);
private:
  vector<long long> Coef;
  long long Mod;
};

#endif
