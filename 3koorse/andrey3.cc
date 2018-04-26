#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool fit_abbr(const string &abbr, char a, char b, char c)
{
  string cons_abbr = string(1, a) + string(1, b) + string(1, c);
  return abbr == cons_abbr;
}

struct pair_t
{
  string p;
  int n;
};

int main()
{
  map<string, int> occurences;
  string abbr;
  int N;
  cin >> abbr >> N;
  while (!cin.eof())
  {
    string sender, receiver, product;
    int partnumber;
    cin >> sender >> receiver >> product >> partnumber;
    if (fit_abbr(abbr, sender[0], receiver[0], product[0]))
      ++occurences[sender + " " + receiver + " " + product];
  }
  vector<pair_t> occ_vec;
  for (auto it = occurences.begin(); it != occurences.end(); ++it)
    occ_vec.push_back({ it->first, it->second });
  sort(occ_vec.begin(), occ_vec.end(), [](const pair_t &a, const pair_t &b) {
        return a.n > b.n;
      });
  for (const pair_t &p : occ_vec)
    cout << p.p << " " << p.n << endl;
}

