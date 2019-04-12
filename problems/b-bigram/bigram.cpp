#include <bits/stdc++.h>

using namespace std;

int gcd (int p, int q) { return q == 0 ? p : gcd(q, p%q); }

int main () {
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  map<pair<string,string>,int> num;
  map<string,int> den;
  int n; cin >> n;
  for (int i = 0; i < n; i++) {
    int m; cin >> m;
    vector<string> s(m);
    for (int i = 0; i < m; i++) cin >> s[i];
    for (int i = 0; i < m-1; i++) {
      num[{s[i], s[i+1]}] += 1;
      den[s[i]] += 1;
    }
  }
  int q; cin >> q;
  while (q--) {
    string s, t; cin >> s >> t;
    if (den[s] == 0) printf("Insufficient data\n");
    else {
      int g = gcd(num[{s,t}], den[s]);
      int p = num[{s,t}] / g;
      int q = den[s] / g;
      printf("%d/%d\n", p, q);
    }
  }

  return 0;
}

