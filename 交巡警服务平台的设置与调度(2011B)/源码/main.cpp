#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <tuple>
#include <cstring>
#include <cmath>
#include <limits>
#include <ostream>
#include <fstream>
#include "point.h"
using namespace  std;

//double a[93][93];
double a[583][583];
//double mindis[93][93];
double mindis[583][583];
double mintime[583][583];
vector<int> guan[21];
pair<int,double> p[93] ; // <交巡警平台编号 ，距离>  solve()里面求解
vector<int> neng[93];
int ansp[93];
double tans[93];
vector<int> road[93][93];//从i点到j点最短路路径
int froad[93];//路径 ， 临时变量

void init();
void solve_mindis();//求各点最短路
void solve_mindis2();//比一加了求路径
void road_dfs(int ,int,int);//求路径的dfs
void solve();//问题1.1
void put_file();//问题1.1 输出文件

void put_to_matlab(); // line
void put_to_matlab(vector<int> &); // point vector
void put_to_matlab(vector<pair<double,double>> &); // pair point
void put_to_matlab_police();
void put_to_matlab_text();
void put_to_matlab_text(vector<int> &);
void put_to_matlab_point(vector<int> &);

void solve2();// 问题1.1 为各交巡警服务平台分配管辖范围 求解 交警平台到各点最大值最小
void put_file2();// solve2 的输出文件

int Alukou[13] = {12,14,16,21,22,23, 24 ,28,29,30,38,48,62};
double solve3_ans = 1e6;
double solve3_now_ans;
double solve3_k[13];
bool solve3_vis[21];
void solve3();// 问题1.2
void solve3_dfs(int);

void put_to_lingo();

string &s = lingo_question2_s2;// 处理lingo输出的字符串

vector<tuple<int,int,int>>solve_lingo_v;
void solve_lingo();// 处理lingo输出
void solve_lingo_put_file();

void solve4();// 问题2.1

vector<double> all_x;
vector<double> all_y;
vector<pair<int,int> > connect;
vector<int>police;
vector<int>solve5_ans[583];
set<double>p_alltime; // p点扩大范围的时间

vector<int>last_point;// 上次范围的点

void mindis_all();//求全市各点最短路
void solve5_infile();//处理解决问题2需要的文件
void solve5();// 完整解决问题2
void solve5_outfile();//输出解决问题2需要的方案
void solve5_outfile(string );////输出解决问题2需要的玩意
void mindis_all_put_file();
void solve5_can();//算交警平台能围堵的表格 solve5_ans[i].push_back(j);

vector<int>solve5_A_ans_vis;

void solve5_A();//A区 分析搞定
void solve5_F();//F区 搞定
void solve5_C();//C区 分析搞定
void solve5_E();//E区 搞定
void solve5_D();//D区 搞定

vector<int>solve5_neng[583];
vector<int>solve5_C_police;
int solve5_C_fangan[583];
int ending_ans[583];
int solve5_C_ans = 40;//犯罪嫌疑人全区活动范围,如果很大说明没有封到C区内
bool solve5_C_vis[583];//封点
bool solve5_C_vis_police[583];//警察局有没有用过
void solve5_C_dfs(int x);
int solve5_C_bfs();
void solve5_C_outfile();

void solve5_A_bfs();

int main(){
    solve_lingo();
    //solve5_C();
    //solve5_A();
    //solve_lingo();
    return 0;
}

void solve5_A(){
#if 1

    mindis_all();
    vector<int>police_C;
    int pc;
    while(cin >> pc) { if(pc==-1)break;police_C.push_back(pc); }

    for(auto i:police_C){
        cout << "plot(" << all_x[i] << "," << all_y[i] << ",'o','Color','red');\n";
    }


    cout << "hold on;\n";

    solve5_C_vis[3]=true;
    solve5_C_vis[4]=true;
    solve5_C_vis[5]=true;
    solve5_C_vis[6]=true;
    solve5_C_vis[10]=true;
    solve5_C_vis[16]=true;
    solve5_C_vis[29]=true;
    solve5_C_vis[40]=true;
    solve5_C_vis[41]=true;
    solve5_C_vis[55]=true;
    solve5_C_vis[60]=true;
    solve5_C_vis[168]=true;
    solve5_C_vis[232]=true;
    solve5_C_vis[240]=true;
    solve5_C_vis[244]=true;
    solve5_C_vis[248]=true;
    solve5_C_vis[246]=true;
    solve5_C_vis[370]=true;
    solve5_C_vis[371]=true;
    solve5_C_vis[561]=true;

    solve5_C_bfs();
    put_to_matlab_text(solve5_A_ans_vis);
    solve5_A_bfs();

    for(int i=1;i<=582;i++){
        if(solve5_C_vis[i]){
            cout << "plot(" << all_x[i] << "," << all_y[i] << ",'x','Color','red','MarkerSize',10,'LineWidth',2);\n";
        }
    }
    put_to_matlab(solve5_A_ans_vis);

    for(auto i:solve5_A_ans_vis){
        for(auto j:solve5_A_ans_vis){
            if(a[i][j]){
                cout << "line([" << all_x[i] << "," << all_x[j] << "],[" << all_y[i] << "," << all_y[j] << "]);\n";
            }
        }
    }

#endif

#if 0
    //结果
    solve5_infile();
    mindis_all();
    vector<int>mv;
    for(int i=1;i<=92;i++){
        mv.push_back(i);
    }
    cout << "hold on;\n";
    put_to_matlab(mv);
    put_to_matlab(); // line
    put_to_matlab_police();
    //put_to_matlab_text();
    vector<int>ev;

    ev.push_back(29);
    ev.push_back(40);
    ev.push_back(41);
    ev.push_back(55);
    ev.push_back(60);
    cout << "text(" << all_x[32] << "," << all_y[32] << ",'" << 32 << "' , 'FontSize',8 );\n";
    put_to_matlab_text(ev);

    ev.push_back(6);
    ev.push_back(5);
    ev.push_back(4);
    ev.push_back(3);
    ev.push_back(10);
    ev.push_back(16);
    //put_to_matlab_text(ev);
    put_to_matlab_point(ev);
    vector<int>police_c;
    for(auto i:police){
        if(i>=1 && i<= 20)
            police_c.push_back(i);
    }
    put_to_matlab_text(police_c);
    //cout << "title('A区封锁点示意图');\n";
    ev.push_back(239);
    ev.push_back(239);

#endif
}

