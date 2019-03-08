#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100000;
const int MAXM = 100000;
int a[100001],b[100001],c[100001];
int num[100001];
const double p = 0.90;
bool randbool(){
   if(double (rand()%1000000)/1000000<p)
      return true;
   else
      return false;
}
struct EDGE{
   int A,B;
   EDGE(){}
   EDGE(int AA,int BB){A=AA;B=BB;}
};
vector<EDGE> v;
int main(){
   ios_base::sync_with_stdio(0);
   cin.tie(0);
   srand(time(NULL));
   for(int i=0;i<MAXN;i++)
      num[i]=i+1;
   for(int i=1;i<MAXN;i++)
      b[i]=i;
   for(int i=1;i<MAXN;i++)
      a[i]=rand()%i;
   for(int i=0;i<MAXM;i++)
      c[i]=rand()%MAXM+1;
   random_shuffle(num,num+MAXN);
   int cnt = 0;
   for(int i=1;i<MAXN;i++){
      if(randbool()){
         v.push_back(EDGE(num[a[i]],num[b[i]]));
         cnt++;
      }
   }

   cout<<MAXN<<' '<<cnt<<endl;
   for(int i=0;i<v.size();i++)
      cout<<v[i].A<<' '<<v[i].B<<endl;
}
