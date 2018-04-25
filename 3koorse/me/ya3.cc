#include <iostream>
#include <string>
#include <vector>
using namespace std;

int count_occ(string hay, string needle)
{
  int o = 0;
  string::size_type p = 0;
  while ((p = hay.find(needle, p)) != string::npos)
  {
    ++o;
    p += needle.length();
  }
  return o;
}

int main()
{
  string w = "abc";
  vector<string> wz = {
    "asdf",
    "qwer",
    "no",
    "xaxbxcx",
    "+++",
    "++++",
    "qwercqwer"
  };
  for (string e : wz)
  {
    string a(e.size(), '*');
    for (int i = 0; ; ++i)
    {
      if (i >= (int)e.size())
        break;
      if (w.find(e[i]) == string::npos)
        continue;
      e.insert(i + 1, a);
      i += a.size() - 1;
    }
    if (count_occ(e, "**") + count_occ(e, "++") < 2)
      continue;
    auto p = e.rfind("++");
    if (p != string::npos)
      e.erase(p, 2);
    cout << e << " ";
  }
  cout << endl;
}

