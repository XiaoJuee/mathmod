#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <map>
#include "solve_lingo.h"
#define sw 0 // 原则1(on) or 原则2(off)
using namespace std;
void solve_line();
string s=" Y( 1, 2, 18)        29.00000            0.000000\n"
         "                             Y( 1, 4, 8)        44.00000            0.000000\n"
         "                             Y( 2, 1, 9)        1.000000            0.000000\n"
         "                            Y( 2, 1, 19)        1.000000            0.000000\n"
         "                             Y( 2, 2, 4)        34.00000            0.000000\n"
         "                            Y( 2, 4, 15)        30.00000            0.000000\n"
         "                             Y( 2, 5, 1)        10.00000            0.000000\n"
         "                             Y( 2, 5, 5)        19.00000            0.000000\n"
         "                            Y( 3, 1, 10)        1.000000            0.000000\n"
         "                            Y( 3, 1, 13)        18.00000            0.000000\n"
         "                            Y( 3, 2, 16)        26.00000            0.000000\n"
         "                            Y( 3, 4, 12)        35.00000            0.000000\n"
         "                             Y( 3, 5, 7)        12.00000            0.000000\n"
         "                            Y( 3, 5, 17)        3.000000            0.000000\n"
         "                             Y( 4, 2, 3)        36.00000            0.000000\n"
         "                            Y( 4, 4, 20)        30.00000            0.000000\n"
         "                             Y( 7, 2, 2)        33.00000            0.000000\n"
         "                            Y( 7, 3, 11)        4.000000            0.000000\n"
         "                            Y( 7, 3, 19)        24.00000            0.000000\n"
         "                            Y( 7, 5, 17)        35.00000            0.000000\n"
         "                            Y( 8, 1, 10)        28.00000            0.000000\n"
         "                             Y( 8, 2, 4)        2.000000            0.000000\n"
         "                             Y( 8, 3, 1)        12.00000            0.000000\n"
         "                             Y( 8, 3, 6)        25.00000            0.000000\n"
         "                            Y( 8, 4, 16)        2.000000            0.000000\n"
         "                            Y( 8, 5, 11)        27.00000            0.000000\n"
         "                            Y( 10, 1, 9)        33.00000            0.000000\n"
         "                           Y( 10, 3, 14)        45.00000            0.000000\n"
         "                            Y( 10, 5, 7)        18.00000            ";
map<int,int>ma;
map<pair<int,int>,int>mb;
double zhong;
double d[5][10] = {5.26,5.19,4.21,4,2.95,2.74,2.46,1.9,0.64,1.27,
                    1.9,0.99,1.9,1.13,1.27,2.25,1.48,2.04,3.09,3.51,
                    5.89,5.61,5.61,4.56,3.51,3.65,2.46,2.46,1.06,0.57,
                    0.64,1.76,1.27,1.83,2.74,2.6,4.21,3.72,5.05,6.1,

                    4.42,3.86,3.72,3.16,2.25,2.81,0.78,1.62,1.27,0.5,};
int main() {

    solve_line();
    return 0;
    solve_lingo();
    put_file();
    for(int i=1;i<=5;i++){
        cout << ma[i] << ' ';
    }
    cout << '\n';
    cout << zhong;
    return 0;
}

