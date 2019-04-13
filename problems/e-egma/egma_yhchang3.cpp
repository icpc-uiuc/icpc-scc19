#include<bits/stdc++.h>
using namespace std;

const int MAXN=500000+5,INF=500000;
struct node{
   int lson,rson,data;
}ST[MAXN*20];
int root[MAXN],stamp;
void update(int l,int r,int& duplicate,int old,int val,int index){
   ST[++stamp]=ST[old];
   duplicate=stamp;
   if(l==r){
   	ST[duplicate].data=index;
	return;
   }
   int mid=(l+r)>>1;
   if(val<=mid)   update(l,mid,ST[duplicate].lson,ST[old].lson,val,index);
   else   update(mid+1,r,ST[duplicate].rson,ST[old].rson,val,index);
   ST[duplicate].data=min(ST[ST[duplicate].lson].data,ST[ST[duplicate].rson].data);
}
int query(int l,int r,int index,int x){
   if(l==r)	return l;
   int mid=(l+r)/2;
   if(ST[ST[index].lson].data>=x)	return query(mid+1,r,ST[index].rson,x);
   else	   return query(l,mid,ST[index].lson,x);
}
int main(){
   ios_base::sync_with_stdio(0);
   cin.tie(0);
   int n,q;
   cin>>n;
   if(n<1||n>INF) return 1;
   for(int i=1,x;i<=n;i++){
      cin>>x;
      if(x>1000000000||x<0)   return 1;
      x=min(x,INF);
      update(0,INF,root[i],root[i-1],x,i);
   }
   cin>>q;
   if(q<1||q>INF) return 1;
   for(int i=0,l,r;i<q;i++){
      cin>>l>>r;
      cout<<query(0,INF,root[r],l)<<'\n';
   }
   return 0;
}
