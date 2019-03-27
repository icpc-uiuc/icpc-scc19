#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int NMAX = 100000;
int n;
vector<int> adj[NMAX];
int p[NMAX], siz[NMAX];
vector<int> c[NMAX];

void dfs (int u) {
  siz[u] = 1;
  for (int v : adj[u]) {
    if (v == p[u]) continue;
    p[v] = u;
    c[u].push_back(v);
    dfs(v);
    siz[u] += siz[v];
  }
}

int main () {
  int n; cin >> n;
  for (int i = 0; i < n-1; i++) {
    int u, v, w; cin >> u >> v >> w; u--; v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs(0);
  LL ans = (LL)n * (n-1) * (n-2) / 6;
  for (int i = 0; i < n; i++) {
    ans -= (LL)(siz[i] - 1) * (n - siz[i]);
    ans -= (LL)(siz[i] - 1) * (siz[i] - 2) / 2;
    for (int v : c[i]) ans += (LL)siz[v] * (siz[v] - 1) / 2;
  }
  cout << ans << endl;

  return 0;
}

