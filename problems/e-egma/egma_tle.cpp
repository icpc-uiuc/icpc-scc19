#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
#include <map>

using namespace std;

const int maxN = 1e5 + 10;

typedef pair < int, int > pi;

map < pi, int > mm;
vector < int > val;
int n, q, a[maxN];

int get_mex(int l, int r) {
    if (mm.count({l, r})) return mm[make_pair(l, r)];
    val.clear();
    for (int i = l; i <= r; ++i) val.push_back(a[i]);
    sort(val.begin(), val.end());
    int mex = 0;
    for (int v : val)
        if (mex == v) ++mex;
        else if (mex < v) break;
    return mm[make_pair(l, r)] = mex;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    cin >> q;
    for (int i = 1; i <= q; ++i) {
        int t; scanf("%d", &t);
        if (t == 1) {
            int x, v; scanf("%d %d", &x, &v);
            mm.clear(); a[x] = v;
        } else {
            int l, r; scanf("%d %d", &l, &r);
            cout << get_mex(l, r) << endl;
        }
    }
}
