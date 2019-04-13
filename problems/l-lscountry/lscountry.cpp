#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int maxN = 5010, modP = 1e9 + 7;

struct City {
    bool operator < (const City& rhs) const {
        return v < rhs.v;
    }
    int i, v, t;
};

int n, f[maxN][maxN][2][2];
City c[maxN];

int dp(int i, int j, bool s, bool e) {
    if (i > n) return (j == 1 && s && e);
    if (f[i][j][s][e] != -1) return f[i][j][s][e];
    int& tmp = f[i][j][s][e]; tmp = 0;
    
    // Add new subpath
    // 1. Endpoints:
    if (c[i].i == 1 && c[i].t == 1)  // Left endpoint
        tmp = (1ll * tmp + dp(i + 1, j + 1, true, e)) % modP;
    if (c[i].i == n) // Right endpoint
        tmp = (1ll * tmp + dp(i + 1, j + 1, s, true)) % modP;
    // 2. Middle:
    if (c[i].i > 1 && c[i].i < n && c[i].t == 1)
        tmp = (1ll * tmp + dp(i + 1, j + 1, s, e)) % modP;

    // Extend existing subpath
    // 1. Endpoints:
    if (c[i].i == 1 && c[i].t == 2) { // Left endpoint
        // Extend one with 2 open endpoints
        if (j - e > 0)
            tmp = (1ll * tmp + 1ll * (j - e) * dp(i + 1, j, true, e)) % modP;
        // Extend one with only 1 open endpoint
        // Happens only when 1 is added last
        if (i == n && j == 1 && e)
            tmp = (1ll * tmp + 1ll * dp(i + 1, j, true, e)) % modP;
    }
    if (c[i].i == n) {
        // Extend one with 2 open endpoints
        if (j - s > 0)
            tmp = (1ll * tmp + 1ll * (j - s) * dp(i + 1, j, s, true)) % modP;
        // Extend one with only 1 open endpoint
        // Happens only when n is added last
        if (i == n && j == 1 && s)
            tmp = (1ll * tmp + 1ll * dp(i + 1, j, s, true)) % modP;
    }
    // 2. Middle:
    if (c[i].i > 1 && c[i].i < n) {
        // Extend one with 2 open endpoints
        if (j - s - e > 0)
            tmp = (1ll * tmp + 1ll * (j - s - e) * dp(i + 1, j, s, e)) % modP;
        // Extend one with only 1 open endpoint
        if (c[i].t == 1 && s)
            tmp = (1ll * tmp + dp(i + 1, j, s, e)) % modP;
        if (c[i].t == 2 && e)
            tmp = (1ll * tmp + dp(i + 1, j, s, e)) % modP;
    }

    // Merge 2 existing subpaths
    if (c[i].i > 1 && c[i].i < n && c[i].t == 2) {
        // 1. Middle with middle
        if (j - s - e >= 2) {
            int num = (j - s - e) * (j - s - e - 1);
            tmp = (1ll * tmp + 1ll * num * dp(i + 1, j - 1, s, e)) % modP;
        }
        // 2. Endpoints with middle
        if (j - s - e > 0) {
            tmp = (1ll * tmp + 1ll * s * (j - s - e) * dp(i + 1, j - 1, s, e)) % modP;
            tmp = (1ll * tmp + 1ll * e * (j - s - e) * dp(i + 1, j - 1, s, e)) % modP;
        }
        // 3. Endpoint with endpoint (last add)
        if (i == n)
            tmp = (1ll * tmp + dp(i + 1, j - 1, s, e)) % modP;
    }

    return f[i][j][s][e] = tmp;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) scanf("%d", &c[i].v), c[i].i = i;
    for (int i = 1; i <= n; ++i) scanf("%d", &c[i].t);
    sort(c + 1, c + n + 1);
    /*for (int i = 1; i <= n; ++i) cout << c[i].i << " ";
    cout << endl;*/
    memset(f, 255, sizeof(f));
    cout << dp(1, 0, 0, 0) << endl;
}
