#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

const int maxN = 1e5 + 10, blockSize = 50;

typedef pair < int, int > pi;
typedef set < pi >::iterator iter;

struct Update { int p, fr, to, t; };
struct Query { int l, r, t; };

int n, q, a[maxN], b[maxN], res[maxN];
unordered_map < int, int > cnt;
vector < Update > updates;
vector < Query > queries;
bool is_query[maxN];
set < pi > seg;

void merge(iter it) {
    auto nit = next(it);
    int l = it->first, r = it->second;
    if (nit != seg.end() && nit->first == it->second + 1) {
        r = nit->second;
        seg.erase(nit);
    }
    if (it != seg.begin()) {
        auto pit = prev(it);
        if (pit->second == it->first - 1) {
            l = pit->first;
            seg.erase(pit);
        }
    }
    if (it->first != l || it->second != r) {
        seg.erase(it);
        seg.insert({l, r});
    }
}

void add(int v) {
    ++cnt[v];
    if (cnt[v] == 1) {
        seg.insert({v, v});
        merge(seg.lower_bound({v, v}));
    }
}

void remove(int v) {
    --cnt[v];
    if (cnt[v] == 0) {
        auto it = seg.upper_bound({v, n + 1}); --it;
        if (it->first <= v - 1) seg.insert({it->first, v - 1});
        if (it->second >= v + 1) seg.insert({v + 1, it->second});
        seg.erase(it);
    }
}

void apply(int l, int r, int p, int v) {
    if (l <= p && p <= r)
        add(v), remove(a[p]);
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
            make_pair(get_block(x.l), make_pair(get_block(x.r), x.t)) <
            make_pair(get_block(y.l), make_pair(get_block(y.r), y.t));
    });
    int l = 1, r = 0, now = 0;
    for (auto& qu : queries) {
        for (; updates[now].t > qu.t; --now) apply(l, r, updates[now].p, updates[now].fr);
        for (; updates[now + 1].t <= qu.t; ++now)
            apply(l, r, updates[now + 1].p, updates[now + 1].to);
        while (r < qu.r) ++r, add(a[r]);
        while (r > qu.r) remove(a[r]), --r;
        while (l < qu.l) remove(a[l]), ++l;
        while (l > qu.l) --l, add(a[l]);
        res[qu.t] = seg.begin()->first ? 0 : seg.begin()->second + 1;
    }
    for (int i = 1; i <= q; ++i) 
        if (is_query[i]) printf("%d\n", res[i]);
}
