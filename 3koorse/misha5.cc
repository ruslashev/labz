#include <iostream>
#include <functional>
#include <string>

using namespace std;

int main() {
  int count = 0, branch_count = 0, a = 5, b = 31;

  function<void (int, int, string, bool)> calc =
    [&calc, &count, &branch_count](int x, int fin, string way, bool pred_sat) {
      branch_count++;
      if (x < fin) {
        int x1 = x + 3, x2 = x + 4, x3 = x * 2;
        calc(x1, fin, way + "+3 ", pred_sat | (x1 == 20) | (x1 == 27));
        calc(x2, fin, way + "+4 ", pred_sat | (x2 == 20) | (x2 == 27));
        calc(x3, fin, way + "*2 ", pred_sat | (x3 == 20) | (x3 == 27));
      } else
        if (x == fin && pred_sat) {
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
    [&calc_rev, &count, &branch_count](int x, int fin, string way, bool pred_sat) {
      branch_count++;
      if (x > fin) {
        int x1 = x - 3, x2 = x - 4, x3 = x / 2;
        calc_rev(x1, fin, way + "-3 ", pred_sat | (x1 == 20) | (x1 == 27));
        calc_rev(x2, fin, way + "-4 ", pred_sat | (x2 == 20) | (x2 == 27));
        if (x % 2 == 0)
          calc_rev(x3, fin, way + "/2 ", pred_sat | (x3 == 20) | (x3 == 27));
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

