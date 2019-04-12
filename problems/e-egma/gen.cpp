#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

typedef pair < int, int > pi;

vector < int > a;
set < pi > qu;

int getn(int testcase) {
    if (testcase < 2) return (rand() % 20) + 1;
    if (testcase < 5) return (rand() % 500000) + 1;
    return 500000;
}

int getq(int testcase) {
    if (testcase < 2) return (rand() % 10) + 1;
    if (testcase < 5) return (rand() % 500000) + 1;
    return 500000;
}

int geta(int testcase) {
    if (testcase < 5) return rand() % 10;
    if (testcase < 10) return rand() % 500000;
    return rand() % 100000;
}

pi getquery(int testcase, int n) {
    if (testcase < 5) {
        int l = (rand() % n) + 1;
        int r = l + (rand() % (n - l + 1));
        return make_pair(l, r);
    }
    int len = (rand() % (n / 2)) + (n / 2);
    int l = (rand() % (n - len)) + 1;
    return make_pair(l, l + len);
}

void printcase(FILE* out, int testcase) {
    int n = a.size(), q = qu.size();
    fprintf(out, "%d\n", n);
    for (int i = 0; i < n; ++i)
        fprintf(out, "%d ", a[i]);
    fprintf(out, "\n");
    fprintf(out, "%d\n", q);
    for (auto p : qu)
        fprintf(out, "%d %d\n", p.first, p.second);
    fclose(out);
}

int main()
{
    srand(23041997);

    for (int testcase = 0; testcase < 16; ++ testcase) {
        cout << "Generating test " << testcase << endl;
        char filename[100];
        sprintf(filename, "%d.in", testcase);
        FILE* out = fopen(filename, "w");
        a.clear(); qu.clear();
        if (testcase < 15) {
            int n = getn(testcase);
            for (int i = 0; i < n; ++i)
                a.push_back(geta(testcase));
            int q = getq(testcase);
            if ((1ll * n * (n - 1)) < 2ll * q)
                q = (n * (n - 1)) / 2;
            for (int i = 0; i < q; ++i) {
                auto p = getquery(testcase, n);
                while (qu.count(p))
                    p = getquery(testcase, n);
                qu.insert(getquery(testcase, n));
            }
        } else {
            int n = 500000, q = 500000;
            for (int i = 1; i <= n; ++i) a.push_back(i - 1);
            random_shuffle(a.begin(), a.end());
            int l = 1, len = n;
            for (int i = 0; i < q; ++i) {
                qu.insert({l, l + len - 1});
                ++l;
                if (l + len - 1 > n) --len, l = 1; 
            }
        }
        printcase(out, testcase);

        char ansfilename[100];
        sprintf(ansfilename, "%d.out", testcase);
        char command[200];
        sprintf(command, "../a.out < %s > %s", filename, ansfilename);
        system(command);

        /*sprintf(ansfilename, "%d_tle.out", testcase);
        sprintf(command, "../b.out < %s > %s", filename, ansfilename);
        system(command);*/
    }
    return 0;
}
