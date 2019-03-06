#include <bits/stdc++.h>
#define LL long long
#define NMAX 40

using namespace std;

LL b[NMAX];
LL c[NMAX][NMAX];

int main () {
  for (int i = 0; i < NMAX; i++) c[i][0] = 1;
  for (int j = 1; j < NMAX; j++) c[0][j] = 0;
  for (int i = 1; i < NMAX; i++)
    for (int j = 1; j < NMAX; j++)
      c[i][j] = c[i-1][j] + c[i-1][j-1];
  b[0] = 1;
  for (int i = 1; i < NMAX; i++) {
    for (int j = 0; j < i; j++) {
      b[i] += c[i-1][j] * b[j];
    }
  }
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    cout << b[n] << endl;
  }
  return 0;
}

