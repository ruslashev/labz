#include <iostream>
#include <iterator>
#include <set>
#include <algorithm>
#include <string>

using namespace std;

int rand_in_range(int min, int max) {
  return min + rand() % (max - min + 1);
}

void print_set(const string &name, const set<int> &s) {
  cout << name << " = { ";
  for (int x : s)
    cout << x << " ";
  cout << "}" << endl;

}

int main() {
  srand(time(nullptr));

  set<int> U, A, B;
  int a = 1, b = 20, c = 10, d = 20;

  for (int i = a; i <= b; ++i)
    U.insert(i);

  for (int i = c; i <= d; ++i)
    if (U.count(i) && i % 2 != 0)
      A.insert(i);

  for (int x : U)
    if (x % 2 == 0)
      B.insert(x);

  set<int> AB, nAB, nA, nB, nAunB;
  set_intersection(A.begin(), A.end(), B.begin(), B.end(), inserter(AB, AB.begin()));
  set_difference(U.begin(), U.end(), AB.begin(), AB.end(), inserter(nAB, nAB.begin()));
  set_difference(U.begin(), U.end(), A.begin(), A.end(), inserter(nA, nA.begin()));
  set_difference(U.begin(), U.end(), B.begin(), B.end(), inserter(nB, nB.begin()));
  set_union(nA.begin(), nA.end(), nB.begin(), nB.end(), inserter(nAunB, nAunB.begin()));

  print_set("U", U);
  print_set("A", A);
  print_set("B", B);
  print_set("nAB", nAB);
  print_set("nAunB", nAunB);

  for (int i = (double)b * (7. / 10.) + 0.5; i <= b; ++i)
    if (U.count(i))
      cout << i << " ";
}

