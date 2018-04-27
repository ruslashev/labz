#include <iostream>
#include <vector>

int rand_in_range(int min, int max) {
  return min + rand() % (max - min + 1);
}

int main() {
  std::vector<int> a;
  for (int i = 0; i < 40; ++i)
    a.push_back(rand_in_range(1, 100));

  int first = 1, mindiff;
  for (int i = 0; i < 40; ++i)
    for (int j = 0; j < 40; ++j)
      if (first || std::abs(a[j] - a[i]) < mindiff) {
        first = 1;
        mindiff = std::abs(a[j] - a[i]);
      }

  std::cout << mindiff;
}