void solve_line(){
    int ma[6][11]={0};
    double x[] = {0,1.9 , 2.2 , 3.7 , 4 , 5.5 , 5.5 , 7 , 6.9 , 8.9 , 9.8};//12345678910
    double y[] = {0, 3.5 , 2.1 , 4.2 , 3.1 , 3.3 , 4.8 , 2.1 , 3.6 , 3.7 , 2.2};
    double x1[] = {0,1 , 4.2 , 8.8 , 9.8 , 11};//42513
    double y1[] = {0,5.2 , 1.1 , 1.3 , 5 , 3.5};
    int xy[] = {0,4,2,5,1,3};
    string color[] = {"0","red" , "green" , "blue" , "black" , "cyan"};
    vector<pair<int,int>>v;
    map<pair<int,int>,int>mv;
    map<pair<int,int>,int>mv2;
#if sw // 原则1
    v.push_back({1,4});mv[{1,4}]=81;
    v.push_back({2,1});mv[{2,1}]=13;
    v.push_back({2,2});mv[{2,2}]=42;
    v.push_back({2,5});mv[{2,5}]=13;
    v.push_back({3,4});mv[{3,4}]=43;
    v.push_back({3,5});mv[{3,5}]=2;
    v.push_back({4,2});mv[{4,2}]=43;
    v.push_back({8,1});mv[{8,1}]=54;
    v.push_back({9,3});mv[{9,3}]=70;
    v.push_back({10,1});mv[{10,1}]=11;
    v.push_back({10,3});mv[{10,3}]=15;
    v.push_back({10,5});mv[{10,5}]=70;
#else // 原则二
    for(int i=1;i<=5;i++){
        for(int j=1;j<=10;j++){
            cin >> ma[i][j];
            if(ma[i][j]){
                v.push_back({j,i});
                mv[{j,i}]=ma[i][j];
            }
        }
    }
    /*
    0	29	0	44	0
    2	34	0	30	29
    19	26	0	35	15
    0	36	0	30	0
    0	0	0	0	0
    0	0	0	0	0
    0	33	28	0	35
    28	2	37	2	27
    0	0	0	0	0
    33	0	45	0	18
     */
#endif

    for(auto u:v){
        cout << "line([" << x[u.first] << ',' << x1[xy[u.second]] << "],[" << y[u.first] << ',' << y1[xy[u.second]] << "]";
        cout << ",'Color','" << color[u.second] <<"'";
        cout << ",'LineWidth',1.5";
        cout << ");\n";
    }
    cout << '\n';
    for(auto u:v){
        cout << "text(" << (x[u.first]+x1[xy[u.second]])/2  << ","  << (y[u.first]+y1[xy[u.second]])/2 << ",'" <<mv[u]  << "');\n";
    }
    cout << '\n';
    for(auto u:mv){
        mv2[{u.first.second , u.first.first}] = u.second;
        cout << u.first.first << ' ' << u.first.second << ' ' << u.second << '\n';
    }
    cout << '\n';

#if sw // 原则1
    for(auto u : mv2){
        //if(k!=u.first.second)cout << ';';
        //else cout << ',';
        //cout  << u.second;
        ma[u.first.first][u.first.second] = u.second;
    }
#endif
    for(int i=1;i<=5;i++){
        for(int j=1;j<=10;j++){
            cout << ma[i][j] << ",;"[j==10];
        }
    }

}
vector<tuple<int,int,int,int>>v;
void put_file(){
    std::ofstream file("ans.xls"); // 创建ofstream对象并打开文件
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
    }
    //file << "起点" << '\t' << "终点" << '\t' << "车辆编号" << '\t' << "运输次数" << '\n';
    for(auto x:v){
        //file << get<0>(x) << '\t' << get<1>(x) << '\t' << get<2>(x) << '\t' << get<3>(x) << '\n';
        for(int i=1;i<=10;i++){
            ma[i] += (get<1>(x)==i)*154*(get<3>(x)) ;
            for(int j=1;j<=5;j++)
                mb[make_pair(i,j)] += (get<1>(x)==j)*(get<0>(x)==i)*(get<3>(x));
        }
    }

    for(int i=1;i<=10;i++){
        for(int j=1;j<=5;j++){
            file << mb[make_pair(i,j)] << '\t';
            zhong += mb[make_pair(i,j)]*d[j-1][i-1]*154;//总运量
        }

        file << '\n';
    }

    file.close(); // 关闭文件
}

void solve_lingo(){
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

        //6.读取下标(3)
        //处理间隙空格
        while(s[t]==' ')t++;

        int z = 0;
        //string sz="";
        while(s[t]>='0'&&s[t]<='9'){
            //sz.push_back(s[t]);
            z*=10;
            z+=s[t]-'0';
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
        v.push_back(make_tuple(x,y,z,ans));
        //处理剩余数据
        while(t<s.size()&&s[t]!='\n')t++;
        t++;
        if(t>=s.size())break;

    }
}