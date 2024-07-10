#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <ostream>
using namespace std;
#define opfile
int cnt[46] ={43,59,39,41,27,28,34,21,24,24,20,25,21,23,21,18,31,23,22,59,18,25,35,29,30,42,28,42,45,49,50,64,52,63,49,35,27,16,12,2,0,6,0,0,0,1}; // 3+0.5i
int x[4];
int a[46];
void init_d();
void solve();//考虑原材料的数量
void f(int,int);
void solve_struct2();//不用考虑原材料的数量
void solve_struct2_f(int,int&);

double min_size = 3,max_size =6.5,total_size =89;
int roots_Number = 20;
int f_xi = 1;

double now_total_size=0;
int now_roots_Number = 0;
int bt = 1;


#ifdef opfile
std::ofstream outFile("product3.xlsx");
#endif

int ansd[46]={0};
int ans = 0;
void f(  int k ,int u){
    if(now_total_size <= 0.5 + total_size && now_total_size >= total_size - 0.5){
        if(now_roots_Number == roots_Number || now_roots_Number == roots_Number-1){
            for(int i=22;i<=45;i++){
                if(a[i])
                    ansd[i] = min(ansd[i],cnt[i]/a[i]);
                
                //outFile << a[i] << '\t';
            }
            //outFile << '\n';
            return ;

        }
        else return ;
    }


    if(3+0.5*k < min_size)return ; // can't chose
    int ct = min(cnt[k] ,(int)((total_size -  now_total_size)/(3+0.5*k)));
    ct = min(ct,roots_Number - now_roots_Number);
    //if(now_roots_Number > roots_Number)return ;
    for(int i=0;i<=ct;i++){
        cnt[k]-=i;
        now_total_size += i*(3+0.5*k);
        now_roots_Number+=i;
        a[k]+=i;
        f(k-1,u);
        now_total_size -= i*(3+0.5*k);
        now_roots_Number-=i;
        cnt[k]+=i;
        a[k]-=i;
    }

}

void solve(){
    for(int i=0;i<46;i++)ansd[i] = 0x3f3f3f3f;
#ifdef opfile
    if (!outFile.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return ;
    }
#endif
    min_size = 14,max_size =25.5,total_size =89;
    roots_Number = 5;f_xi = 1;
    now_total_size=0;now_roots_Number = 0;
    f((max_size - 3)*2,0);
    for(int i=22;i<=45;i++)ans = max(ans,ansd[i]);
    cout <<'\n'<<ans;
}



int main() {
    //init_d();
    solve();
    //for(double i=14;i<=25.5;i+=0.5)printf("%.1f,",i);
    //return 0;
    //solve_struct2();
    return 0;
}
void init_d(){
    for(int i=1;i<=46;i++)cnt[i-1]=0;
    cnt[2-1]=5;
    cnt[4-1]=6;
    cnt[5-1]=1;
    cnt[6-1]=3;
    cnt[9-1]=23;
    cnt[10-1]=23;
    cnt[11-1]=7;
    cnt[12-1]=1;
    cnt[14-1]=4;
    cnt[15-1]=2;
    cnt[17-1]=1;
    //for(int i=0;i<46;i++)cout << cnt[i] << ',';
    cout << '\n';
}

int uu = 0;


void solve_struct2(){
    for(int i=0;i<46;i++)ansd[i] = 0x3f3f3f3f;

    //不用考虑原材料的数量
    //编程求出有多少种答案满足这个答案
    min_size = 14,max_size =25.5,total_size =89;
    roots_Number = 5;
    now_total_size=0;now_roots_Number = 0;
    int u = 0;;
    solve_struct2_f((max_size - 3)*2,u);
    for(int i=int((min_size - 3)*2);3+0.5*i<=max_size;i++){
        cout << cnt[i] << ',';
    }
    cout << '\n' << u << '\n' << uu;
    for(int i=22;i<=45;i++)ans = max(ans,ansd[i]);
    cout <<'\n'<<ans;
}

void solve_struct2_f(int k ,int &u){
    if(now_total_size <= 0.5 + total_size && now_total_size >= total_size - 0.5){
        if(now_roots_Number == roots_Number || now_roots_Number == roots_Number-1){
            u++;
            for(int i=22;i<=45;i++){
                outFile << a[i] << '\t';
            }

            outFile << '\n';
            return ;
        }
        else return ;
    }
    if(3+0.5*k < min_size)return ; // can't chose
    int ct = roots_Number - now_roots_Number;
    //if(now_roots_Number > roots_Number)return ;
    for(int i=0;i<=ct;i++){
        now_total_size += i*(3+0.5*k);
        now_roots_Number+=i;
        a[k]+=i;
        solve_struct2_f(k-1,u);
        now_total_size -= i*(3+0.5*k);
        now_roots_Number-=i;
        a[k]-=i;
    }
}