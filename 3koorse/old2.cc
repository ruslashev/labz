#include <iostream>
using namespace std;

int main() {
  int max_a, max_b, max_c, max_d, count_a = 0, count_b = 0
    , count_c = 0, count_d = 0;
  bool set_a = 0, set_b = 0, set_c = 0, set_d = 0;
  while (!cin.eof()) {
    string comp, shop, cat;
    int price;
    cin >> comp >> shop >> cat >> price;

    if (cat == "A") {
      if (set_a && price == max_a)
        ++count_a;
      if (!set_a || price > max_a) {
        set_a = 1;
        count_a = 1;
        max_a = price;
      }
    } else if (cat == "B") {
      if (set_b && price == max_b)
        ++count_b;
      if (!set_b || price > max_b) {
        set_b = 1;
        count_b = 1;
        max_b = price;
      }
    } else if (cat == "C") {
      if (set_c && price == max_c)
        ++count_c;
      if (!set_c || price > max_c) {
        set_c = 1;
        count_c = 1;
        max_c = price;
      }
    } else if (cat == "D") {
      if (set_d && price == max_d)
        ++count_d;
      if (!set_d || price > max_d) {
        set_d = 1;
        count_d = 1;
        max_d = price;
      }
    }
  }
  cout << count_a << " " << count_b << " " << count_c << " " << count_d;
}

