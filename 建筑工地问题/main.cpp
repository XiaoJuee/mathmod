#include <iostream>
#include <cmath>
#include <queue>
using namespace  std;
double a[10] = {0, 1.25,8.75,0.5,5.75,3,7.25,5,2},b[10] = {0, 1.25,0.75,4.75,5,6.5,7.75,1,7};
double px = 5 , py = 1;
double qx = 2 , qy = 7;
double dis[10][10];
double min_dis[10]; // p
double min_dis2[10]; // q

void bfs(int begin){
    queue<int>q;
    q.push(begin);
    while(!q.empty()){
        int x = q.front();q.pop();
        for(int i=1;i<=8;i++){
            if(begin == 7){
                if(min_dis[i] > min_dis[x] + dis[x][i]){
                    min_dis[i] = min_dis[x] + dis[x][i];
                    q.push(i);
                }
            }
            else{
                if(min_dis2[i] > min_dis2[x] + dis[x][i]){
                    min_dis2[i] = min_dis2[x] + dis[x][i];
                    q.push(i);
                }
            }
        }
    }
}


int main() {
    //init dis
    for(int i=1;i<=8;i++){
        for(int j=i+1;j<=8;j++){
            dis[i][j] = dis[j][i] = sqrt((a[i]-a[j]) * (a[i]-a[j])+  (b[i]-b[j])*(b[i]-b[j])); // 初始化距离
        }
    }
    for(int i=1;i<=6;i++)min_dis[i] = min_dis2[i] = 0x3f3f3f3f; // max set
    min_dis[7] = min_dis2[8] = 0;
    bfs(7); // p
    bfs(8); // q
    for(int i=1;i<=6;i++){
        cout << min_dis[i] << ',';
        cout << min_dis2[i] << ',';
    }
    return 0;
}
