#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

const int maxN = 5010, modP = 1e9 + 7;

struct City {
    int v, t;
};

vector < int > p;
City c[maxN];
int n, res;

bool verify(int i, int j) {
    if (c[i].t == 1 && c[i].v < c[j].v)
        return true;
    if (c[i].t == 2 && c[i].v > c[j].v)
        return true;
    return false;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) scanf("%d", &c[i].v);
    for (int i = 1; i <= n; ++i) scanf("%d", &c[i].t);
    if (n == 2) {
        cout << verify(1, n) << endl;
        return 0;
    }
    for (int i = 1; i <= n - 2; ++i) p.push_back(i);
    do {
        bool ok = verify(1, p[0] + 1) & verify(p.back() + 1, n);
        for (int i = 0; i + 1 < p.size(); ++i)
            ok &= verify(p[i] + 1, p[i + 1] + 1);
        res = (res + ok) % modP;
    } while (next_permutation(p.begin(), p.end()));
    cout << res << endl;
}
