#include <bits/stdc++.h>
#define ll long long
#define vvpi vector<vector<pair<ll,ll>>>
#define vvi vector<vector<ll>>
#define vpi vector<pair<ll,ll>>
#define vi vector<ll>
#define pi pair<ll,ll>
#define pb push_back
#define fi first
#define si second
#define loop(i, x, f) for(int i=x; i<f; i++)
#define MAXN 501

using namespace std;

ll n, m1, m2;
ll matching[MAXN][MAXN] = {0};
vvi adji(MAXN, vi());
vvi adjf(MAXN, vi());
vpi edgesi;
vpi edgesf;

vector<vector<int>> g;
vector<int> mt;
vector<bool> used;

bool try_kuhn(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (int to : g[v]) {
        if (mt[to] == -1 || try_kuhn(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

int solve()
{
    if (m1 != m2) return -1;
    loop(v, 0, n)
    {
        for(auto u : adji[v])
            if (matching[v][u] == 1 && v < u) edgesi.pb({v, u}); // v < u para evitar duplicação de arestas, mesmo sendo um grafo bidirecional, isso afeta a montagem do grafo bipartite
    }
    loop(v, 0, n)
    {
        for(auto u : adjf[v])
            if (matching[v][u] == 1 && v < u) edgesf.pb({v, u});
    }
    if (edgesi.empty()) return 0;
    g.resize(edgesi.size());
    loop(i, 0, edgesi.size())
        loop(j, 0, edgesf.size())
        {
            auto e1 = edgesi[i], e2 = edgesf[j];
            if (e1.fi == e2.fi || e1.fi == e2.si || e1.si == e2.fi || e1.si == e2.si)
            {
                g[i].push_back(j);
            }
        }
    int matchs = 0;
    mt.assign(g.size(), -1);
    for (int v = 0; v < g.size(); ++v) {
        used.assign(g.size(), false);
        matchs += try_kuhn(v);
    }
    return 2*edgesi.size() - matchs;
}

signed main()
{
    cin >> n >> m1 >> m2;
    loop(i, 0, m1)
    {
        int v, u; cin >> v >> u;
        v--; u--;
        adji[v].pb(u);
        adji[u].pb(v);
        matching[v][u]++;
        matching[u][v]++;
    }
    loop(i, 0, m2)
    {
        int v, u; cin >> v >> u;
        v--; u--;
        adjf[v].pb(u);
        adjf[u].pb(v);
        matching[v][u]++;
        matching[u][v]++;
    }
    
    cout << solve() << endl;
}