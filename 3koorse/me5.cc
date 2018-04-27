#include <iostream>
#include <functional>
#include <string>

using namespace std;

int main() {
  int count = 0, branch_count = 0, a = 3, b = 28, p1 = 14, p2 = 20;

  function<void (int, int, string, bool)> calc =
    [&](int x, int fin, string way, bool pred_sat) {
      branch_count++;
      if (x < fin) {
        int x1 = x + 1, x2 = x + 2, x3 = x * 3;
        calc(x1, fin, way + "+1 ", pred_sat | (x1 == p1) | (x1 == p2));
        calc(x2, fin, way + "+2 ", pred_sat | (x2 == p1) | (x2 == p2));
        calc(x3, fin, way + "*3 ", pred_sat | (x3 == p1) | (x3 == p2));
      } else if (x == fin && pred_sat) {
          count++;
          cout << way << endl;
        }
    };
  cout << "from " << a << " to " << b << endl;
  calc(a, b, "", 0);
  cout << "routes = " << count << endl;
  cout << "branches taken = " << branch_count << endl;
  cout << endl;
  count = branch_count = 0;

  function<void (int, int, string, bool)> calc_rev =
    [&](int x, int fin, string way, bool pred_sat) {
      branch_count++;
      if (x > fin) {
        int x1 = x - 1, x2 = x - 2, x3 = x / 3;
        calc_rev(x1, fin, way + "-1 ", pred_sat | (x1 == p1) | (x1 == p2));
        calc_rev(x2, fin, way + "-2 ", pred_sat | (x2 == p1) | (x2 == p2));
        if (x % 3 == 0)
          calc_rev(x3, fin, way + "/3 ", pred_sat | (x3 == p1) | (x3 == p2));
      } else
        if (x == fin && pred_sat) {
          count++;
          cout << way << endl;
        }
    };
  cout << "from " << b << " to " << a << endl;
  calc_rev(b, a, "", 0);
  cout << "routes = " << count << endl;
  cout << "branches taken = " << branch_count << endl;
}

