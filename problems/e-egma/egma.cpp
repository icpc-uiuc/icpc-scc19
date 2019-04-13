#include <iostream>
#include <vector>

using namespace std;

const int maxN = 5e5 + 10;

int n, q, a[maxN], t[5 * maxN], res[maxN];
vector < pair < int, int > > qu[maxN];

void update(int k, int l, int r, int i, int v) {
    if (i < l || r < i) return;
    if (l == r) {
        t[k] = v;
        return;
    }
    int mid = (l + r) >> 1;
    update(k * 2, l, mid, i, v);
    update(k * 2 + 1, mid + 1, r, i, v);
    t[k] = min(t[k * 2], t[k * 2 + 1]);
}

int get(int k, int l, int r, int x) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    if (t[k * 2] < x) return get(k * 2, l, mid, x);
    return get(k * 2 + 1, mid + 1, r, x);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    cin >> q;
    for (int i = 1; i <= q; ++i) {
        int l, r; scanf("%d %d", &l, &r);
        qu[r].push_back({l, i});
    }
    for (int i = 1; i <= n; ++i) {
        if (a[i] > n + 1) continue;
        update(1, 0, n + 1, a[i], i);
        for (auto p : qu[i])
            res[p.second] = get(1, 0, n + 1, p.first);
    }
    for (int i = 1; i <= q; ++i) printf("%d\n", res[i]);
}
