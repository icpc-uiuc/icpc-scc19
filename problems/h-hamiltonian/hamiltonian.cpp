#include<bits/stdc++.h>
using namespace std;
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
int ans[100001],tmp[100001];
void mergesort(int l,int r){
   if(l==r) return;
   int mid=(l+r)/2;
   mergesort(l,mid);mergesort(mid+1,r);
   int cnt=l,lcnt=l,rcnt=mid+1;
   while(lcnt<=mid&&rcnt<=r){
      if(f(ans[lcnt],ans[rcnt]))
         tmp[cnt++]=ans[lcnt++];
      else
         tmp[cnt++]=ans[rcnt++];
   }
   while(lcnt<=mid)  tmp[cnt++]=ans[lcnt++];
   while(rcnt<=r)    tmp[cnt++]=ans[rcnt++];
   for(int i=l;i<=r;i++)
      ans[i]=tmp[i];
}
int main(){
   ios_base::sync_with_stdio(0);
   cin.tie(0);
   cin>>n>>p>>q;
   for(int i=1;i<=n;i++)
      ans[i]=i;
   mergesort(1,n);
   for(int i=1;i<=n;i++)
      cout<<ans[i]<<endl;
}
