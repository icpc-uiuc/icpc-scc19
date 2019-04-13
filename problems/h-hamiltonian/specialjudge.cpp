#include<bits/stdc++.h>
using namespace std;
int expected_ans[100001];
bool visit[100001];
const int mod = 1e9+7;
int n;
long long int p,q;
long long int power(long long int x,long long int y){
   long long int res=1;
   x%=mod;
   while(y){
      if(y&1)
         res=res*x%mod;
      y>>=1;
      x=x*x%mod;
   }
   return res;
}
int f(int u,int v){
   if(u==v) return 0;
   else if(u>v)   return 1-f(v,u);
   else  return power(u*p,v*q)%2;
}
int main(int argc,char *args[]){
    //freopen(args[2],"r",stdin);
    //cin>>n>>p>>q;
    ifstream in(args[1]);
    in>>n>>p>>q;
    //freopen(args[4],"r",stdin);
    for(int i=1;i<=n;i++){
      if(cin>>expected_ans[i]){
         if(expected_ans[i]<1||expected_ans[i]>n){
            //cout<<0<<endl;
            //return 0;
            return 43;
         }
         else
            visit[expected_ans[i]]=true;
      }
      else{
         //cout<<0<<endl;
         //return 0;
         return 43;
      }
   }
   for(int i=1;i<=n;i++)
      if(!visit[i]){
         //cout<<0<<endl;
         //return 0;
         return 43;
      }
   string s;
   if(cin>>s){
      //cout<<0<<endl;
      //return 0;
      return 43;
   }
   for(int i=1;i<=n-1;i++)
      if(f(expected_ans[i],expected_ans[i+1])!=1){
         //cout<<0<<endl;
         //return 0;
         return 43;
      }
   //cout<<1<<endl;
   //return 0;
   return 42;
}