void solve5_C_dfs(int x){
    if(x == 17){
        int k = solve5_C_bfs();
        if( solve5_C_ans > k){
            solve5_C_ans = k;
            for(auto i : solve5_C_police){
                ending_ans[i] = solve5_C_fangan[solve5_C_police[x]];
            }
        }

        return ;
    }
    if(solve5_C_vis_police[solve5_C_police[x]])solve5_C_dfs(x+1);
    for(auto i : solve5_neng[solve5_C_police[x]]){
        if(i>300||solve5_C_vis[i])continue;
        solve5_C_vis[i] = true;
        solve5_C_fangan[solve5_C_police[x]] = i;
        solve5_C_dfs(x+1);
        solve5_C_vis[i] = false;
    }
}
int solve5_C_bfs(){
    //237开始
    int sum = 1;
    bool vis[583] = {false};
    queue<int>q;
    //q.push(237);
    q.push(32);q.push(28);
    solve5_A_ans_vis.push_back(32);
    vis[32] = true;
    while(!q.empty()){
        int u = q.front();q.pop();
        for(int i=1;i<=582;i++){
            if(a[u][i] && !vis[i] ){
                //if(i>319 || i < 166)return 1e6; // 出C区了
                solve5_A_ans_vis.push_back(i);
                if(!solve5_C_vis[i]){
                    vis[i] = true;
                    sum++;
                    q.push(i);
                }

            }
        }
    }
    return sum;
}
void solve5_A_bfs(){
    //237开始
    int kuo = 5; // 向外扩张kuo个点
    bool vis[583] = {false};
    int vis_dis[583];memset(vis_dis,0x3f,sizeof(vis_dis));
    queue<int>q;

    for(auto i:solve5_A_ans_vis){
        vis[i] = true;
        vis_dis[i] = 0;
    }
    for(int i=1;i<=582;i++){
        if(solve5_C_vis[i]) {
            q.push(i);
        }
    }

    while(!q.empty()){
        int u = q.front();q.pop();
        for(int i=1;i<=582;i++){
            if(a[u][i] && vis_dis[i] > vis_dis[u] + 1){
                vis_dis[i] = vis_dis[u] + 1;
                if(vis_dis[i]>kuo)continue;
                if(vis[i])nullptr;
                else solve5_A_ans_vis.push_back(i);
                vis[i] = true;
                q.push(i);

            }
        }
    }
}
void solve5_C(){
#if 0
    //init
    //a[237][30]=a[237][30] = 0;
    for(int i=1;i<=92;i++){
        for(int j=166;j<=319;j++){
            if(a[i][j])
                a[i][j] = a[j][i] = 0;
        }
    }
    /*
    solve5_C_vis_police[173] = true; // 100%
    solve5_C_vis[235] = true;// 100%

    solve5_C_vis_police[167] = true;
    solve5_C_vis[248] = true;
    solve5_C_vis_police[169] = true;
    solve5_C_vis[240] = true;

    solve5_C_vis_police[180] = true;
    solve5_C_vis_police[181] = true;
    */

    //求解
    solve5_infile();
    mindis_all();
    for(auto j : police) {
        for (int i = 166; i <= 319; i++) {
            if (mintime[32][i] - 3 > mintime[j][i]) {
                solve5_neng[j].push_back(i);
            }
        }
    }



    for(auto j:police){
        if(j >=166 && j<=319){
            solve5_C_vis_police[173] = true;
            solve5_C_police.push_back(j);
        }
    }
    solve5_C_vis_police[167] = true;
    solve5_C_vis[248] = true;
    solve5_C_vis_police[169] = true;
    solve5_C_vis[240] = true;

    solve5_C_vis_police[173] = solve5_C_vis_police[171] = solve5_C_vis_police[172] = solve5_C_vis_police[168] = solve5_C_vis_police[175] = false;
    solve5_C_vis_police[171] = true;
    solve5_C_vis[246] = true;
    solve5_C_vis_police[175] = true;
    solve5_C_vis[168] = true;
    solve5_C_vis_police[168] = true;
    solve5_C_vis[190] = true;
    solve5_C_dfs(0);

    cout << "ans : " << solve5_C_ans << '\n';
    for(auto i : solve5_C_police){
        cout << "police: "<< i << " to point:" << ending_ans[i]<<'\n';
    }
    return ;
#endif
#if 1
    //分析
    //166 - 319
    solve5_infile();
    mindis_all(); // 读取点的坐标也在里面
    put_to_matlab_text();
    //point
    vector<int>mv;
    for(int i=166;i<=319;i++){
        mv.push_back(i);
    }
    put_to_matlab(mv);

    put_to_matlab(); // line
    put_to_matlab_police();

    //solve5_can();
    for(int i=166;i<=319;i++){ //can point
        if(solve5_ans[i].empty())continue;
        cout << "plot(" << all_x[i] << "," << all_y[i] << ",'.','Color','blue','MarkerSize',20);\n";
    }
#endif
#if 0
    //结果
    solve5_infile();
    mindis_all();
    vector<int>mv;
    for(int i=166;i<=319;i++){
        mv.push_back(i);
    }
    cout << "hold on;\n";
    put_to_matlab(mv);
    put_to_matlab(); // line
    put_to_matlab_police();
    //put_to_matlab_text();
    vector<int>ev;
    ev.push_back(248);
    ev.push_back(240);
    ev.push_back(246);
    ev.push_back(244);
    ev.push_back(232);
    ev.push_back(168);
    put_to_matlab_text(ev);
    put_to_matlab_point(ev);
    vector<int>police_c;
    for(auto i:police){
        if(i>=166 && i<= 319)
        police_c.push_back(i);
    }
    put_to_matlab_text(police_c);

    ev.push_back(239);
    ev.push_back(239);
#endif
}
void solve5_C_outfile(){
    std::ofstream file("anscan.xls"); // 创建ofstream对象并打开文件
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
    }
    file << "交警平台\n";
    for(auto j : police) {
        if(j >=166 && j<=319){
            file << j << '\t';
            for(auto i : solve5_neng[j]){
                file << i << '\t';
            }
            file << '\n';
        }
    }

    file.close(); // 关闭文件
}
void solve5_F(){
    solve5_infile();
    mindis_all(); // 读取点的坐标也在里面
    //put_to_matlab_text();
    solve5_can();


    for(int i=475;i<=582;i++){
        if(solve5_ans[i].empty())continue;
        cout << "plot(" << all_x[i] << "," << all_y[i] << ",'.','Color','blue','MarkerSize',20);\n";
    }


    //put_to_matlab_police();
    //put_to_matlab();
}

