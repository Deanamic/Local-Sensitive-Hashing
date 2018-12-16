#include "Parser.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
const int MAXIT = 50;

int main() {
  string filename;
  cin >> filename;
  Parser p(filename);
  string s = p.getDocument();
  stringstream line(s);
  vector<string> vs;
  string token;
  while(line >> token)vs.push_back(token);
  for(int i = 0; i < MAXIT; ++i) {
    fstream f(filename + to_string(i+1), ios::out);
    random_shuffle(vs.begin(), vs.end());
    for(string si : vs) f << si << ".,()[] \n"[rand()%8];
    f << endl;
  }
}
