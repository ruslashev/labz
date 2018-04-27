#include <iostream>
#include <functional>
#include <string>

using namespace std;

int solve(int nx)
{
    for (int x = 0; x <= nx; ++x)
        if (x + (x % 5) + 1 == nx)
            return x;
    exit(1);
}

int main()
{
    int count = 0, branch_count = 0, a = 4, b = 24, p1 = 9, p2 = 18;

    function<void (int, int, string, bool)> calc =
        [&](int x, int fin, string way, bool pred_sat)
        {
            branch_count++;
            if (x < fin)
            {
                int x1 = x + 2, x2 = x + (x % 5) + 1;
                calc(x1, fin, way + "+2 ",
                        pred_sat | (x1 == p1) | (x1 == p2));
                calc(x2, fin, way + "+" + to_string(x2 - x) + " ",
                        pred_sat | (x2 == p1) | (x2 == p2));
            } else if (x == fin && pred_sat)
            {
                count++;
                cout << way << endl;
            }
        };
    cout << a << " -> " << b << endl;
    calc(a, b, "", 0);
    cout << "ways: " << count << endl;
    cout << "branches: " << branch_count << endl;
    cout << endl;
    count = branch_count = 0;

    function<void (int, int, string, bool)> calc_rev =
        [&](int x, int fin, string way, bool pred_sat)
        {
            branch_count++;
            if (x > fin)
            {
                int x1 = x - 2, x2 = solve(x);
                calc_rev(x1, fin, way + "-2 ",
                        pred_sat | (x1 == p1) | (x1 == p2));
                calc_rev(x2, fin, way + "-" + to_string(x - x2) + " ",
                        pred_sat | (x2 == p1) | (x2 == p2));
            } else if (x == fin && pred_sat)
            {
                count++;
                cout << way << endl;
            }
        };
    cout << b << " -> " << a << endl;
    calc_rev(b, a, "", 0);
    cout << "ways: " << count << endl;
    cout << "branches: " << branch_count << endl;
}

