#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace  std;
vector<double>vx,vz;
void put_file();
void solve(){
    for(double x1 = -4; x1<=4 ; x1 += 0.1){
        for(double x0 = -36; x0<=36 ; x0 += 1){
            for(double z0 = -36 ; z0<= 36 ; z0 += 1){
                double y0 = (x0*x0+z0*z0)/60;
                double t = (2*x1*x0-2*x0*x0+60*y0-2*z0*z0-900) / (4*x0*x0+3600+4*z0*z0);
                double x2 = 4*x0*t + 2*x0 - x1;
                double y2 = -120*t + 2*y0 - 15;
                double z2 = 4*z0*t + 2*z0;
                double x3 = (25015-y0)/(y2-y0)*(x2-x0)+x0;
                double z3 = (25015-y0)/(y2-y0)*(z2-z0)+z0;
                vx.push_back(x3);
                vz.push_back(z3);
            }
        }
    }

}
void put_file(){
    std::ofstream file("ansx.txt"); // 创建ofstream对象并打开文件
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
    }
    std::ofstream filez("ansz.txt"); // 创建ofstream对象并打开文件
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
    }
    for (auto x : vx){
        file << x << ' ';
    }
    for (auto z : vz){
        filez << z << ' ';
    }
    file.close(); // 关闭文件
}
int main() {
    solve();
    put_file();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