void solve5_E(){
    //372 - 474
    solve5_infile();
    mindis_all(); // 读取点的坐标也在里面
    put_to_matlab_text();
     //point
    vector<int>mv;
    for(int i=372;i<=474;i++){
        mv.push_back(i);
    }
    put_to_matlab(mv);

    //put_to_matlab(); // line
    //put_to_matlab_police();
    /*
    solve5_can();
    for(int i=372;i<=474;i++){ //can point
        if(solve5_ans[i].empty())continue;
        cout << "plot(" << all_x[i] << "," << all_y[i] << ",'.','Color','blue','MarkerSize',20);\n";
    }
    */
}
void solve5_D(){
    //320 - 371
    solve5_infile();
    mindis_all(); // 读取点的坐标也在里面
    put_to_matlab_text();
     //point
    vector<int>mv;
    for(int i=320;i<=371;i++){
        mv.push_back(i);
    }
    put_to_matlab(mv);

    put_to_matlab(); // line
    put_to_matlab_police();

    solve5_can();
    for(int i=320;i<=371;i++){ //can point
        if(solve5_ans[i].empty())continue;
        cout << "plot(" << all_x[i] << "," << all_y[i] << ",'.','Color','blue','MarkerSize',20);\n";
    }

}
void solve5_infile(){
    std::ifstream file("police.txt"); // 打开文件
    if(file.is_open()) { // 检查文件是否成功打开
        int po;
        while(file >> po){
            police.push_back(po);
        }
        file.close(); // 关闭文件
    }
    else {
        std::cout << "无法打开文件" << std::endl;
    }
}
void solve5_outfile(string solve5_s){
    std::ofstream file("f"+solve5_s+".xls"); // 创建ofstream对象并打开文件
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
    }
    bool vis[583] = {false};
    for(auto i:last_point){
        vis[i] = true;
    }
    for(int i=1;i<=582;i++)
        file << vis[i] << '\t';

    file.close(); // 关闭文件
}
void solve5_outfile(){
    std::ofstream file("ans.xls"); // 创建ofstream对象并打开文件
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
    }

    bool vis[583][583] = {false};

    for(int i=1;i<=582;i++){
        for(auto j : solve5_ans[i]){
            vis[i][j] = true;
        }
    }

    for(int i=1;i<=582;i++){
        for(int j=1;j<=582;j++)
            file << vis[i][j] << '\t';
        file << '\n';
    }


    file.close(); // 关闭文件
}
void solve5(){
    //1.求出P点到每个点的最短时间，bfs
    //2.求出每个交警平台到其他点的最短时间,反向bfs
    //3.列出所有交警平台能提前到的点，并且列出能提前到的交警平台编号，进行lingo求解？

    mindis_all();//求每个路最短路 + 邻接矩阵a
    cout << '*';
    //mindis_all_put_file();
    solve5_infile(); //读入交警平台数据


    cout << '*';

    //算交警平台能围堵的表格
    solve5_can();
    cout << '*';

    //算P点逃跑的时间变化（范围变化的时间）
    double max_nowtime = 0;
    for(int i=1;i<=582;i++)
        if(mintime[32][i] > 7){
            p_alltime.insert(mintime[32][i]); // 逃跑时间大于7分钟记录进去
            max_nowtime = max(mintime[32][i],max_nowtime);
        }

    double free_time[582] ={0}; // 每个点最小花费时间
    for(int i=1;i<=582;i++)free_time[i] =mintime[32][i];

    for(auto time : p_alltime){

        vector<int>&point = last_point;
        const double cha = 1e-6; // 误差值
        for(int i=1;i<=582;i++){
            if(fabs(free_time[i]-time) < cha){
                point.push_back(i);
            }
            if(free_time[i] < time){
                for(int j=1;j<=582;j++){
                    if(a[i][j] && a[i][j]*100/1000 + free_time[i] > time ){
                        point.push_back(j);
                    }
                }
            }
        }
        if(fabs(time - 11.000395) < cha)
            put_to_matlab(point);
        solve5_outfile(to_string(time));
        point.clear();
        cout << '*';
    }

    cout << '*';

}
void mindis_all(){
    all_x.push_back(0);
    all_y.push_back(0);
    //处理文件
    std::ifstream file("xpoint.txt"); // 打开文件
    if(file.is_open()) { // 检查文件是否成功打开
        double xp;
        while(file >> xp){
            all_x.push_back(xp);
        }
        file.close(); // 关闭文件
    }
    else {
        std::cout << "无法打开文件" << std::endl;
    }
    file.open("ypoint.txt"); // 打开文件
    if(file.is_open()) { // 检查文件是否成功打开
        double yp;
        while(file >> yp){
            all_y.push_back(yp);
        }
        file.close(); // 关闭文件
    }
    else {
        std::cout << "无法打开文件" << std::endl;
    }
    file.open("connet.txt"); // 打开文件
    if(file.is_open()) { // 检查文件是否成功打开
        int up,vp;
        while(file >> up >> vp){
            connect.push_back(make_pair(up,vp));
        }
        file.close(); // 关闭文件
    }
    else {
        std::cout << "无法打开文件" << std::endl;
    }


    //求解最短路
    for(auto i : connect){
        a[i.first][i.second]=a[i.second][i.first] = sqrt( (all_x[i.first]-all_x[i.second])*(all_x[i.first]-all_x[i.second]) + (all_y[i.first]-all_y[i.second])*(all_y[i.first]-all_y[i.second]) );
    }

    for(int i=1;i<=582;i++){
        for(int j=1;j<=582;j++){
            mindis[i][j]= 1e6;
        }
    }
    //求各点最短路
    for(int i=1;i<=582;i++){
        //init
        queue<int>q;
        q.push(i);
        mindis[i][i] = 0;
        while(!q.empty()){
            int j = q.front();
            q.pop();
            for(int k=1;k<=582;k++){
                if(a[k][j]){
                    if(mindis[i][j] + a[k][j] < mindis[i][k]) {
                        mindis[i][k] = mindis[i][j] + a[k][j];
                        q.push(k);
                    }
                }
            }
        }
    }

    for(int i=1;i<=582;i++){
        for(int j=1;j<=582;j++){
            mintime[i][j] = mindis[i][j]*100/1000;
        }
    }
}
void mindis_all_put_file(){
    std::ofstream file("ans.xls"); // 创建ofstream对象并打开文件
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
    }

    for(int i=1;i<=582;i++){
        for(int j=1;j<=582;j++){
            file << mindis[i][j]*100/1000 << '\t';
        }
        file << '\n';
    }


    file.close(); // 关闭文件
}
void solve4(){
    //【假设嫌疑犯一直往前跑】
    //1、设置嫌疑犯和警察的速度(相同速度)
    // 2、计算嫌疑犯从P点三分钟能到达的地点， 案发地P点的标号：32
    // 所有可能到达的地点都可能为嫌疑犯当前所在点(当前所在点可由路口i到路口i已花费的时间/距离表示,

    for(int i=0;i<=139;i++){
        a[u[i]][v[i]] = a[v[i]][u[i]] = sqrt( (x[u[i]]-x[v[i]])*(x[u[i]]-x[v[i]]) + (y[u[i]]-y[v[i]])*(y[u[i]]-y[v[i]]) );
    }

    double free_time[93] ={0}; // 每个点最小花费时间
    for(int i=1;i<=92;i++)free_time[i] = 1e6;
    for(int i=32;i<=32;i++){
        //init
        queue<int>q;
        q.push(i);
        free_time[i] = 0;
        while(!q.empty()){
            int j = q.front();
            q.pop();
            for(int k=1;k<=92;k++){
                if(a[k][j]){
                    if(free_time[j] + a[k][j]*100/1000 < free_time[k]) {
                        free_time[k] = free_time[j] + a[k][j]*100/1000;
                        q.push(k);
                    }
                }
            }
        }
    }
    vector<pair<double,double>>point; // x ,y
    const double cha = 1e-6; // 误差值
    const double time =  + 3;
    for(int i=1;i<=92;i++){
        cout << free_time[i]<<'\n';
        if(fabs(free_time[i]-time) < cha){
            point.push_back(make_pair(x[i],y[i]));
        }
        if(free_time[i] < time){
            bool flag = false;
            for(int j=0;j<12;j++){
                if(Alukou[j] == i){
                    point.push_back(make_pair(x[i],y[i]));
                    flag = true;
                    break;
                }
            }
            if(flag) continue;
            for(int j=1;j<=92;j++){
                if(a[i][j] && a[i][j]*100/1000 + free_time[i] > time ){
                    double start_to_end = time-free_time[i];
                    double end_to_start = a[i][j]*100/1000 + free_time[i] - time;
                    double new_x,new_y;
                    if(x[i] < x[j]) new_x = x[i]+(start_to_end)*(x[j]-x[i])/(start_to_end+end_to_start);
                    else new_x = x[i]-(start_to_end)*(x[i]-x[j])/(start_to_end+end_to_start);
                    if(y[i] < y[j]) new_y = y[i]+(start_to_end)*(y[j]-y[i])/(start_to_end+end_to_start);
                    else new_y = y[i]-(start_to_end)*(y[i]-y[j])/(start_to_end+end_to_start);
                    point.push_back(make_pair(new_x,new_y));
                }
            }
        }
    }
    put_to_matlab(point);
}
void put_to_matlab_text(vector<int> &mv){
    for(auto i : mv){
        cout << "text(" << all_x[i] << "," << all_y[i] << ",'" << i << "' , 'FontSize',8 );\n";
    }
}
void put_to_matlab_point(vector<int> &mv){
    for(auto i:mv){
        cout << "plot(" << all_x[i] << "," << all_y[i] << ",'x','Color','red','MarkerSize',10,'LineWidth',2);\n";
    }
}
void put_to_matlab_text(){
#if 0 //F区
    //F区
    //text(438.5,373,'82' , 'FontSize',8 );
    for(int i=475;i<=582;i++){
        if(i == 560 || i == 561 || i == 562 || i == 480)
        cout << "text(" << all_x[i] << "," << all_y[i] << ",'" << i << "' , 'FontSize',8 );\n";
    }
#endif
#if 1 //C区
    //C区
    //text(438.5,373,'82' , 'FontSize',8 );
    for(int i=166;i<=319;i++){
        cout << "text(" << all_x[i] << "," << all_y[i] << ",'" << i << "' , 'FontSize',8 );\n";
    }
#endif
#if 0 //E区
    //E区 //372 - 474
    //text(438.5,373,'82' , 'FontSize',8 );
    for(int i=372;i<=474;i++){
        cout << "text(" << all_x[i] << "," << all_y[i] << ",'" << i << "' , 'FontSize',8 );\n";
    }
#endif//372 - 474
#if 0 //D区
    //D区 //320 - 371
    //text(438.5,373,'82' , 'FontSize',8 );
    for(int i=320;i<=371;i++){
        cout << "text(" << all_x[i] << "," << all_y[i] << ",'" << i << "' , 'FontSize',8 );\n";
    }
#endif

}
void put_to_matlab_police(){
#if 1 //A区
    //A区  //166 - 319
    vector<int>police_C;
    for(auto i : police){
        if( i >=1 && i<=92)
            police_C.push_back(i);
    }

    for(auto i:police_C){
        cout << "plot(" << all_x[i] << "," << all_y[i] << ",'o','Color','red');\n";
    }
#endif
#if 0 //F区
    //F区
    vector<int>police_F;
    int x;
    for(int i=1;i<=11;i++){
        cin >> x;
        police_F.push_back(x);
    }

    police_F.push_back(16); //A区要画图的交警

    for(auto i:police_F){
        cout << "plot(" << all_x[i] << "," << all_y[i] << ",'o','Color','red');\n";
    }
#endif
#if 0 //C区
    //C区  //166 - 319
    vector<int>police_C;
    for(auto i : police){
        if( i >=166 && i<=319)
            police_C.push_back(i);
    }

    for(auto i:police_C){
        cout << "plot(" << all_x[i] << "," << all_y[i] << ",'o','Color','red');\n";
    }
#endif
#if 0 //E区
    //E区  //372 - 474
    vector<int>police_E;
    for(auto i : police){
        if( i >=372 && i<=474){
            police_E.push_back(i);
            continue;
        }
        if(i >92)continue;
        bool flag = false;
        for(int j=372;j<=474;j++){
            if(a[i][j]){
                flag = true;
                break;
            }
        }
        if(flag)
            police_E.push_back(i);
    }

    for(auto i:police_E){
        cout << "plot(" << all_x[i] << "," << all_y[i] << ",'o','Color','red');\n";
    }
#endif
#if 0 //D区
    //D区  320 - 371
    vector<int>police_E;
    for(auto i : police){
        if( i >=320 && i<=371){
            police_E.push_back(i);
            continue;
        }
        if(i >92)continue;
        bool flag = false;
        for(int j=320;j<=371;j++){
            if(a[i][j]){
                flag = true;
                break;
            }
        }
        if(flag)
            police_E.push_back(i);
    }

    for(auto i:police_E){
        cout << "plot(" << all_x[i] << "," << all_y[i] << ",'o','Color','red');\n";
    }
#endif//320 - 371

}
void put_to_matlab(vector<pair<double,double>> &mv){
    //plot(444,360,'hexagram','Color','red','MarkerSize',10)
    for(auto x:mv){
        cout << "plot(" << x.first << "," << x.second << ",'.','Color','red','MarkerSize',20);\n";
    }
}
void put_to_matlab(vector<int> &mv){
    //,'Color','red','MarkerSize',10
    for(auto i:mv){
        cout << "plot(" << all_x[i] << "," << all_y[i] << ",'.');\n";
    }
}
void put_to_matlab(){
    //问题1.1 3分钟条件下交警平台管理绘制
    //string color[] = {"","[0,0,1]","[0.23529,0.70196,0.44314]","[1,0,0]","[1,0.84314,0]","[1,0.75294,0.79608]","[0.6,0.19608,0.8]","[0,0.39216,0]","[]"};//蓝，绿，红,金(Gold),Pink,紫DarkOrchid,深绿DarkGreen
    //for(int i=21;i<=92;i++){
    //    cout << "line([" << x[i] << "," << x[p[i].first] << "],[" << y[i] << "," << y[p[i].first] << "]";
    //    cout << ");\n";
    //}
#if 1 //A区
    //A区
    for(int i=1;i<=92;i++){
        for(int j=1;j<=92;j++){
            if(a[i][j]){
                cout << "line([" << all_x[i] << "," << all_x[j] << "],[" << all_y[i] << "," << all_y[j] << "]);\n";
            }
        }
    }
#endif
#if 0 //F区
    //F区
    for(int i=475;i<=582;i++){
        for(int j=475;j<=582;j++){
            if(a[i][j]){
                cout << "line([" << all_x[i] << "," << all_x[j] << "],[" << all_y[i] << "," << all_y[j] << "]);\n";
            }
        }
    }

    //560	16
    //561	38
    cout << "line([" << all_x[16] << "," << all_x[560] << "],[" << all_y[16] << "," << all_y[560] << "]);\n";
    cout << "line([" << all_x[38] << "," << all_x[561] << "],[" << all_y[38] << "," << all_y[561] << "]);\n";
#endif

#if 0 //C区
    //C区
    for(int i=166;i<=319;i++){
        for(int j=166;j<=319;j++){
            if(a[i][j]){
                cout << "line([" << all_x[i] << "," << all_x[j] << "],[" << all_y[i] << "," << all_y[j] << "]);\n";
            }
        }
    }
    for(int i=1;i<=92;i++){
        for(int j=166;j<=319;j++){
            if(j == 190 || j == 239)continue;
            if(a[i][j]){
                cout << "line([" << all_x[i] << "," << all_x[j] << "],[" << all_y[i] << "," << all_y[j] << "],'Color','red','LineWidth',2);\n";
            }
        }
    }
#endif
#if 0 //D区
    //D区 //320 - 371
    for(int i=166;i<=319;i++){
        for(int j=166;j<=319;j++){
            if(a[i][j]){
                cout << "line([" << all_x[i] << "," << all_x[j] << "],[" << all_y[i] << "," << all_y[j] << "]);\n";
            }
        }
    }
    for(int i=1;i<=92;i++){
        for(int j=166;j<=319;j++){
            if(a[i][j]){
                cout << "line([" << all_x[i] << "," << all_x[j] << "],[" << all_y[i] << "," << all_y[j] << "],'Color','red','LineWidth',2);\n";
            }
        }
    }
#endif
#if 0 //E区
    //E区 //372 - 474
    for(int i=372;i<=474;i++){
        for(int j=372;j<=474;j++){
            if(a[i][j]){
                cout << "line([" << all_x[i] << "," << all_x[j] << "],[" << all_y[i] << "," << all_y[j] << "]);\n";
            }
        }
    }
    for(int i=1;i<=92;i++){
        for(int j=372;j<=474;j++){
            if(a[i][j]){
                cout << "line([" << all_x[i] << "," << all_x[j] << "],[" << all_y[i] << "," << all_y[j] << "],'Color','red','LineWidth',2);\n";
            }
        }
    }
#endif
#if 0 //D区 //320 - 371
    //D区 //372 - 474
    for(int i=320;i<=371;i++){
        for(int j=320;j<=371;j++){
            if(a[i][j]){
                cout << "line([" << all_x[i] << "," << all_x[j] << "],[" << all_y[i] << "," << all_y[j] << "]);\n";
            }
        }
    }
    for(int i=1;i<=92;i++){
        for(int j=320;j<=371;j++){
            if(a[i][j]){
                cout << "line([" << all_x[i] << "," << all_x[j] << "],[" << all_y[i] << "," << all_y[j] << "],'Color','red','LineWidth',2);\n";
            }
        }
    }
#endif//320 - 371
    //问题1.2封锁路线绘制
    /*
    for(auto k: solve_lingo_v){
        int start = Alukou[get<1>(k)-1];
        int end = get<0>(k);
        for(int i=1;i<road[start][end].size();i++){
            cout << "line([" << x[road[start][end][i-1]] << "," << x[road[start][end][i]] << "],[" << y[road[start][end][i-1]] << "," << y[road[start][end][i]] << "],'Color','red','LineWidth',2);\n";
        }
    }
     */
}
void put_to_lingo(){
    solve_mindis();
    //excel 版本
    std::ofstream file("lingo.xls"); // 创建ofstream对象并打开文件
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
    }

    for(int i=1;i<=20;i++){
        for(int j=0;j<13;j++){
            file << mindis[i][Alukou[j]] << '\t';
        }
        file << '\n';
    }
    file.close(); // 关闭文件
}
void solve3(){
    // 问题1.2
    //对于重大突发事件，需要调度全区20个交巡警服务平台的警力资源，
    // 对进出该区的13条交通要道实现快速全封锁。
    // 实际中一个平台的警力最多封锁一个路口，
    // 请给出该区交巡警服务平台警力合理的调度方案。

    //1-92点 坐标已知，连线已知，求邻接矩阵
    for(int i=0;i<=139;i++){
        a[u[i]][v[i]] = a[v[i]][u[i]] = sqrt( (x[u[i]]-x[v[i]])*(x[u[i]]-x[v[i]]) + (y[u[i]]-y[v[i]])*(y[u[i]]-y[v[i]]) );
    }
    //求各点最短路
    for(int i=1;i<=92;i++){
        for(int j=1;j<=92;j++){
            mindis[i][j]= 1e8;
        }
    }
    for(int i=1;i<=92;i++){
        //init
        queue<int>q;
        q.push(i);
        mindis[i][i] = 0;
        while(!q.empty()){
            int j = q.front();
            q.pop();
            for(int k=1;k<=92;k++){
                if(a[k][j]){
                    if(mindis[i][j] + a[k][j] < mindis[i][k]) {
                        mindis[i][k] = mindis[i][j] + a[k][j];
                        q.push(k);
                    }
                }
            }
        }
    }
    solve3_dfs(1); // 1-13
    cout << solve3_ans;
}
void solve3_dfs(int x){
    if(x == 14){ // 取完13个路口
        solve3_ans = min(solve3_ans,solve3_now_ans); // 取最小值
        return ;
    }
    for(int i = 1 ; i <= 20;i++){//20个警局
        if(solve3_vis[i])continue;
        solve3_vis[i] = true;

        solve3_k[x] = mindis[x][i];

        if(solve3_now_ans > solve3_k[x]){
            double f = solve3_now_ans;
            solve3_now_ans = solve3_k[x];
            if(solve3_now_ans > solve3_ans){
                solve3_now_ans = f;
                continue;
            }
        }
        solve3_dfs(x+1);

        solve3_vis[i] = false;
    }
}
void solve_mindis(){
    //1-92点 坐标已知，连线已知，求邻接矩阵
    for(int i=0;i<=139;i++){
        a[u[i]][v[i]] = a[v[i]][u[i]] = sqrt( (x[u[i]]-x[v[i]])*(x[u[i]]-x[v[i]]) + (y[u[i]]-y[v[i]])*(y[u[i]]-y[v[i]]) );
    }
    for(int i=1;i<=92;i++){
        for(int j=1;j<=92;j++){
            mindis[i][j]= 1e8;
        }
    }
    //求各点最短路
    for(int i=1;i<=92;i++){
        //init
        queue<int>q;
        q.push(i);
        mindis[i][i] = 0;
        while(!q.empty()){
            int j = q.front();
            q.pop();
            for(int k=1;k<=92;k++){
                if(a[k][j]){
                    if(mindis[i][j] + a[k][j] < mindis[i][k]) {
                        mindis[i][k] = mindis[i][j] + a[k][j];
                        q.push(k);
                    }
                }
            }
        }
    }
}
void solve2(){
    // 问题1.1
    // 请为各交巡警服务平台分配管辖范围
    // 使其在所管辖的范围内出现突发事件时，
    // 尽量能在3分钟内有交巡警（警车的时速为60km/h）到达事发地。

    solve_mindis();

    //put_file2();

    //求解 交警平台到各点最大值最小
    double ans = 0;
    for(int i=1;i<=92;i++){
        tans[i] = 1e6;
        for(int j=1;j<=20;j++){
            if(tans[i] > mindis[i][j]*100/1000){
                ansp[i] =  j;
                tans[i] = mindis[i][j]*100/1000;
            }
        }
        ans = max(ans,tans[i]);
    }
    cout << "ans:" << ans << "15->29";
    put_file2();
}
void solve(){
    //1-92点 坐标已知，连线已知，求邻接矩阵
    for(int i=0;i<=139;i++){
        a[u[i]][v[i]] = a[v[i]][u[i]] = sqrt( (x[u[i]]-x[v[i]])*(x[u[i]]-x[v[i]]) + (y[u[i]]-y[v[i]])*(y[u[i]]-y[v[i]]) );
    }

    double disa[93];
    bool vis[21];
    //求管辖点 , 按照该点最近的警察局是哪个就哪个警察局管
    for(int i=21;i<=92;i++){
        //memset(disa,0,sizeof(disa));
        for(int j=1;j<=92;j++)disa[j] = 1e6;
        memset(vis,false,sizeof(vis));

        queue<int>q;
        q.push(i);
        disa[i] = 0;
        while(!q.empty()){
            int j = q.front();
            q.pop();
            for(int k=1;k<=92;k++){
                if(a[k][j]){
                    if((!p[i].first &&  k>=1 && k <=20) || k>=1 && k <=20 && p[i].second > (a[k][j] + disa[j])){
                        p[i].first = k;
                        p[i].second = a[k][j] + disa[j];
                    }
                    if(k>=1 && k <= 20 && !vis[k] && ((a[k][j] + disa[j])*100)/1000 <= 3){
                        neng[i].push_back(k);
                        vis[k] = true;
                    }

                    if(disa[j] + a[k][j] < disa[k]) {
                        disa[k] = a[k][j] + disa[j];
                        q.push(k);
                    }
                }
            }
        }
    }

    for(int i=21;i<=92;i++){
        if(p[i].first && p[i].first < 21)
            guan[p[i].first].emplace_back(i);
    }
}
void put_file(){
    std::ofstream file("ans.xls"); // 创建ofstream对象并打开文件
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
    }
    file << "按照该点最近的警察局是哪个就哪个警察局管 来 划分管辖点\n";
    file << "全市路口节点标号\t交巡警平台编号\t距最近交巡警平台距离\t花费时间\n";
    for(int i=21;i<=92;i++){
        file << i << '\t';
        file << "A" << p[i].first << "\t";//交巡警平台编号
        file << p[i].second << "\t";//距最近交巡警平台距离
        file << p[i].second*100/1000 << "\n";//花费时间
    }

    file.close(); // 关闭文件
}
void init(){
    for(int i=21;i<=92;i++){
        p[i].second =  1e6;
    }
}
void put_file2(){
    std::ofstream file("ans.xls"); // 创建ofstream对象并打开文件
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
    }

    for(int i=1;i<=92;i++){
        for(int j=1;j<=92;j++){
            file << mindis[i][j] << '\t';
        }
        file << '\n';
    }


    file.close(); // 关闭文件
}
void solve_lingo(){ // 处理lingo
    int t=0;
    while(1){
        //1.处理空格
        while(s[t]==' ')t++;
        //2.处理字母，括号
        t++;//字母
        t++;//括号
        //3.处理间隙空格
        while(s[t]==' ')t++;

        //4.读取下标(1)
        int x = 0;
        //string sx="";
        while(s[t]>='0'&&s[t]<='9'){
            //sx.push_back(s[t]);
            x*=10;
            x+=s[t]-'0';
            t++;
        }
        //读取下标间隔符
        t++;
#if 1 // 分开写读取
        //5.读取下标(2)
        //处理间隙空格
        while(s[t]==' ')t++;

        int y = 0;
        //string sy="";
        while(s[t]>='0'&&s[t]<='9'){
            //sy.push_back(s[t]);
            y*=10;
            y+=s[t]-'0';
            t++;
        }
        //读取下标间隔符
        t++;
#endif
        //7.读取数据(整数)
        //处理间隙空格
        while(s[t]==' ')t++;

        int ans = 0;
        //string sans="";
        while(s[t]>='0'&&s[t]<='9'){
            //sans.push_back(s[t]);
            ans*=10;
            ans+=s[t]-'0';
            t++;
        }
        solve_lingo_v.push_back(make_tuple(x,y,ans));
        //处理剩余数据
        while(t<s.size()&&s[t]!='\n')t++;
        t++;

        if(t>=s.size())break;

    }
    solve_lingo_put_file();
}
void solve_lingo_put_file(){
    std::ofstream file("ans.xls"); // 创建ofstream对象并打开文件
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
    }
    solve_mindis();

    double all_f [93] = {0};
    bool fen[93] = {false};

    file << "按照该分配工作任务方差最小 来 划分管辖点\n";
    file << "全市路口节点标号\t交巡警平台编号\t距最近交巡警平台距离\t花费时间\t该点犯罪率\n";
    for(auto i : solve_lingo_v){
        if(get<0>(i) >=1 && get<0>(i)  <=20)
            file << get<1>(i) << "\tA" << get<0>(i) << "\t" << mindis[get<1>(i)][get<0>(i)] << "\t" << mindis[get<1>(i)][get<0>(i)]*100/1000 << "\t" << crime[get<1>(i)] << '\n';
        else
            file << get<1>(i) << "\t" << get<0>(i) << "\t" << mindis[get<1>(i)][get<0>(i)] << "\t" << mindis[get<1>(i)][get<0>(i)]*100/1000 << "\t" << crime[get<1>(i)] << '\n';
        all_f[get<0>(i)] += crime[get<1>(i)];
        fen[get<0>(i)] = true;
    }
    file << '\n';

    file << "分配工作任务犯罪量总和\n";
    for(int i=1;i<=20;i++){
        file << "A" << i << "\t" << all_f[i] << '\n';
    }
    for(int i=21;i<=92;i++){
        if(fen[i])
            file << i << "\t" << all_f[i] << '\n';
    }

    file.close(); // 关闭文件
}
void solve_mindis2(){
    //1-92点 坐标已知，连线已知，求邻接矩阵
    for(int i=0;i<=139;i++){
        a[u[i]][v[i]] = a[v[i]][u[i]] = sqrt( (x[u[i]]-x[v[i]])*(x[u[i]]-x[v[i]]) + (y[u[i]]-y[v[i]])*(y[u[i]]-y[v[i]]) );
    }
    for(int i=1;i<=92;i++){
        for(int j=1;j<=92;j++){
            mindis[i][j]= 1e8;
        }
    }
    //求各点最短路 以及路径
    for(int i=1;i<=92;i++){
        //init
        for(int j=1;j<=92;j++)froad[j] = 0;

        queue<int>q;
        q.push(i);
        mindis[i][i] = 0;
        while(!q.empty()){
            int j = q.front();
            q.pop();
            for(int k=1;k<=92;k++){
                if(a[k][j]){
                    if(mindis[i][j] + a[k][j] < mindis[i][k]) {
                        froad[k] = j; // 父节点
                        mindis[i][k] = mindis[i][j] + a[k][j];
                        q.push(k);
                    }
                }
            }
        }
        for(int j=1;j<=92;j++)road_dfs(i,j ,j);
    }
}
void road_dfs(int strat,int x , int end){
    if(x == strat){
        road[strat][end].push_back(x);
        return ;
    }
    road_dfs(strat,froad[x],end);
    road[strat][end].push_back(x);
}
void solve5_can(){

    for(int i=1;i<=582;i++){
        for(auto j : police)
            if(mintime[32][i]-3 > mintime[j][i]){
                solve5_ans[i].push_back(j);
            }
    }
}