#ifndef __AHOCORASICK_H
#define __AHOCORASICK_H
#include <vector>
#include <string>
#include <queue>
#include <stdexcept>
using namespace std;

class AhoCorasick {
public:
  AhoCorasick(const vector<string>& v);
  int findMatches(const string& s);
  struct node;
private:
  int Alpha;
  vector<node> V;
  vector<int> order;

  int getval(const char c);
  void build(const vector<string>& v);
  void CreateSuffixLink();
};
#endif
