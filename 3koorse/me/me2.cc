#include <bits/stdc++.h>
using namespace std;

int main() {
  map<char,array<int,3>> d;
  d['a'][1] = d['b'][1] = d['c'][1] = d['d'][1] = 0;
  d['a'][2] = d['b'][2] = d['c'][2] = d['d'][2] = 0;
  while (!cin.eof()) {
    string comp, shop, cat;
    int price;
    cin >> comp >> shop >> cat >> price;

    if (cat == "A") {
      if (d['a'][2] && price == d['a'][0])
        ++d['a'][1];
      if (!d['a'][2] || price > d['a'][0]) {
        d['a'][2] = d['a'][1] = 1;
        d['a'][0] = price;
      }
    } else if (cat == "B") {
      if (d['b'][2] && price == d['b'][0])
        ++d['b'][1];
      if (!d['b'][2] || price > d['b'][0]) {
        d['b'][2] = d['b'][1] = 1;
        d['b'][0] = price;
      }
    } else if (cat == "C") {
      if (d['c'][2] && price == d['c'][0])
        ++d['c'][1];
      if (!d['c'][2] || price > d['c'][0]) {
        d['c'][2] = d['c'][1] = 1;
        d['c'][0] = price;
      }
    } else if (cat == "D") {
      if (d['d'][2] && price == d['d'][0])
        ++d['d'][1];
      if (!d['d'][2] || price > d['d'][0]) {
        d['d'][2] = d['d'][1] = 1;
        d['d'][0] = price;
      }
    }
  }
  cout << d['a'][1] << " " << d['b'][1] << " " << d['c'][1] << " " << d['d'][1];
}

