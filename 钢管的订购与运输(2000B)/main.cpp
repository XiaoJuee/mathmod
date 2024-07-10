#include <iostream>
#include <queue>
#include <algorithm>
#include <tuple>
#include <cstring>
#include <limits>
#include <vector>
#include <fstream>
using namespace  std;
const int N = 200;
const int INF = 0x3f3f3f3f;//无穷大
double a[N][N];//图的带权值的邻接矩阵
bool te[N][N];//铁路标记
int te_a[N][N];//铁路最短路费用
double ans[N][N];//运费矩阵 (每单位钢管从第i厂运输到第j点的运费)
double cost[N];//花费数组
int road[N];//路径数组
bool vis[N];//访问标记
void init_f(int u,int v,int w){a[u][v] = a[v][u] = w;}//初始化图的函数(初始化节点u到节点v的边权为w)(无向图)
void init_t(int u,int v){te[u][v] = te[v][u] = true;}//初始化铁路标记函数(记节点u到节点v的路为铁路)
void init();//初始化
void solve();
void put_file();//输出文件

int main() {
    init();//初始化
    solve();//解决问题
    put_file();//输出文件
    return 0;
}

double cost_te(double x){//铁路花费函数(传入铁路长度x,输出该长度铁路费用)
    if(x<=300)return 20;
    if(x<=350)return 23;
    if(x<=400)return 26;
    if(x<=450)return 29;
    if(x<=500)return 32;
    if(x<=600)return 37;
    if(x<=700)return 44;
    if(x<=800)return 50;
    if(x<=900)return 55;
    if(x<=1000)return 60;
    return 60 + ( int((x-1000-1)/100) + 1) *  5;
}
double cost_go(double x){//公里花费函数(传入铁路长度x,输出该长度公路费用)
    return x*0.1;
}
void bfs(int start){

    for(int i=1;i<=39;i++){
        cost[i] = numeric_limits<double>::max();//初始化为无穷大
    }
    cost[start] = 0;
    queue<int> q;
    q.push(start);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i=1;i<=39;i++){
            if(te_a[u][i] != INF  && cost[u]+cost_te(te_a[u][i]) < cost[i]){//如果是有铁路连接，并且走铁路花费小
                road[i] = u;//记录从哪一个节点来的
                cost[i] = cost[u]+cost_te(te_a[u][i]);//更新费用
                q.push(i);
            }
            if(a[u][i] > 0 && !te[u][i] && cost[u]+cost_go(a[u][i]) < cost[i]){//如果是有公路连接，并且走公路花费小
                road[i] = u;//记录从哪一个节点来的
                cost[i] = cost[u]+cost_go(a[u][i]);//更新费用
                q.push(i);
            }
        }
    }
}
vector<int>v;
void dfs(int start,int x){
    if(x == start){//走到了起始点
        v.push_back(x);
        return ;
    }
    v.push_back(x);//记录节点
    dfs(start,road[x]);//找从哪一个节点来的
}

void solve(){

    std::ofstream file("road.xls"); // 创建ofstream对象并打开文件
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
    }

    for(int i=1;i<=7;i++){
        bfs(i);

        for(int j=25;j<=39;j++){
            ans[i][j] = cost[j]; // 更新运费矩阵
        }

        for(int j=25;j<=39;j++){
            dfs(i,j);//求终点到起点的路径
            reverse(v.begin(),v.end());//将终点到起点的路径反转为起点到终点的路径
            file << i << "->" << j-24 << '\t';
            for(auto x:v){
                file << x << '\t';//输出路径到文件
            }
            file << '\n';
            v.clear();//清除路径
        }

    }
    for(int i=1;i<=7;i++){
        for(int j=25;j<=39;j++)
            cout << ans[i][j] << ' ';//输出运费矩阵
        cout << '\n';
    }
    cout << '\n';

}
void put_file(){
    std::ofstream file("cost.xls"); // 创建ofstream对象并打开文件
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
    }

    for(int i=1;i<=7;i++){
        for(int j=25;j<=39;j++)
            file << ans[i][j] << '\t';//输出文件
        file << '\n';
    }
    cout << '\n';

    file.close(); // 关闭文件
}

void init_so(){
    //初始化铁路最短路长度

    for(int i=1;i<=39;i++)
        for(int j=1;j<=39;j++)
            te_a[i][j] = INF;

    for(int i=1;i<=39;i++){
        memset(vis,false,sizeof(vis));

        queue<pair<int,int> >q;
        q.push(make_pair(i,0));
        while(!q.empty()){
            int u,k;
            tie(u,k) = q.front();
            q.pop();
            for(int j=1;j<=39;j++){
                if(j==u)continue;
                if(te[u][j]){
                    if(a[u][j] + k < te_a[i][j]) // 判断起始节点i到节点u的最短路长度加上节点u和节点j的直接边边权是否小于起始节点i到节点j的最短路长度
                        q.push(make_pair(j,a[u][j] + k));
                    te_a[i][j] = min( k + (int)a[u][j] , te_a[i][j]);//更新最短路长度
                }
            }
        }
    }
}
void init(){
    //初始化每条边以及边权
    init_f(25,26,104);
    init_f(26,8,3);
    init_f(8,9,450);
    init_f(9,10,80);
    init_f(26,27,301);
    init_f(27,28,750);
    init_f(28,29,606);
    init_f(29,30,194);
    init_f(30,31,205);
    init_f(31,32,201);
    init_f(9,11,1150);
    init_f(12,13,306);
    init_f(11,28,600);
    init_f(10,27,2);
    init_f(8,26,3);
    init_f(13,14,195);
    init_f(11,15,1100);
    init_f(1,15,202);
    init_f(1,14,20);
    init_f(1,31,31);
    init_f(31,14,10);
    init_f(13,30,5);
    init_f(12,29,10);
    init_f(32,31,201);

    /////////
    init_f(2,15,1200);
    init_f(3,16,690);
    init_f(16,33,42);
    init_f(15,16,720);
    init_f(16,17,520);
    init_f(17,34,70);
    init_f(17,18,170);
    init_f(4,18,690);
    init_f(18,19,88);
    init_f(19,5,462);
    init_f(19,35,10);
    init_f(18,20,160);
    init_f(20,21,70);
    init_f(21,36,10);
    init_f(20,22,320);
    init_f(22,37,62);
    init_f(22,23,160);
    init_f(23,6,70);
    init_f(6,38,110);
    init_f(23,38,30);
    init_f(23,24,290);
    init_f(24,39,20);
    init_f(24,7,30);
    init_f(7,39,20);
    init_f(15,32,12);


    ///
    init_f(25,26,104);
    init_f(26,27,301);
    init_f(27,28,750);
    init_f(28,29,606);
    init_f(29,30,194);
    init_f(30,31,205);
    init_f(31,32,201);
    init_f(32,33,680);
    init_f(33,34,480);
    init_f(34,35,300);
    init_f(35,36,220);
    init_f(36,37,210);
    init_f(37,38,420);
    init_f(38,39,500);

    //初始化铁路标签
    init_t(8,9);
    init_t(9,11);
    init_t(9,10);
    init_t(11,15);
    init_t(2,15);
    init_t(15,1);
    init_t(1,14);
    init_t(13,14);
    init_t(12,13);
    init_t(15,16);
    init_t(3,16);
    init_t(16,17);
    init_t(17,18);
    init_t(4,18);
    init_t(19,18);
    init_t(5,19);
    init_t(18,20);
    init_t(20,21);
    init_t(20,22);
    init_t(22,23);
    init_t(23,6);
    init_t(23,24);
    init_t(24,7);


    init_so();//初始化铁路最短路长度
}