#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

const int maxN = 1e5 + 10, blockSize = 600, maxV = maxN;

typedef pair < int, int > pi;
typedef set < pi >::iterator iter;

struct Update { int p, fr, to, t; };
struct Query { int l, r, t; };
struct Node { int l, r, s, v; };

int n, q, a[maxN], b[maxN], res[maxN], cnt_op, cntl, cntr, cntt, num_node;
vector < Update > updates;
vector < Query > queries;
Node node[maxN * 50];
bool is_query[maxN];

int update(int k, int l, int r, int i, int v) {
    if (i < l || r < i) return k;
    if (k == 0) k = ++num_node;
    if (l == r) {
        node[k].v += v;
        node[k].s = node[k].v > 0;
        return k;
    }
    int mid = (l + r) >> 1;
    node[k].l = update(node[k].l, l, mid, i, v);
    node[k].r = update(node[k].r, mid + 1, r, i, v);
    node[k].s = node[node[k].l].s + node[node[k].r].s;
    return k;
}

int get(int k, int l, int r) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    if (!node[k].l) return l;
    if (node[node[k].l].s < mid - l + 1)
        return get(node[k].l, l, mid);
    if (!node[k].r) return mid + 1;
    return get(node[k].r, mid + 1, r);
}

void apply(int l, int r, int p, int v) {
    if (l <= p && p <= r)
        update(1, 0, maxV, v, 1), update(1, 0, maxV, a[p], -1);
    a[p] = v;
}

int get_block(int x) {
    return (x - 1) / blockSize;
}

int main() {
    cin >> n; num_node = 1;
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
        for (; updates[now].t > qu.t; --now) apply(l, r, updates[now].p, updates[now].fr), ++cntt;
        for (; updates[now + 1].t <= qu.t; ++now)
            apply(l, r, updates[now + 1].p, updates[now + 1].to), ++cntt;
        while (r < qu.r) ++r, update(1, 0, maxV, a[r], 1), ++cntr;
        while (r > qu.r) update(1, 0, maxV, a[r], -1), --r, ++cntr;
        while (l < qu.l) update(1, 0, maxV, a[l], -1), ++l, ++cntl;
        while (l > qu.l) --l, update(1, 0, maxV, a[l], 1), ++cntl;;
        res[qu.t] = get(1, 0, maxV);
        //cout << qu.t << endl;
    }
    for (int i = 1; i <= q; ++i) 
        if (is_query[i]) printf("%d\n", res[i]);
    cout << "NUM OP: " << cnt_op << endl;
    cout << "NUM T: " << cntt << endl;
    cout << "NUM L: " << cntl << endl;
    cout << "NUM R: " << cntr << endl;
}
