#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10;
const int MAXM = 100000;
int a[100001],b[100001],c[100001];
int num[100001];
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
   cout<<MAXN<<endl;
   for(int i=1;i<MAXN;i++)
      cout<<num[a[i]]<<' '<<num[b[i]]<<' '<<c[i]<<endl;
}
