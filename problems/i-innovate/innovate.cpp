#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

vector<string> split(const string &text, char sep) {
  vector<string> tokens;
  size_t start = 0, end = 0;
  while ((end = text.find(sep, start)) != string::npos) {
    tokens.push_back(text.substr(start, end - start));
    start = end + 1;
  }
  tokens.push_back(text.substr(start));
  return tokens;
}

void moveStrings(vector<vector<string> > & splits, int index) {
  int shift = 0;
  for (int i = 0; i < splits.size(); ++i) {
    if (index >= splits[i].size()) continue; // would go out of bounds, don't need to align
    shift = max(shift, (int) splits[i][index].size());
  }
  for (int i = 0; i < splits.size(); ++i) {
    if (index >= splits[i].size()) continue;
    int currSize = splits[i][index].size();
    if (currSize == shift && index != splits[i].size() - 1) {
      splits[i][index] += " ";
      continue;
    }
    while (currSize < shift + 1) {
      splits[i][index] += " ";
      currSize++;
    }
  }
}

int main() {
      int n;
      cin >> n;
      vector<string> strs;
      string line;
      for (int i = 0; i < n + 1; ++i) {
        getline(cin, line);
        cout << line << endl;
        if (i > 0) strs.push_back(line);
      }
      vector<vector<string> > splits(strs.size(), vector<string>());
      for (int i = 0; i < strs.size(); ++i) {
        splits[i] = split(strs[i], ' '); // split by whitespace
      }

      for (int i = 0; i < strs.size(); ++i) moveStrings(splits, i); // call helper

      for (int i = 0; i < strs.size(); ++i) {
        string temp = "";
        for (auto & str: splits[i]) {
          temp += str;
        }
        cout << temp << endl;
      }
      return 0;
}
