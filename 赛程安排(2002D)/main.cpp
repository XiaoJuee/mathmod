
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 20;
int n,r,nx,mr;
vector<pair<int,int> >v(200);
vector<int>chose(200);//选择
int interval[N];//间隔
int ans[N][N];//答案矩阵

//优化结构
map<pair<int,int>,int>mv;//对局->选择
int maxn[N];//当前球队比赛场次最大值(球队上次比赛的场次)

void f(int);
inline void print_ans();

int main(){
    cin >> n; // n个球队
    r = (n-3)/2;//间隔下线（下限）

    nx = (n-1)*n/2;//(n-1)+(n-2)+...+1
    //step1. 列出每一个对局(小数在前),并初始化对局
    int x = 1;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            v[x++] = make_pair(i,j);
            mv[{i,j}]=x-1;
        }
    }
    for(int i=1;i<=n;i++){
        interval[i] = -1;
        maxn[i] = -1;
    }
    //step2. 初始化选择
    if(n%2==0){
        mr = r+3;//间隔上限
        int k = 1;
        //12 34 ... n-1 n
        for(int i=1;i<=n-1;i+=2){
            ans[i][i+1] = ans[i+1][i] = (i+1)/2;
            maxn[i]=maxn[i+1] = k;
            chose[k++]=mv[{i,i+1}];
        }
        for(int i=1;i<=n-5;i+=4){
            for(int j=0;j<2;j++){
                ans[i+j][(i+j+2+n)%n] = ans[(i+j+2+n)%n][i+j] = k;
                maxn[i+j]=maxn[(i+j+2+n)%n] = k;
                chose[k++]=mv[{i+j,(i+j+2+n)%n}];
            }
        }
        f(k);
    }
    else{
        mr = r+2;//间隔上限
        int k = 1;
        //12 34 ... n-2 n-1
        for(int i=1;i<=n-2;i+=2){
            ans[i][i+1] = ans[i+1][i] = (i+1)/2;
            maxn[i]=maxn[i+1] = k;
            chose[k++]=mv[{i,i+1}];
        }
        f(k);
    }
    //print_ans();
    return 0;
}
bool flag = false;
void f(int x){
    if(flag || x == nx+1){
        if(!flag)
            print_ans();
        cout << '\n';
        return ;
    }
    //step3. 算间隔,取出必选(可选)的列表（对局列表）
    vector<int>must_chose;

    bool m_or_ke = false;//false 表示 是可选列表， 反之是必选
    vector<int>must_n;
    vector<int>no_n;
    for(int i=1;i<=n;i++){
        if(maxn[i]==-1){//没被选过
            must_n.push_back(i);
            continue;
        }
        if(m_or_ke){//必选已经出来了
            if(x-maxn[i]>mr)must_n.push_back(i);//直接加必选
            if(x-maxn[i]<=r)no_n.push_back(i);//不可选
            continue;
        }
        if(x-maxn[i]>mr){
            if(!m_or_ke)must_n.clear();
            m_or_ke = true;
            must_n.push_back(i);
        }
        else if(x-maxn[i]>r){
            must_n.push_back(i);
        }
        else{
            no_n.push_back(i);//不可选
        }
    }

    //预处理
    bool mn_[n+1];
    for(int i=1;i<=n;i++)mn_[i]=false;
    for(auto xx:must_n)mn_[xx]=true;
    for(auto xx:no_n)mn_[xx]=false;

    for(int i=1;i<=n;i++){//优化后
        if(!mn_[i])continue;
        for(int j=i+1;j<=n;j++){
            if(mn_[j]){
                must_chose.push_back(mv[{i,j}]);
            }
        }
    }

    int mi = must_chose.size();
    for(int i=0;i<mi;i++){
        //check
        if(ans[v[must_chose[i]].first][v[must_chose[i]].second])continue;
        //chose
        chose[x] = must_chose[i];
        ans[v[must_chose[i]].first][v[must_chose[i]].second] = x;
        ans[v[must_chose[i]].second][v[must_chose[i]].first] = x;

        int vf_maxn = maxn[v[must_chose[i]].first];//备份
        int vs_maxn = maxn[v[must_chose[i]].second];
        maxn[v[must_chose[i]].first] = maxn[v[must_chose[i]].second] = x;
        f(x+1);
        //cut chose
        ans[v[must_chose[i]].first][v[must_chose[i]].second] = 0;
        maxn[v[must_chose[i]].first] = vf_maxn;
        maxn[v[must_chose[i]].second] = vs_maxn;
    }
}
inline void print_ans(){

    for(int i=1;i<=n;i++){
        vector<int>v1;
        for(int j=1;j<=n;j++){
            cout << ans[i][j] << ' ';
            v1.push_back(ans[i][j]);
        }
        sort(v1.begin(),v1.end());
        cout << ',';
        vector<int>v2; // *
        for(int j=2;j<n;j++){
            cout << v1[j]-v1[j-1]-1 << ' ';
            v2.push_back(v1[j]-v1[j-1]-1);
        }
        cout << ",";
        sort(v2.begin(),v2.end());
        for(int j=0;j<v2.size();j++){
            cout << v2[j] << ' ';
        }
        cout << '\n';
    }
    return ;

}
