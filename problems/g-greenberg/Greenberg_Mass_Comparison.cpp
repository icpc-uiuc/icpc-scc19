#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;
template<typename T>
string to_string(const T& x){
   stringstream ss;
   ss<<x;
   return ss.str();
}

struct bigN:vector<ll>{
   const static int base=1000000000,width=9;
   bool negative;
   void trim(){
      while(size()&&!back())  pop_back();
      if(empty()) negative=0;
   }
   bigN(string s){
      if(s.empty())  return;
      if(s[0]=='-'){
         negative=true;s=s.substr(1);
      }
      else negative=false;
      for(int i=(int)s.size()-1;i>=0;i-=width){
         ll t=0;
         for(int j=max(0,i-width+1);j<=i;j++)
            t=t*10+s[j]-'0';
         push_back(t);
      }
      trim();
   }
   template<typename T>
   bigN(const T& x):bigN(to_string(x)){}
   bigN():negative(0){}
   void carry(){
      for(size_t i=0;i<size();i++){
         if(at(i)>=0&&at(i)<base)   continue;
         if(i+1u==size())  push_back(0);
         ll r=at(i)%base;
         if(r<0)  r+=base;
         at(i+1)+=(at(i)-r)/base;
         at(i)=r;
      }
   }
   bigN operator+(const bigN &b)const{
      bigN res =*this;
      if(b.size()>size())  res.resize(b.size());
      for(size_t i=0;i<b.size();i++)   res[i]+=b[i];
      res.carry();res.trim();
      return res;
   }
   bigN operator*(const bigN &b)const{
      bigN res;
      res.negative=(negative!=b.negative);
      res.resize(size()+b.size());
      for(size_t i=0;i<size();i++)
         for(size_t j=0;j<b.size();j++)
            if((res[i+j]+=at(i)*b[j])>=base){
               res[i+j+1]+=res[i+j]/base;
               res[i+j]%=base;
            }
      res.trim();
      return res;
   }
   friend istream& operator>>(istream &ss,bigN &b){
		string s;
      ss>>s;b=s;
		return ss;
	}
   friend ostream& operator<<(ostream &ss,bigN &b){
      if(b.negative) ss<<'-';
      ss<<(b.empty()?0:b.back());
      for(int i=(int) b.size()-2;i>=0;i--)
         ss<<setw(width)<<setfill('0')<<b[i];
      return ss;
   }
};

const int MAXN = 101;
bigN b[MAXN];
bigN c[MAXN][MAXN];

int main(){
   ios_base::sync_with_stdio(0);
   cin.tie(0);
   for(int i=0;i<MAXN;i++) c[i][0]=1;
   for(int i=1;i<MAXN;i++)
      for(int j=0;j<=i;j++){
         if(j==0)
            c[i][j]=1;
         else
            c[i][j]=c[i-1][j]+c[i-1][j-1];
      }
   for(int i=0;i<MAXN;i++)
      b[i]=0;
   b[0]=1;
   for(int i=1;i<MAXN;i++)
      for(int j=0;j<i;j++)
         b[i]=b[i]+b[j]*c[i-1][j];
   int t;
   cin>>t;
   int n;
   while(t--){
      cin>>n;
      cout<<b[n]<<endl;
   }
}
