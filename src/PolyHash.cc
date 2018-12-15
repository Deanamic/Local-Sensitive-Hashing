#include "PolyHash.h"
#include <iostream>
PolyHash::PolyHash(int seed, int gr, long long mod) : Coef(gr + 1), Mod(mod) {
  srand(seed);
  for(int i = 0; i <= gr; ++i) {
      Coef[i] = rand()%(Mod-1)+1;
  }
}

PolyHash::PolyHash(vector<int> coef, long long mod) : Coef((int)coef.size()), Mod(mod) {
  for(int i = 0; i < (int)coef.size(); ++i) Coef[i] = coef[i];
}

long long PolyHash::evaluate(long long x) {
  long long val = 0;
  for(long long a : Coef) {
    val *= x;
    val += a;
    val %= Mod;
  }
  return (val%Mod+Mod)%Mod;
}

long long PolyHash::getPrimeMod(long long n){
    for (int i = n; ; ++i){
        bool primer = true;
        for (int j = 2; j*j < i and primer; ++j) if (i%j == 0) primer = false;
        if (primer) return i;
    }
}
