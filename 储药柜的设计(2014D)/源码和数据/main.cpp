#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <set>
#include <fstream>
#include <ostream>
#include <cmath>
#include <tuple>
#include "data.h"
using namespace std;
std::ofstream outFile;
std::ifstream fin;

vector<pair<int,int>>v(1919);
vector<int>ans2;
int now_ans = 47;
//weight[N]
//length[N]
//height[N]

void solve_file();
void solve();
void solve2();
void solve2_f(int,int,int);

int k=0;
int now_rong = 0x3f3f3f3f;
int main() {
    solve();
    //solve2();
    sort(v.begin(),v.end(),[&](pair<int,int> x, pair<int,int> y){
        if(x.first == y.first)return x.second < y.second;
        return x.first < y.first;
    });
    solve2_f(0,1,0);
    cout << k;
    return 0;
}

void solve2_f(int start ,  int cnt ,int rong){
    if(cnt > now_ans)return ;
    for(int i = v[start].second;i>=v[start].first;i--){
        bool flag = false;
        int sum = 0;
        for(int j=start;j<v.size();j++){
            if(v[j].first>i){
                flag = true;
                ans2.push_back(i);
                solve2_f(j,cnt+1,rong + sum);
                ans2.pop_back();
                break;
            }
            sum += i-v[j].first;
        }
        if(!flag){
            k++;
            ans2.push_back(i);
            if(ans2[3]>58);
            else{
                for(auto x:ans2)cout << x << ' ';
                cout << "rong:" << rong;
                cout << '\n';
            }
            ans2.pop_back();
            now_ans = min(now_ans,cnt);
        }
    }
}

void solve2(){
    sort(v.begin(),v.end(),[&](pair<int,int> x, pair<int,int> y){
       if(x.first == y.first)return x.second < y.second;
       return x.first < y.first;
    });
    int cnt = 0 , start=0 , end;
    vector<pair<int,int>>ans;
    while(cnt < 1919){
        double x = v[start].second;
        cnt++;
        bool flag = false;
        for(int i=start;i<v.size();i++){
            if(v[i].first>x){
                end = i-1;
                flag = true;
                break;
            }
        }
        if(flag)
            ans.push_back(make_pair(v[end].first,x));
        else{
            ans.push_back(make_pair(v[v.size()-1].first,x));
            break;
        }
        start = end+1;
    }
    cout << cnt << '\n';
    for(auto x:ans){
        cout << x.first << ',' << x.second << '\n';
    }
}
void solve(){
    double a[N],b[N];
    for(int i=1;i<=1919;i++){
        a[i] = 2+weight[i];
        b[i] = min({2.0*weight[i],sqrt(weight[i]*weight[i] + height[i]*height[i]), sqrt(weight[i]*weight[i] + length[i]*length[i])});
        if((long long)b[i] == b[i])b[i]--;
        b[i] = (int)b[i];
        v[i-1].first = a[i]  , v[i-1].second=b[i];
    }
}
void solve_file(){
    outFile.open("附件1-药盒型号.xlsx");
    fin.open("附件1-药盒型号.xlsx");
    if (!outFile.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return ;
    }
    if (!fin.is_open())
    {
        std::cerr << "无法打开文件" << std::endl;
        return ;
    }
    string s;
    while(getline(fin,s)){
        cout << s << '\n';
    }
    fin.close();
    outFile.close();
}