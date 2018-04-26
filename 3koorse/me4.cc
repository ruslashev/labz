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

bool contains_all_but_b(const set<int> &A, set<int> U, const set<int> &B) {
  for (int x : B)
    U.erase(x);
  return U == A;
}

int main() {
  srand(time(nullptr));

  set<int> U, A, B;

  /*
  int N = 10;
  cout << "Enter " << N << " numbers: ";
  while (N) {
    int t;
    cin >> t;
    U.insert(t);
    --N;
  }
  */
  for (int i = 1; i <= 10; ++i)
    U.insert(i);

  for (int x : U)
    if (x % 2 == 0)
      B.insert(x);

  while (!contains_all_but_b(A, U, B)) {
    size_t idx = rand_in_range(0, U.size() - 1);
    int elem = *next(U.cbegin(), idx);
    if (elem % 2 == 0)
      continue;
    A.insert(elem);
  }

  set<int> ab;
  set_intersection(A.begin(), A.end(), B.begin(), B.end(), inserter(ab, ab.begin()));

  set<int> nA, nB, nAunB, nnAunB;
  set_difference(U.begin(), U.end(), A.begin(), A.end(), inserter(nA, nA.begin()));
  set_difference(U.begin(), U.end(), B.begin(), B.end(), inserter(nB, nB.begin()));
  set_union(nA.begin(), nA.end(), nB.begin(), nB.end(), inserter(nAunB, nAunB.begin()));
  set_difference(U.begin(), U.end(), nAunB.begin(), nAunB.end(), inserter(nnAunB, nnAunB.begin()));

  print_set("U", U);
  print_set("A", A);
  print_set("B", B);
  print_set("ab", ab);
  print_set("nnAnB", nnAunB);

  int n = 0, m = 9;
  for (int i = n; i <= m; ++i)
    cout << *next(U.cbegin(), i) << " ";
}

