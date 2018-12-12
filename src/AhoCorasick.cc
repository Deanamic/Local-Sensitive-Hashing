#include "AhoCorasick.h"

AhoCorasick::AhoCorasick(const vector<string>& v) {
  build(v);
}

struct AhoCorasick::node {
  node(int par, char l, int Alpha): nxt(Alpha,0), p(par), c(l) {}
  vector<int> nxt;
  int p = -1;
  char c;
  int end = 0, SuffixLink = -1, cnt = 0;
};

int AhoCorasick::getval(const char c) {
  if(c == ' ') return 0;
  if(isalpha(c)) return c - 'a' + 1;
  if(isdigit(c)) return ('z' - 'a' + 1) + (c - '0');
  throw runtime_error("Undefined Character");
}

void AhoCorasick::CreateSuffixLink() {
  queue<int> q;
  for(q.push(0); q.size(); q.pop()) {
    int pos = q.front();
    order.push_back(pos);
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
  for(auto &s : v) {
    int pos = 0;
    for(auto &c : s) {
      int val = getval(c);
      if(!V[pos].nxt[val]) {
        V.emplace_back(pos, c, 40);
        V[pos].nxt[val] = (int)V.size() - 1;
      }
      pos = V[pos].nxt[val];
    }
    V[pos].end++;
  }
  CreateSuffixLink();
}

int AhoCorasick::findMatches(const string& s) {
  int pos = 0, matches = 0;
  for(auto c : s) {
    int val = getval(c);
    pos = V[pos].nxt[val];
    V[pos].cnt++;
  }
  for(int i = (int)order.size() - 1; i >= 0; --i) {
    int	x = order[i];
    matches += V[x].cnt;
    if(V[x].SuffixLink != -1) V[V[x].SuffixLink].cnt += V[x].cnt;
  }
  return matches;
}
