#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t, c, k; cin >> t >> c >> k;

    if (k * t > c)
    {
        cout << c << endl;
        return 0;
    }
    cout << k*t << endl;

    return 0;
}