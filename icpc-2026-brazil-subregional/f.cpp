#include <bits/stdc++.h>
#define int long long int

int maxn = 1e7 + 1;

using namespace std;

signed main()
{
    int n; cin >> n;
    vector<int> ans(maxn, -1);
    ans[1] = 2;

    for(int i = 2; i <= n; i++)
    {
        if (ans[i] == -1) ans[i] = ans[i-1] + 1;
        if (ans[i] <= maxn - 1) ans[ans[i]] = i * 3;
    }

    cout << ans[n] << endl;
}