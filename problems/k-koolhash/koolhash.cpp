#include <iostream>
using namespace std;

int main() {
  int n, temp;
  cin >> n;
  while (n--) {
     cin >> temp;
     int leastSig = temp & 1, mostSig = temp & (1<<31), numSig = 0;
     while (temp) {
        numSig += (temp & 1);
        temp >>= 1;
     }
     cout << mostSig << " " << leastSig << " " << numSig << endl;
  }
  return 0;
}
