#include<bits/stdc++.h>
using namespace std;

long long int ans=0,square,n;
vector<int> edge[100001];

long long int dfs(int now,int parent){
   long long int child = 1,tmp,cnt = 0;
   for(int i=0;i<edge[now].size();i++){
      if(edge[now][i]!=parent){
         tmp=dfs(edge[now][i],now);
         child+=tmp;
         cnt+=tmp*tmp;
      }
   }
   cnt+=(n-child)*(n-child);
   ans-=(square-cnt)/2;
   return child;
}
int main(){
   ios_base::sync_with_stdio(0);
   cin.tie(0);
   int u,v,t;
   cin>>n;
   square=(n-1)*(n-1);
   for(int i=1;i<n;i++){
      cin>>u>>v>>t;
      edge[u].push_back(v);
      edge[v].push_back(u);
   }
   ans=n*(n-1)*(n-2)/6;
   dfs(1,0);
   cout<<ans<<endl;
}
