#include<bits/stdc++.h>
using namespace std;

string s[10],stmp;
stringstream ss;
vector<string> sep[10];
int maxn[11];
string exp_ans[10],user_ans[10];

int main(int argc,char *args[]){
   freopen(args[2],"r",stdin);
   int n;
   cin>>n;
   getline(cin,stmp);
   for(int i=0;i<n;i++){
      getline(cin,s[i]);
      ss.clear();
      ss.str("");
      ss<<s[i];
      int cnt=0;
      while(ss>>stmp){
         sep[i].push_back(stmp);
         maxn[cnt]=max(maxn[cnt],(int) sep[i].back().size());
         cnt++;
      }
   }
   for(int i=0;i<n;i++){
      for(int j=0;j<sep[i].size();j++){
         exp_ans[i]+=sep[i][j];
         if(j!=sep[i].size()-1){
            for(int k=sep[i][j].size();k<=maxn[j];k++)
               exp_ans[i]+=' ';
         }
      }
   }
   freopen(args[4],"r",stdin);
   for(int i=0;i<n;i++){
      getline(cin,user_ans[i]);
      while(user_ans[i].size()&&user_ans[i].back()==' ')
         user_ans[i].pop_back();
   }
   if(cin>>stmp){
      cout<<0<<endl;
      return 0;
   }
   for(int i=0;i<n;i++)
      if(user_ans[i]!=exp_ans[i]){
         cout<<0<<endl;
         return 0;
      }
   cout<<1<<endl;
   fclose(stdin);
}
