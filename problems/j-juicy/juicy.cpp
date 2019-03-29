#include<bits/stdc++.h>
using namespace std;
const int MAXN = 112;
int parent[MAXN],Rank[MAXN]; //we can’t use rank as a variable in C++
void Init(){
   for(int i=1;i<MAXN;i++){
      parent[i]=i;
      Rank[i]=1;
   }
}
int Find(int x){ // Path Compression
   return x==parent[x] ? x : parent[x] = Find(parent[x]);
}
void Union(int x,int y){ //Union by Rank
   int rootx = Find(x),rooty = Find(y);
   if(rootx!=rooty){
      if(Rank[rootx] < Rank[rooty])    swap(rootx,rooty);
      parent[rooty]=rootx;
      if(Rank[rootx] == Rank[rooty])    Rank[rootx]++;
   }
}
long double L = 1,ans;
int a,b,m;
int p,q,ansp,ansq;
bool choose[11];
struct EDGE{
   long long int happiness,energy,from,to;
   bool operator<(const EDGE& rhs)const{
      return happiness-L*energy>rhs.happiness-L*rhs.energy;
   }
}edge[1000];

int main(){
   ios_base::sync_with_stdio(0);
   cin.tie(0);
   cin>>a>>b>>m;
   for(int i=0;i<m;i++){
      cin>>edge[i].from>>edge[i].to>>edge[i].happiness>>edge[i].energy;
      if(edge[i].from<1||edge[i].from>a+b+1||edge[i].to<1||edge[i].from>a+b+1||edge[i].happiness<0||edge[i].happiness>1000000||edge[i].energy<1||edge[i].energy>1000000)
         return -1;
   }
   int limit=1<<a;
   do{
      ans=L;
      sort(edge,edge+m);
      L=-1;
      for(int i=0;i<limit;i++){
         int x=i,cnt=b;
         for(int j=1;j<=a;j++){
            if(x%2){
               choose[j]=true;
               cnt++;
            }
            else
               choose[j]=false;
            x>>=1;
         }
         p=0;q=0;
         Init();
         for(int j=0;j<m;j++){
            if(Find(edge[j].from)!=Find(edge[j].to)&&(edge[j].from>a||choose[edge[j].from])&&(edge[j].to>a||choose[edge[j].to])){
               Union(edge[j].from,edge[j].to);
               cnt--;
               p+=edge[j].happiness;
               q+=edge[j].energy;
            }
         }
         if(cnt==0&&(long double)p/q>L){
            L=(long double)p/q;
            ansp=p;
            ansq=q;
         }

      }
   }while(ans>=1e-12&&abs(ans-L)/ans>1e-7);
   cout<<(long long int)ansp/__gcd(ansp,ansq)*ansq/__gcd(ansp,ansq)<<endl;
}
