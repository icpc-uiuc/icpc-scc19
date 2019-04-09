#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

const int maxN = 1e5 + 10, blockSize = 2100, maxV = maxN;

typedef pair < int, int > pi;
typedef set < pi >::iterator iter;

struct Update { int p, fr, to, t; };
struct Query { int l, r, t; };
struct Node { int l, r, s, v; };

int n, q, a[maxN], b[maxN], res[maxN], t[maxV], cnt[maxV];
vector < Update > updates;
vector < Query > queries;
Node node[maxN * 50];
bool is_query[maxN];

void update(int x, int v) {
    if (x > n) return;
    if (x == 0) { cnt[x] += v; return; }
    if (v == -1 && cnt[x] == 1) cnt[x] = 0;
    else if (v == 1 && cnt[x] == 0) cnt[x] = 1;
    else { cnt[x] += v; return; }
    while (x <= n) {
        t[x] += v;
        x += (x & (-x));
    }
}

int get(int x) {
    int tmp = cnt[0] > 0;
    if (x == 0) return tmp;
    int tx = x;
    while (x) {
        tmp += t[x];
        x -= (x & (-x));
    }
    return tmp;
}

int get_mex() {
    if (!cnt[0]) return 0;
    int l = 1, r = n + 1, mex;
    while (l <= r) {
        int mid = (l + r) >> 1;
        int tmp = get(mid - 1);
        if (get(mid - 1) == mid) mex = mid, l = mid + 1;
        else r = mid - 1;
    }
    return mex;
}

void apply(int l, int r, int p, int v) {
    if (l <= p && p <= r)
        update(v, 1), update(a[p], -1);
    a[p] = v;
}

int get_block(int x) {
    return (x - 1) / blockSize;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), b[i] = a[i];
    cin >> q;
    updates.push_back({0, 0, 0, 0});
    updates.push_back({0, 0, 0, q + 1});
    for (int i = 1; i <= q; ++i) {
        int t; scanf("%d", &t);
        if (t == 1) {
            int x, v; scanf("%d %d", &x, &v);
            updates.push_back({x, b[x], v, i});
            b[x] = v;
        } else {
            int l, r; scanf("%d %d", &l, &r);
            is_query[i] = true;
            queries.push_back({l, r, i});
        }
    }
    sort(updates.begin(), updates.end(), [](const Update& x, const Update& y) {
        return x.t < y.t;
    });
    sort(queries.begin(), queries.end(), [](const Query& x, const Query& y) {
        return
            get_block(x.l) < get_block(y.l) || 
            (get_block(x.l) == get_block(y.l) && get_block(x.r) < get_block(y.r)) ||
            (get_block(x.l) == get_block(y.l) && get_block(x.r) == get_block(y.r) && x.t < y.t);
    });
    int l = 1, r = 0, now = 0;
    for (auto& qu : queries) {
        for (; updates[now].t > qu.t; --now) apply(l, r, updates[now].p, updates[now].fr);
        for (; updates[now + 1].t <= qu.t; ++now)
            apply(l, r, updates[now + 1].p, updates[now + 1].to);
        while (r < qu.r) ++r, update(a[r], 1);
        while (l > qu.l) --l, update(a[l], 1);
        while (r > qu.r) update(a[r], -1), --r;
        while (l < qu.l) update(a[l], -1), ++l;
        res[qu.t] = get_mex();
    }
    for (int i = 1; i <= q; ++i) 
        if (is_query[i]) printf("%d\n", res[i]);
}
