#include <iostream>
#include <iterator>
#include <set>
#include <algorithm>
#include <string>

using namespace std;

int rand_in_range(int min, int max)
{
    return min + rand() % (max - min + 1);
}

void print_set(const string &name, const set<int> &s)
{
    cout << name;
    bool first = true;
    for (int x : s)
    {
        if (first)
        {
            first = false;
            cout << ": [";
        } else
        {
            cout << ", ";
        }
        cout << x;
    }
    cout << "]" << endl;
}

bool contains_all_but_b(const set<int> &A, set<int> U, const set<int> &B)
{
    for (int x : B)
    {
        U.erase(x);
    }
    return U == A;
}

int main()
{
    srand(time(nullptr));

    int a = 0, b = 100, c = 50, d = 100, N = 10;

    set<int> U, A, B;

    while (U.size() != (size_t)N)
    {
        U.insert(rand_in_range(a, b));
    }

    for (int x = c; x <= d; ++x)
    {
        if (U.count(x))
        {
            B.insert(x);
        }
    }

    while (!contains_all_but_b(A, U, B))
    {
        size_t idx = rand_in_range(0, U.size() - 1);
        int elem = *next(U.cbegin(), idx);
        if (c <= elem && elem <= d)
        {
            continue;
        }
        A.insert(elem);
    }

    set<int> un, na, nb, nanb, nnanb;
    set_union(A.begin(), A.end(), B.begin(), B.end(), inserter(un, un.begin()));

    set_difference(U.begin(), U.end(), A.begin(), A.end(), inserter(na, na.begin()));
    set_difference(U.begin(), U.end(), B.begin(), B.end(), inserter(nb, nb.begin()));
    set_intersection(na.begin(), na.end(), nb.begin(), nb.end(), inserter(nanb, nanb.begin()));
    set_difference(U.begin(), U.end(), nanb.begin(), nanb.end(), inserter(nnanb, nnanb.begin()));

    print_set("U", U);
    print_set("A", A);
    print_set("B", B);
    print_set("un", un);
    print_set("nnanb", nnanb);

    cout << "equal? " << (un == nnanb) << endl;

    for (int x : un)
    {
        if ((x % 2) != 0)
        {
            cout << x << " ";
        }
    }
    cout << endl;
}

