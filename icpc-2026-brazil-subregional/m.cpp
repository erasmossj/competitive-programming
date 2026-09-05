#include <bits/stdc++.h>
#define ll long long int
#define vpi vector<pair<ll,ll>>
#define vvpi vector<vector<pair<ll,ll>>>
#define vi vector<ll>
#define pi pair<ll,ll>>

using namespace std;

void dijkstra(ll v0, vector<vector<pair<ll, ll>>> &adj, vector<ll> &dist)
{
    ll n = adj.size();

    dist[v0] = 0;

    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    pq.push({dist[v0], v0});

    while (!pq.empty())
    {
        auto [d, v] = pq.top();
        pq.pop();
        for (auto [u, w] : adj[v])
            if (dist[u] > dist[v] + w)
            {
                dist[u] = dist[v] + w;
                pq.push({dist[u], u});
            }
    }
}

int main()
{
    int n, m, k; cin >> n >> m >> k;

    vvpi adj0(n*(k+1), vpi());
    vvpi adj(n*(k+1), vpi());
    vi dist(n*(k+1), LLONG_MAX/2);
    vvpi mapping(n, vpi());

    for(int i=0;i<m;i++)
    {
        int v, u, f, w; cin >> v >> u >> f >> w;
        v--; u--;
        if(w != -1)
        {
            mapping[v].push_back({u,w});
            mapping[u].push_back({v,w});
        }
        adj0[v].push_back({u,f});
        adj0[u].push_back({v,f});
    }

    for (int i = 0; i<=k; i++)
    {
        for(int v=0; v<n; v++)
        {
            for(auto u : adj0[v])
            {
                int f = u.second;
                adj[v+i*n].push_back({u.first+i*n, f});
            }
            if (!mapping[v].empty() && i > 0)
            {
                for (auto w : mapping[v])
                {
                    int u = w.first, f = w.second;
                    adj[v+n*(i-1)].push_back({u+i*n, f});
                }
            }
        }
    }

    dijkstra(0, adj, dist);

    ll ans = LLONG_MAX;

    for(int i=0; i<=k; i++) ans = min(ans, dist[n+n*i-1]);

    cout << ans << endl;
}