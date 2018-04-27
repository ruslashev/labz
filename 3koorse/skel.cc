#include <iostream>
#include <functional>
#include <string>

using namespace std;

int main() {
  int count = 0, branch_count = 0, a = 2, b = 8;

  function<void (int, int, string)> calc =
    [&calc, &count, &branch_count](int x, int fin, string way) {
      branch_count++;
      if (x < fin) {
        calc(x + 1, fin, way + " +1");
        calc(x * 2, fin, way + " *2");
      } else
        if (x == fin) {
          count++;
          cout << way << endl;
        }
    };
  cout << "from " << a << " to " << b << endl;
  calc(a, b, "");
  cout << "routes = " << count << endl;
  cout << "branches taken = " << branch_count << endl;
  cout << endl;
  count = branch_count = 0;

  function<void (int, int, string)> calc_rev =
    [&calc_rev, &count, &branch_count](int x, int fin, string way) {
      branch_count++;
      if (x > fin) {
        calc_rev(x - 1, fin, way + " -1");
        if (x % 2 == 0)
          calc_rev(x / 2, fin, way + " /2");
      } else
        if (x == fin) {
          count++;
          cout << way << endl;
        }
    };
  cout << "from " << b << " to " << a << endl;
  calc_rev(b, a, "");
  cout << "routes = " << count << endl;
  cout << "branches taken = " << branch_count << endl;
}

