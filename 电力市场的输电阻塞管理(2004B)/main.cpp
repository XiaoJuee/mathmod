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
#include <algorithm>

using namespace  std;

const double sum_capacity = 1052.8;
const int max_price = 405; // 人为规定最大段价
int max_index ; // 最大段价对应的 i

int Segment_capacity[9][11]; //  各机组的段容量
int pre_capacity[9][11]; // 前缀和算出来各段的总容量
int price[9][11]; // 各机组的段价
double ramp_rate[9];
double start[9];

double accuracy = 0.1; // 精度
double min_price = 500;
double now_price;

map<double , double >ma[9] ; // 8个机组的容量到段价

double now_capacity;
double now[9];
double ans[9];

vector<int>all_price;

void init();
void solve3(); // 问题3
void infile();
void outfile();


int main() {
    solve3();
    return 0;
}

void solve3(){
    init();
    for(int i=max_index ;i >= 0 ; i--){
        double sum = 0;

        for(int j=1;j<=8;j++){
            int index_k = 1;
            while(start[j]-ramp_rate[j] > pre_capacity[j][index_k])index_k++;
            for(int k=index_k;k<=10;k++){
                if(price[j][k] > all_price[i] ){ // found max
                    index_k = k-1;
                    break;
                }
            }
            sum += min((double)pre_capacity[j][index_k],start[j]+ramp_rate[j]);

            now[j] = index_k;
        }

        if(sum >= sum_capacity){
            min_price = all_price[i];
            for(int j = 1;j<=8;j++)
                ans[j] = now[j];
        }
        else
            break; // no answer
    }
    cout << min_price << '\n';
    for(int j=1;j<=8;j++){
        cout << ans[j] << ' ';
    }
}
void init(){
    //input file
    infile();



    //step 1. 前缀和
    for(int i=1;i<=8;i++){
        int sum = 0;
        for(int j=1;j<=10;j++){
            sum += Segment_capacity[i][j];
            pre_capacity[i][j] = sum;
        }
    }
    //outfile();

    //15min
    for(int i=1;i<=8;i++){
        ramp_rate[i] *= 15.0;
    }


    for(int i=1;i<=8;i++){
        for(int j=1;j<=10;j++)
            all_price.push_back(price[i][j]);
    }

    sort(all_price.begin(),all_price.end());

    for(int i=0;i<all_price.size();i++){
        if(all_price[i] == max_price){
            max_index = i;
            break;
        }
    }


}
void infile(){
    std::ifstream file("Segment capacity.txt"); // 打开文件
    if(file.is_open()) { // 检查文件是否成功打开
        for(int i=1;i<=8;i++){
            for(int j=1;j<=10;j++)
                file >> Segment_capacity[i][j];
        }
        file.close(); // 关闭文件
    }
    else {
        std::cout << "无法打开文件" << std::endl;
    }

    file.open("start.txt");
    if(file.is_open()) { // 检查文件是否成功打开
        for(int i=1;i<=8;i++){
            file >> start[i];
        }
        file.close(); // 关闭文件
    }
    else {
        std::cout << "无法打开文件" << std::endl;
    }

    file.open("Segment price.txt");
    if(file.is_open()) { // 检查文件是否成功打开
        for(int i=1;i<=8;i++){
            for(int j=1;j<=10;j++)
                file >> price[i][j];
        }
        file.close(); // 关闭文件
    }
    else {
        std::cout << "无法打开文件" << std::endl;
    }

    file.open("ramp rate.txt");
    if(file.is_open()) { // 检查文件是否成功打开
        for(int i=1;i<=8;i++){
            file >> ramp_rate[i];
        }
        file.close(); // 关闭文件
    }
    else {
        std::cout << "无法打开文件" << std::endl;
    }
}
void outfile(){
    std::ofstream file("ans.xls"); // 创建ofstream对象并打开文件
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
    }
    for(int i=1;i<=8;i++){
        int sum = 0;
        for(int j=1;j<=10;j++){
            sum += Segment_capacity[i][j];
            pre_capacity[i][j] = sum;
            file << pre_capacity[i][j] << '\t';
        }
        file << '\n';
    }
    file.close(); // 关闭文件
}
