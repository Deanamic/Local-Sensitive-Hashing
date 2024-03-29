#ifndef __AHOCORASICK_H
#define __AHOCORASICK_H
#include <vector>
#include <string>
#include <queue>
#include <stdexcept>
using namespace std;

class AhoCorasick {
public:
  AhoCorasick(){}
  AhoCorasick(const vector<string>& v, int alpha);
  int findMatches(const string& s);
  int getNumWords();
private:
  int Words;
  int K;
  int Alpha;
  vector<int> endStates;
  int getval(const char& c);
  void build(const vector<string>& v);
  void CreateSuffixLink();
  struct Node {
    Node(int par, char l, int Alpha);
    vector<int> nxt;
    int p = -1;
    char c;
    int end = 0, SuffixLink = -1, cnt = 0;
  };
  vector<Node> V;
};
#endif
