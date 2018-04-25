#include <iostream>
#include <iterator>
#include <set>
#include <algorithm>
#include <string>

using namespace std;

int rand_in_range(int min, int max) {
  return min + rand() % (max - min + 1);
}

int nearest_even(int x) {
  return x % 2 == 0 ? x : x + 1;
}

void print_set(const string &name, const set<int> &s) {
  cout << name << " = { ";
  for (int x : s)
    cout << x << " ";
  cout << "}" << endl;

}

int main() {
  srand(time(nullptr));

  int a = 0, b = 100, N = 10;

  set<int> U, A, B;

  while (U.size() != (size_t)N)
    U.insert(rand_in_range(a, b));

  for (int x = nearest_even(a); x < b && (x % 2) == 0; x += 2)
    if (U.count(x))
      A.insert(x);

  for (int x : U)
    if (x % 2)
      B.insert(x);

  set<int> AuB;
  set_union(A.begin(), A.end(), B.begin(), B.end(), inserter(AuB, AuB.begin()));

  set<int> nA, nB, nAnB, nnAnB;
  set_difference(U.begin(), U.end(), A.begin(), A.end(), inserter(nA, nA.begin()));
  set_difference(U.begin(), U.end(), B.begin(), B.end(), inserter(nB, nB.begin()));
  set_intersection(nA.begin(), nA.end(), nB.begin(), nB.end(), inserter(nAnB, nAnB.begin()));
  set_difference(U.begin(), U.end(), nAnB.begin(), nAnB.end(), inserter(nnAnB, nnAnB.begin()));

  print_set("U", U);
  print_set("A", A);
  print_set("B", B);
  print_set("AuB", AuB);
  print_set("nnAnB", nnAnB);

  copy_if(AuB.begin(), AuB.end(), ostream_iterator<int>(cout, " "),
      [](int x) { return x % 2 != 0; });
}

