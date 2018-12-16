#include "AhoCorasick.h"

AhoCorasick::AhoCorasick(const vector<string>& v, int alpha): Words(0), K(v[0].size()), Alpha(alpha) {
  build(v);
}

AhoCorasick::Node::Node(int par, char l, int Alpha): nxt(Alpha,0), p(par), c(l) {}

int AhoCorasick::getval(const char& c) {
  if(c == ' ') return 0;
  if(isalpha(c)) return c - 'a' + 1;
  if(isdigit(c)) return ('z' - 'a' + 1) + (c - '0');
  throw runtime_error("Undefined Character");
}

void AhoCorasick::CreateSuffixLink() {
  queue<int> q;
  for(q.push(0); q.size(); q.pop()) {
    int pos = q.front();
    if(!pos || !V[pos].p) V[pos].SuffixLink = 0;
    else {
      int val = getval(V[pos].c);
      int j = V[V[pos].p].SuffixLink;
      V[pos].SuffixLink = V[j].nxt[val];
    }
    for(int i = 0; i < Alpha; ++i) {
      if(V[pos].nxt[i]) q.push(V[pos].nxt[i]);
      else if(!pos || !V[pos].p) 	V[pos].nxt[i] = V[0].nxt[i];
      else V[pos].nxt[i] = V[V[pos].SuffixLink].nxt[i];
    }
  }
}

void AhoCorasick::build(const vector<string> &v) {
  V.reserve(v.size() * v[0].size());
  V.emplace_back(-1, 0, Alpha);
  for(auto &s : v) {
    int pos = 0;
    for(auto &c : s) {
      int val = getval(c);
      if(!V[pos].nxt[val]) {
        V.emplace_back(pos, c, Alpha);
        V[pos].nxt[val] = (int)V.size() - 1;
      }
      pos = V[pos].nxt[val];
    }
    if(V[pos].end == 0) {
      Words++;
      endStates.push_back(pos);
    }
    V[pos].end = 1;

  }
  CreateSuffixLink();
}

int AhoCorasick::getNumWords() {
  return Words;
}

int AhoCorasick::findMatches(const string& s) {
  int pos = 0, matches = 0;
  for(auto& c : s) {
    int val = getval(c);
    pos = V[pos].nxt[val];
    if(V[pos].end) V[pos].cnt = 1;
  }
  for(int x : endStates) {
    if(V[x].cnt) matches++;
    V[x].cnt = 0;
  }
  return matches;
}
