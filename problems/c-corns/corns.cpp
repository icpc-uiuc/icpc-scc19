#include<bits/stdc++.h>
using namespace std;

int cnt[200001],now;
bool dp[2][200001];
int n,W;
queue<int> q;

int main(){
   cin>>n>>W;
   dp[0][0]=true;
   for(int i=0,p;i<n;i++){
      cin>>p;cnt[p]++;
   }
   for(int i=1;i<=W;i++){
      if(cnt[i]){
         now^=1;
         for(int r=0;r<i;r++){
            while(!q.empty()) q.pop();
            for(int j=0;j*i+r<=W;j++){
               if(dp[now^1][j*i+r]) q.push(j);
               while(!q.empty()&&j-q.front()>cnt[i])  q.pop();
               if(!q.empty()) dp[now][j*i+r]=true;
            }
         }
      }
   }
   for(int i=W;;i--)
      if(dp[now][i]){
         cout<<i<<endl;
         break;
      }
}
