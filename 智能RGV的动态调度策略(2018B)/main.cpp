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
#include <random>
#include <cstdlib>
#include <ctime>

#define GROUP 3 // 组数
#define early 0 // 提前响应
#define STRONG_JUDE 0 //强判
#define OPEN_HAND_PROPORTION
#undef OPEN_HAND_PROPORTION
#define PROPORTION 3 // 工序一个数
using namespace  std;

const int N = 500;

//constant
int move_t1;//RGV移动1个单位所需时间
int move_t2;//RGV移动2个单位所需时间
int move_t3;//RGV移动3个单位所需时间
int move_time[4] ;//
int complete;//CNC加工完成一个一道工序的物料所需时间
int complete2_1;//CNC加工完成一个两道工序物料的第一道工序所需时间
int complete2_2;//CNC加工完成一个两道工序物料的第二道工序所需时间
int updown_even;//RGV为CNC1#，3#，5#，7#一次上下料所需时间
int updown_odd;//RGV为CNC2#，4#，6#，8#一次上下料所需时间
int updown[2];
int clean;//RGV完成一个物料的清洗作业所需时间
//var
int rgv_pos = 1;
int cnc_pos[9] = {0,1,1,2,2,3,3,4,4};
int cnc_now[9];
int cnc_endtime[9];
int cnt;
int cnt_end;
queue<int>instruct;
vector<int>start;
struct Result{
    int i;
    int cnc;
    int start;
    int end;
    int last_end;
};
Result result[N];
int ans;
int a[9];
int ansa[9];
bool vis[9];

int main();
void init();
void solve();
void outfile();
void dfs(int ); // 跑出最优的上料组合
void reset();

struct Result2{
    int i;
    int first_cnc;
    int second_cnc;
    int first_start;
    int second_start;
    int first_end;
    int second_end;
    int last_end;
};
Result2 result2[N];
int a2[9];//第一道工序的CNC
int a2_size; //第一工序的CNC数量
bool rgv_hand;//判断rgv手上有没有第一道工序的成品
bool cnc_pp[9];//first false , second true
int rgv_cnt;//rgv 手上的工件编号是什么
void solve2();
void outfile2();
void dfs2(int);
void hand_init();
void outfile3_3();

struct Fault{
    int i;
    int cnc;
    int cnc_now;
    int start_time;
    int end_time;
};
Fault fault[N];
int fault_size;
int cnc_fault_endtime[9];
void dfs3_1(int x);
void dfs3_2(int x);
void solve3_1();
void solve3_2();
void outfile3_1();
inline pair<bool,int> lucky_Roulette();

void menu(){
    cout << "situation one  GROUP one: 11";
}
void init(int );

int main() {
    std::ofstream file("jun.xls"); // 创建ofstream对象并打开文件
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
    }
    file  << "物料数量\t系统工作效率\t故障数量\n";
    int _ = 0;
    init(1);
    dfs3_2(1);
    reset();
    for(int i=1;i<=a2_size;i++){
        a2[i] = ansa[i];
        cnc_pp[a2[i]] = false;
    }
    while(++_ <= 100){
        reset();
        solve3_2();
        file  << cnt_end << '\t' <<  ((double)cnt_end/269.158878504673) << '\t' << fault_size<<'\n';
    }
    file.close(); // 关闭文件
    return 0;



    cout << "group:";
    int group;
    cin >> group;
    init(group);
    switch(group){
        case 1:break;
        case 2:break;
        case 3:break;
        default:return 0;
    }

    cout << "situation: (1,2,31,32)";
    int situation;
    cin >> situation;
    switch (situation) {
        case 1:
            dfs(1);
            reset();
            for(int i=1;i<=8;i++){
                a[i] = ansa[i];
            }
            solve();
            outfile();
            cout << "\ncomplete mun:" << cnt_end;
            break;
        case 2:
            cout << "PROPORTION NUM:";
            cin >> a2_size;
            dfs2(1);
            reset();
            for(int i=1;i<=a2_size;i++){
                a2[i] = ansa[i];
                cnc_pp[a2[i]] = false;
            }
            solve2();
            outfile2();
            cout << "\ncomplete mun:" << cnt_end;
            break;
        case 31:
            dfs3_1(1);
            reset();
            for(int i=1;i<=8;i++){
                a[i] = ansa[i];
            }
            solve3_1();
            outfile();
            outfile3_1();
            cout << "\ncomplete mun:" << cnt_end << '\n';
            cout << "fault_num:" << fault_size;

            break;
        case 32:
            cout << "PROPORTION NUM:";
            cin >> a2_size;
            dfs3_2(1);
            reset();
            for(int i=1;i<=a2_size;i++){
                a2[i] = ansa[i];
                cnc_pp[a2[i]] = false;
            }
            solve3_2();
            outfile2();
            outfile3_1();
            cout << "\ncomplete mun:" << cnt_end << '\n';
            cout << "fault_num:" << fault_size;
            break;
        default:return 0;
    }
    //getchar();getchar();getchar();
    return 0;

    init();
    //hand_init();
    dfs3_2(1);
    reset();
    for(int i=1;i<=a2_size;i++){
        a2[i] = ansa[i];
        cnc_pp[a2[i]] = false;
    }
    //hand_init();
    solve3_2();
    outfile2();
    outfile3_1();
    cout << cnt_end << '\n';
    cout << fault_size << '\n';
    return 0;
    init();
    dfs3_1(1);
    reset();
    for(int i=1;i<=8;i++){
        a[i] = ansa[i];
    }
    solve3_1();
    outfile();
    outfile3_1();
    cout << fault_size;

    return 0;
    init();
    //hand_init();
    dfs2(1);
    reset();
    for(int i=1;i<=a2_size;i++){
        a2[i] = ansa[i];
        cnc_pp[a2[i]] = false;
    }
    //hand_init();
    solve2();
    outfile2();
    cout << cnt_end;
    return 0;
    init();
    dfs(1);
    reset();
    for(int i=1;i<=8;i++){
        a[i] = ansa[i];
    }
    solve();
    outfile();
    cout << ans;
    return 0;
}
void hand_init(){
    cnc_pp[2] = cnc_pp[4] = cnc_pp[6] = cnc_pp[3] = cnc_pp[8] = true;
    a2_size = 3;
    a2[1] = 1;
    a2[2] = 7;
    a2[3] = 5;

}
void reset(){
    rgv_pos = 1;//rvg归位
    cnt = cnt_end = 0;
    for(int i=1;i<=8;i++){
        cnc_endtime[i] = 0;
        cnc_now[i] = 0;
        cnc_fault_endtime[i] = 0;
        //cnc_pp[i] = true;
    }
    rgv_hand = false;
    rgv_cnt = 0;
    fault_size = 0;
}
void dfs(int x){
    if(x == 9){
        reset();
        solve();
        if(cnt_end > ans){
            ans = cnt_end;
            for(int i=1;i<=8;i++)
                ansa[i] = a[i];
        }
        return ;
    }
    if(x == 1){
        for(int i=1;i<=2;i++){
            if(!vis[i]){
                vis[i] = true;
                a[x] = i ;
                dfs(x+1);
                vis[i] = false;
            }
        }
    }
    else if(x == 2){
        for(int i=1;i<=4;i++){
            if(!vis[i]){
                vis[i] = true;
                a[x] = i ;
                dfs(x+1);
                vis[i] = false;
            }
        }
    }
    else{
        for(int i=1;i<=8;i++){
            if(!vis[i] ){
                if(x<=4 && cnc_pos[a[x-1]] >= cnc_pos[i])
                    continue;
                if(abs(cnc_pos[a[x-1]] - cnc_pos[i]) >= 2) // 认为规定
                    continue;
                vis[i] = true;
                a[x] = i ;
                dfs(x+1);
                vis[i] = false;
            }
        }
    }
}
void dfs2(int x){
    if(x == a2_size+1){
        reset();
        solve2();
        if(cnt_end > ans){
            ans = cnt_end;
            for(int i=1;i<=a2_size;i++){
                ansa[i] = a2[i];
            }
        }
        return ;
    }
    if(x == 1){
        for(int i=1;i<=2;i++){
            if(!vis[i]){
                vis[i] = true;
                a2[x] = i ;
                cnc_pp[a2[x]] = false;
                dfs2(x+1);
                vis[i] = false;
                cnc_pp[a2[x]] = true;
            }
        }
    }
    else if(x == 2){
        for(int i=1;i<=4;i++){
            if(!vis[i]){
                vis[i] = true;
                a2[x] = i ;
                cnc_pp[a2[x]] = false;
                dfs2(x+1);
                vis[i] = false;
                cnc_pp[a2[x]] = true;
            }
        }
    }
    else{
        for(int i=1;i<=8;i++){
            if(!vis[i]){
                if(x<=4 && cnc_pos[a2[x-1]] >= cnc_pos[i])
                    continue;
                if(abs(cnc_pos[a2[x-1]] - cnc_pos[i]) >= 2) // 人为规定
                    continue;
                vis[i] = true;
                a2[x] = i ;
                cnc_pp[a2[x]] = false;
                dfs2(x+1);
                vis[i] = false;
                cnc_pp[a2[x]] = true;
            }
        }
    }
}
void dfs3_1(int x){
    if(x == 9){
        reset();
        solve3_1();
        if(cnt_end > ans){
            ans = cnt_end;
            for(int i=1;i<=8;i++)
                ansa[i] = a[i];
        }
        return ;
    }
    if(x == 1){
        for(int i=1;i<=2;i++){
            if(!vis[i]){
                vis[i] = true;
                a[x] = i ;
                dfs3_1(x+1);
                vis[i] = false;
            }
        }
    }
    else if(x == 2){
        for(int i=1;i<=4;i++){
            if(!vis[i]){
                vis[i] = true;
                a[x] = i ;
                dfs3_1(x+1);
                vis[i] = false;
            }
        }
    }
    else{
        for(int i=1;i<=8;i++){
            if(!vis[i] ){
                if(x<=4 && cnc_pos[a[x-1]] >= cnc_pos[i])
                    continue;
                if(abs(cnc_pos[a[x-1]] - cnc_pos[i]) >= 2) // 认为规定
                    continue;
                vis[i] = true;
                a[x] = i ;
                dfs3_1(x+1);
                vis[i] = false;
            }
        }
    }
}
void dfs3_2(int x){
    if(x == a2_size+1){
        reset();
        solve3_2();
        if(cnt_end > ans){
            ans = cnt_end;
            for(int i=1;i<=a2_size;i++){
                ansa[i] = a2[i];
            }
        }
        return ;
    }
    if(x == 1){
        for(int i=1;i<=2;i++){
            if(!vis[i]){
                vis[i] = true;
                a2[x] = i ;
                cnc_pp[a2[x]] = false;
                dfs3_2(x+1);
                vis[i] = false;
                cnc_pp[a2[x]] = true;
            }
        }
    }
    else if(x == 2){
        for(int i=1;i<=4;i++){
            if(!vis[i]){
                vis[i] = true;
                a2[x] = i ;
                cnc_pp[a2[x]] = false;
                dfs3_2(x+1);
                vis[i] = false;
                cnc_pp[a2[x]] = true;
            }
        }
    }
    else{
        for(int i=1;i<=8;i++){
            if(!vis[i]){
                if(x<=4 && cnc_pos[a2[x-1]] >= cnc_pos[i])
                    continue;
                if(abs(cnc_pos[a2[x-1]] - cnc_pos[i]) >= 2) // 人为规定
                    continue;
                vis[i] = true;
                a2[x] = i ;
                cnc_pp[a2[x]] = false;
                dfs3_2(x+1);
                vis[i] = false;
                cnc_pp[a2[x]] = true;
            }
        }
    }
}
int jude(vector<int>&v,int time){
    //距离优先
    for (auto vi : v){
        if(cnc_pos[vi] == rgv_pos)
            return vi;
    }
    cout << '/';
    //预判
    bool pos[4] = {false};
    for (auto vi : v){
        pos[abs(cnc_pos[vi] - rgv_pos)]|=1;
    }
    for(int i=1;i<=3;i++)cout << pos[i] << ' ';

    if(pos[1]){
        for (auto vi : v)
            if(abs(cnc_pos[vi] - rgv_pos) == 1)
                return vi;
    }
    else if(pos[2]){

        int index2 ;
        for(auto vi:v)
            if(2==abs(cnc_pos[vi] - rgv_pos))
                index2 = vi;


        int time1 = time + move_t2;
        time1 += updown_even; // if all is even

        int index = 0;
        int timet=move_time[2]+time;
        while(cnc_fault_endtime[index] > timet)index++;
        for(int i=1;i<=8;i++){
            if(cnc_endtime[i] <= timet  && cnc_fault_endtime[i] <= time){
                index = i*(1==abs(cnc_pos[i] - rgv_pos));
            }
        }

        if(index){
            int time2 =  cnc_endtime[index] - time;
            time2 += move_t1;
            time2 += updown_even;

            time2 += move_t1;
            time2 += updown_even;

            time1 += move_time[abs(cnc_pos[index2]-cnc_pos[index])];
            time1 += updown_even;

            if(time1 < time2)//move2
                return index2;
            else
                return index;
        }
        else
            return index2;
    }
    else{ // pos[3] no

        int index3;
        for(auto vi:v)
            if(3==abs(cnc_pos[vi] - rgv_pos))
                index3 = vi;

        int time1 = time + move_t3;
        time1 += updown_even; // if all is even

        int index = 0;
        int timet=move_time[3];
        while(cnc_fault_endtime[index] > timet)index++;
        for(int i=1;i<=8;i++){
            if(cnc_endtime[i] <= timet  && cnc_fault_endtime[i] <= timet && (!index|| abs(cnc_pos[i] - rgv_pos) < abs(cnc_pos[index] - rgv_pos))){
                index = i;
            }
        }

        if(index){
            int time2 =  cnc_endtime[index] - time;
            time2 += move_time[abs(cnc_pos[index] - rgv_pos)];
            time2 += updown_even;



            time2 += move_time[abs(cnc_pos[index]-cnc_pos[index3])];
            time2 += updown_even;

            time1 += move_time[abs(cnc_pos[index]-cnc_pos[index3])];
            time1 += updown_even;

            if(time1 < time2){//move3
                return index3;
            }
            else
                return index;
        }
        else
            return index3;

    }

}
int jude2_find_second(vector<int>&v,int time){
    //距离优先
    for (auto vi : v){
        if(cnc_pos[vi] == rgv_pos)
            return vi;
    }
    cout << '/';
    //预判
    bool pos[4] = {false};
    for (auto vi : v){
        pos[abs(cnc_pos[vi] - rgv_pos)]|=1;
    }
    for(int i=1;i<=3;i++)cout << pos[i] << ' ';

    if(pos[1]){
        for (auto vi : v)
            if(abs(cnc_pos[vi] - rgv_pos) == 1)
                return vi;
    }
    else if(pos[2]){

        int index2 ;
        for(auto vi:v)
            if(2==abs(cnc_pos[vi] - rgv_pos))
                index2 = vi;


        int time1 = time + move_t2;
        time1 += updown[index2&1];

        int index = 0;
        int timet=move_time[2]+time;
        vector<int>text = {2,4,6,8,1,3,5,7};
        for(auto i : text){
            if(cnc_pp[i] && cnc_endtime[i] <= timet && cnc_fault_endtime[i] <= timet){
                index = i*(1==abs(cnc_pos[i] - rgv_pos));
            }
        }
        text.clear();

        if(index){
            int time2 =  cnc_endtime[index];
            time2 += move_t1;
            time2 += updown[index&1];

            time2 += move_time[abs(cnc_pos[index]-cnc_pos[index2])];
            time2 += updown[index2&1];

            time1 += move_time[abs(cnc_pos[index2]-cnc_pos[index])];
            time1 += updown[index&1];

            if(time1 < time2)//move2
                return index2;
            else
                return index;
        }
        else
            return index2;
    }
    else{ // pos[3] no

        int index3;
        for(auto vi:v)
            if(3==abs(cnc_pos[vi] - rgv_pos))
                index3 = vi;

        int time1 = time + move_t3;
        time1 += updown[index3&1];

        int index = 0;
        int timet=move_time[3]+time;
        vector<int>text = {2,4,6,8,1,3,5,7};
        for(auto i: text){
            if(cnc_pp[i] && cnc_endtime[i] <= timet && (!index|| abs(cnc_pos[i] - rgv_pos) < abs(cnc_pos[index] - rgv_pos) && cnc_fault_endtime[i] <= timet)){
                index = i;
            }
        }
        text.clear();

        if(index){
            int time2 =  cnc_endtime[index];
            time2 += move_time[abs(cnc_pos[index] - rgv_pos)];
            time2 += updown[index&1];

            time2 += move_time[abs(cnc_pos[index]-cnc_pos[index3])];
            time2 += updown[index3&1];

            time1 += move_time[abs(cnc_pos[index]-cnc_pos[index3])];
            time1 += updown[index&1];

            if(time1 < time2){//move3
                return index3;
            }
            else
                return index;
        }
        else
            return index3;

    }

}
int jude2_find_first(vector<int>&v,int time){
    //距离优先
    for (auto vi : v){
        if(cnc_pos[vi] == rgv_pos)
            return vi;
    }
    cout << '/';
    //预判
    bool pos[4] = {false};
    for (auto vi : v){
        pos[abs(cnc_pos[vi] - rgv_pos)]|=1;
    }
    for(int i=1;i<=3;i++)cout << pos[i] << ' ';

    if(pos[1]){
        for (auto vi : v)
            if(abs(cnc_pos[vi] - rgv_pos) == 1)
                return vi;
    }
    else if(pos[2]){

        int index2 ;
        for(auto vi:v)
            if(2==abs(cnc_pos[vi] - rgv_pos))
                index2 = vi;


        int time1 = time + move_t2;
        time1 += updown[index2&1];

        int index = 0;
        int timet=move_time[2]+time;
        vector<int>text = {2,4,6,8,1,3,5,7};
        for(auto i : text){
            if(!cnc_pp[i] && cnc_endtime[i] <= timet && cnc_fault_endtime[i] <= timet){
                index = i*(1==abs(cnc_pos[i] - rgv_pos));
            }
        }
        text.clear();

        if(index){
            int time2 =  cnc_endtime[index] - time;
            time2 += move_t1;
            time2 += updown[index&1];

            time2 += move_time[abs(cnc_pos[index]-cnc_pos[index2])];
            time2 += updown[index2&1];

            time1 += move_time[abs(cnc_pos[index2]-cnc_pos[index])];
            time1 += updown[index&1];

            if(time1 < time2)//move2
                return index2;
            else
                return index;
        }
        else
            return index2;
    }
    else{ // pos[3] no

        int index3;
        for(auto vi:v)
            if(3==abs(cnc_pos[vi] - rgv_pos))
                index3 = vi;

        int time1 = time + move_t3;
        time1 += updown[index3&1];

        int index = 0;
        int timet=move_time[3]+time;
        vector<int>text = {2,4,6,8,1,3,5,7};
        for(auto i:text){
            if(!cnc_pp[i] && cnc_endtime[i] <= timet && (!index|| abs(cnc_pos[i] - rgv_pos) < abs(cnc_pos[index] - rgv_pos)) && cnc_fault_endtime[i] <= timet){
                index = i;
            }
        }
        text.clear();

        if(index){
#if STRONG_JUDE
            if(abs(cnc_pos[index]-rgv_pos)==2){
                int timett = max(timet + move_time[abs(cnc_pos[index]-cnc_pos[index3])] ,cnc_endtime[index] + move_time[abs(cnc_pos[index]-rgv_pos)] );
                int index1 = 0;
                for(int i=1;i<=8;i++){
                    if(!cnc_pp[i] && cnc_endtime[i] <= timet && (!index1|| abs(cnc_pos[i] - rgv_pos) < abs(cnc_pos[index1] - rgv_pos)) && cnc_fault_endtime[i] <= timet){
                        index1 = i;
                    }
                }
                if(abs(cnc_pos[index1]-rgv_pos)==1){//找到一个1单位的
                    int time4 = cnc_endtime[index1];

                }
            }
#endif
            int time2 =  cnc_endtime[index] - time + time;
            time2 += move_time[abs(cnc_pos[index] - rgv_pos)];
            time2 += updown[index&1];



            time2 += move_time[abs(cnc_pos[index]-cnc_pos[index3])];
            time2 += updown[index3&1];

            time1 += move_time[abs(cnc_pos[index]-cnc_pos[index3])];
            time1 += updown[index&1];

            if(time1 < time2){//move3
                return index3;
            }
            else
                return index;
        }
        else
            return index3;

    }

}
void solve2(){
    int time = 0;
    //上1料
    for(int i=1;i<=a2_size;i++){
        time += move_time[abs(rgv_pos - cnc_pos[a2[i]])];//移动
        rgv_pos = cnc_pos[a2[i]];

        cnc_now[a2[i]] = ++cnt;
        result2[cnc_now[a2[i]]].i = cnt;
        result2[cnc_now[a2[i]]].first_cnc = a2[i];
        result2[cnc_now[a2[i]]].first_start = time;
        time += updown[a2[i]&1];
        cnc_endtime[a2[i]] = time + complete2_1;
    }
    while(time < 28800){
        if(rgv_hand){//有第一道工序的成品，需要去第二道工序

            bool flag = false;
            for(int i=1;i<=8;i++){
                if(cnc_pp[i] && cnc_endtime[i] <= time){
                    flag |= 1;
                    break;
                }
            }
            if(!flag){
                //提前移动
                int index = 1;
                while(!cnc_pp[index])index++; //找到第一个是第二工序的cnc
                for(int i=2;i<=8;i++){
                    if(cnc_pp[i] && cnc_endtime[index] > cnc_endtime[i]){
                        index = i;
                    }
                    else if(cnc_pp[i] && cnc_endtime[index] == cnc_endtime[i]){
                        if(abs(cnc_pos[index] - rgv_pos) > abs(cnc_pos[i] - rgv_pos))
                            index = i;
                    }
                }


#if early
                time += max(move_time[abs(cnc_pos[index] - rgv_pos)] , cnc_endtime[index] - time);//pass time
                rgv_pos = cnc_pos[index];
#else
                time +=  cnc_endtime[index] - time;//pass time
#endif
                continue;
            }

            vector<int>v;
            for(int i=1;i<=8;i++){
                if(cnc_pp[i] && cnc_endtime[i] <= time){
                    v.push_back(i);
                    cout << i << ' ';
                }
            }
            //jude
            cout << '*';
            int next = jude2_find_second(v,time);//rgv下一个要到的地点为next个cnc
            cout << next << '\n';

            time+=move_time[abs(cnc_pos[next] - rgv_pos)]; //增加移动的时间
            rgv_pos = cnc_pos[next];
            //不能默认有熟料


            cnc_endtime[next] = time+complete2_2+updown[next&1]; // 更新结束时间
            if(cnc_now[next]) {//如果cnc有工件
                result2[cnc_now[next]].last_end = time + clean + updown[next & 1];//记录成品
                if(result2[cnc_now[next]].last_end < 28800)
                    cnt_end ++ ; //加工完
                result2[cnc_now[next]].second_end = time; // 记录开始下料时间
                cnc_now[next] = rgv_cnt; // 更新现在cnc上的工件

                result2[cnc_now[next]].i = cnc_now[next];
                result2[cnc_now[next]].second_start = time; // 记录开始上料时间

                time+=updown[next&1];//上下料
                time+=clean;//  清洗

                result2[cnc_now[next]].second_cnc = next;

                v.clear();
                cout << time << '\n';

                rgv_hand = false; // rgv手上没有了
                continue;
            }
            else{
                cnc_now[next] = rgv_cnt; // 更新现在cnc上的工件

                result2[cnc_now[next]].i =cnc_now[next];
                result2[cnc_now[next]].second_start = time; // 记录开始上料时间
                time+=updown[next&1];//上下料
                result2[cnc_now[next]].second_cnc = next;
                v.clear();
                cout << time << '\n';

                rgv_hand = false; // rgv手上没有了
                continue;
            }
        }
        //rgv手上没有加工件

        bool flag = false;
        for(int i=1;i<=8;i++){
            if(!cnc_pp[i] && cnc_endtime[i] <= time){
                flag |= 1;
                break;
            }
        }
        if(!flag){
            //提前移动
            int index = 1;
            while(cnc_pp[index])index++; //找到第一个是第一工序的cnc
            for(int i=2;i<=8;i++){
                if(!cnc_pp[i] && cnc_endtime[index] > cnc_endtime[i]){
                    index = i;
                }
                else if(!cnc_pp[i] && cnc_endtime[index] == cnc_endtime[i]){
                    if(abs(cnc_pos[index] - rgv_pos) > abs(cnc_pos[i] - rgv_pos))
                        index = i;
                }
            }

#if early
            time += max(move_time[abs(cnc_pos[index] - rgv_pos)] , cnc_endtime[index] - time);//pass time
            rgv_pos = cnc_pos[index];
#else
            time +=  cnc_endtime[index] - time;//pass time
#endif
            continue;
        }

        vector<int>v;
        for(int i=1;i<=8;i++){
            if(!cnc_pp[i] && cnc_endtime[i] <= time){
                v.push_back(i);
                cout << i << ' ';
            }
        }
        //jude
        cout << '*';
        int next = jude2_find_first(v,time);//rgv下一个要到的地点为next个cnc
        cout << next << '\n';

        time+=move_time[abs(cnc_pos[next] - rgv_pos)]; //增加移动的时间
        rgv_pos = cnc_pos[next];


        cnc_endtime[next] = time+complete2_1+updown[next&1]; // 更新结束时间
        result2[cnc_now[next]].first_end = time; // 记录开始下料时间
        rgv_cnt = cnc_now[next];
        cnc_now[next] = ++cnt; // 更新现在cnc上的工件

        result2[cnc_now[next]].i = cnt;
        result2[cnc_now[next]].first_start = time; // 记录开始上料时间

        time+=updown[next&1];//上下料

        result2[cnc_now[next]].first_cnc = next;
        v.clear();
        cout << time << '\n';

        rgv_hand = true; // rgv手上有了
    }
}
void solve(){
    int time = 0;
    //纯上料
    //int a[9] = {0,1,3,5,7,8,6,4,2};
    for(int i=1;i<=8;i++){

        time += move_time[abs(rgv_pos - cnc_pos[a[i]])];//移动
        rgv_pos = cnc_pos[a[i]];

        cnc_now[a[i]] = ++cnt;
        result[cnt].start = time;
        time += updown[a[i]&1];
        cnc_endtime[a[i]] = time + complete;
        result[cnt].i = cnt;
        result[cnt].cnc = a[i];

    }
    while(time < 28800){
        bool flag = false;
        for(int i=1;i<=8;i++){
            if(cnc_endtime[i] <= time){
                flag |= 1;
                break;
            }
        }
        if(!flag){
            //提前移动
            int index = 1;
            for(int i=2;i<=8;i++){
                if(cnc_endtime[index] > cnc_endtime[i]){
                    index = i;
                }
                else if(cnc_endtime[index] == cnc_endtime[i]){
                    if(abs(cnc_pos[index] - rgv_pos) > abs(cnc_pos[i] - rgv_pos))
                        index = i;
                }
            }
#if early
            time += max(move_time[abs(cnc_pos[index] - rgv_pos)] , cnc_endtime[index] - time);//pass time
            rgv_pos = cnc_pos[index];
#else
            time +=  cnc_endtime[index] - time;//pass time
#endif
            continue;
        }
        vector<int>v;
        for(int i=1;i<=8;i++){
            if(cnc_endtime[i] <= time){
                v.push_back(i);
                cout << i << ' ';
            }
        }
        //jude
        cout << '*';
        int next = jude(v,time);//rgv下一个要到的地点为next个cnc
        cout << next << '\n';

        time+=move_time[abs(cnc_pos[next] - rgv_pos)]; //增加移动的时间
        rgv_pos = cnc_pos[next];
        //默认有熟料
        result[cnc_now[next]].end = time; // 记录开始下料时间
        cnc_endtime[next] = time+complete+updown[next&1];

        result[cnc_now[next]].last_end = time+clean+updown[next&1];//add
        if(result[cnc_now[next]].last_end < 28800)
            cnt_end ++ ; //加工完
        cnc_now[next] = ++cnt;
        result[cnt].i = cnt;
        result[cnt].start = time; // 记录开始上料时间

        time+=updown[next&1];//上下料
        time+=clean;//  清洗

        result[cnt].cnc = next;

        v.clear();
        cout << time << '\n';
    }
}
void solve3_1(){
    int time = 0;
    //纯上料
    //int a[9] = {0,1,3,5,7,8,6,4,2};
    for(int i=1;i<=8;i++){

        time += move_time[abs(rgv_pos - cnc_pos[a[i]])];//移动
        rgv_pos = cnc_pos[a[i]];

        cnc_now[a[i]] = ++cnt;
        result[cnt].start = time;
        time += updown[a[i]&1];
        cnc_endtime[a[i]] = time + complete;
        result[cnt].i = cnt;
        result[cnt].cnc = a[i];

        //生产故障
        pair<bool,int>p = lucky_Roulette();
        if(p.first){
            ++fault_size;
            fault[fault_size].cnc = a[i];
            int fst = (rand()%complete) + time;
            fault[fault_size].start_time = fst;
            fault[fault_size].end_time = fst+p.second;
            fault[fault_size].cnc_now = cnc_now[fault[fault_size].cnc];
            fault[fault_size].i = fault_size;

            cnc_now[a[i]] = 0;
            cnc_endtime[a[i]] = 0;
            cnc_fault_endtime[a[i]] = fst+p.second;

            result[cnt].end = -1;
            result[cnt].last_end = -1;
        }

    }
    while(time < 28800){
        bool flag = false;
        for(int i=1;i<=8;i++){
            if(cnc_endtime[i] <= time && cnc_fault_endtime[i] <= time){
                flag |= 1;
                break;
            }
        }
        if(!flag){
            //提前移动
            int index = 1;
            while(cnc_fault_endtime[index] > time)index++;//排除故障
            for(int i=2;i<=8;i++){
                if(cnc_endtime[index] > cnc_endtime[i] && cnc_fault_endtime[i] <= time){
                    index = i;
                }
                else if(cnc_endtime[index] == cnc_endtime[i] && cnc_fault_endtime[i] <= time){
                    if(abs(cnc_pos[index] - rgv_pos) > abs(cnc_pos[i] - rgv_pos))
                        index = i;
                }
            }
            time += max(move_time[abs(cnc_pos[index] - rgv_pos)] , cnc_endtime[index] - time);//pass time
            rgv_pos = cnc_pos[index];
            continue;
        }
        vector<int>v;
        for(int i=1;i<=8;i++){
            if(cnc_endtime[i] <= time  && cnc_fault_endtime[i] <= time){
                v.push_back(i);
                cout << i << ' ';
            }
        }
        //jude
        cout << '*';
        int next = jude(v,time);//rgv下一个要到的地点为next个cnc
        cout << next << '\n';

        time+=move_time[abs(cnc_pos[next] - rgv_pos)]; //增加移动的时间
        rgv_pos = cnc_pos[next];
        if(cnc_now[next])
            result[cnc_now[next]].end = time; // 记录开始下料时间
        cnc_endtime[next] = time+complete+updown[next&1];
        if(cnc_now[next]){
            result[cnc_now[next]].last_end = time+clean+updown[next&1];//add
            if(result[cnc_now[next]].last_end < 28800)
                cnt_end ++ ; //加工完
        }


        cnc_now[next] = ++cnt;
        result[cnt].i = cnt;
        result[cnt].start = time; // 记录开始上料时间

        time+=updown[next&1];//上下料
        time+=clean;//  清洗

        result[cnt].cnc = next;

        v.clear();


        pair<bool,int>p = lucky_Roulette();
        if(p.first){
            ++fault_size;
            fault[fault_size].cnc = next;
            int fst = (rand()%complete) + time;
            fault[fault_size].start_time = fst;
            fault[fault_size].end_time = fst+p.second;
            fault[fault_size].cnc_now = cnc_now[fault[fault_size].cnc];
            fault[fault_size].i = fault_size;

            cnc_now[next] = 0;
            cnc_endtime[next] = 0;
            cnc_fault_endtime[next] = fst+p.second;

            result[cnt].end = -1;
            result[cnt].last_end = -1;
        }

        cout << time << '\n';
    }
}
void solve3_2(){
    int time = 0;
    //上1料
    for(int i=1;i<=a2_size;i++){
        time += move_time[abs(rgv_pos - cnc_pos[a2[i]])];//移动
        rgv_pos = cnc_pos[a2[i]];

        cnc_now[a2[i]] = ++cnt;
        result2[cnc_now[a2[i]]].i = cnt;
        result2[cnc_now[a2[i]]].first_cnc = a2[i];
        result2[cnc_now[a2[i]]].first_start = time;
        time += updown[a2[i]&1];
        cnc_endtime[a2[i]] = time + complete2_1;

        pair<bool,int>p = lucky_Roulette();
        if(p.first){
            ++fault_size;
            fault[fault_size].cnc = a2[i];
            int fst = (rand()%complete2_1) + time;
            fault[fault_size].start_time = fst;
            fault[fault_size].end_time = fst+p.second;
            fault[fault_size].cnc_now = cnc_now[fault[fault_size].cnc];
            fault[fault_size].i = fault_size;

            result2[cnc_now[a2[i]]].first_end = -1;
            result2[cnc_now[a2[i]]].second_start = -1;
            result2[cnc_now[a2[i]]].second_end = -1;
            result2[cnc_now[a2[i]]].second_cnc = -1;
            result2[cnc_now[a2[i]]].last_end = -1;


            cnc_now[a2[i]] = 0;
            cnc_endtime[a2[i]] = 0;
            cnc_fault_endtime[a2[i]] = fst+p.second;

        }


    }
    while(time < 28800){
        if(rgv_hand){//有第一道工序的成品，需要去第二道工序

            bool flag = false;
            for(int i=1;i<=8;i++){
                if(cnc_pp[i] && cnc_endtime[i] <= time && cnc_fault_endtime[i] <= time){
                    flag |= 1;
                    break;
                }
            }
            if(!flag){
                //提前移动
                int index = 1;
                while((!cnc_pp[index]||cnc_fault_endtime[index] > time )&& index<=8)index++; //找到第一个是第二工序的cnc
                if(index == 9){//所有的都故障了
                    //找到故障时间最短的
                    index = 1;
                    while(!cnc_pp[index])index++;
                    for(int i=2;i<=8;i++){
                        if(cnc_pp[i] && cnc_fault_endtime[index] > cnc_fault_endtime[i]){
                            index = i;
                        }
                        else if(cnc_pp[i] && cnc_endtime[index] == cnc_endtime[i]){
                            if(abs(cnc_pos[index] - rgv_pos) > abs(cnc_pos[i] - rgv_pos))
                                index = i;
                        }
                    }
#if early
                    time += max(move_time[abs(cnc_pos[index] - rgv_pos)] , cnc_fault_endtime[index] - time);//pass time
                    rgv_pos = cnc_pos[index];
#else
                    time +=  cnc_fault_endtime[index] - time;//pass time
#endif
                    continue;
                }//都故障
                for(int i=2;i<=8;i++){
                    if(cnc_pp[i] && cnc_endtime[index] > cnc_endtime[i] && cnc_fault_endtime[i] <= time){
                        index = i;
                    }
                    else if(cnc_pp[i] && cnc_endtime[index] == cnc_endtime[i] && cnc_fault_endtime[i] <= time){
                        if(abs(cnc_pos[index] - rgv_pos) > abs(cnc_pos[i] - rgv_pos))
                            index = i;
                    }
                }


#if early
                time += max(move_time[abs(cnc_pos[index] - rgv_pos)] , cnc_endtime[index] - time);//pass time
                rgv_pos = cnc_pos[index];
#else
                time +=  cnc_endtime[index] - time;//pass time
#endif
                continue;
            }

            vector<int>v;
            for(int i=1;i<=8;i++){
                if(cnc_pp[i] && cnc_endtime[i] <= time && cnc_fault_endtime[i] <= time){
                    v.push_back(i);
                    cout << i << ' ';
                }
            }
            //jude
            cout << '*';
            int next = jude2_find_second(v,time);//rgv下一个要到的地点为next个cnc
            cout << next << '\n';

            time+=move_time[abs(cnc_pos[next] - rgv_pos)]; //增加移动的时间
            rgv_pos = cnc_pos[next];
            //不能默认有熟料


            cnc_endtime[next] = time+complete2_2+updown[next&1]; // 更新结束时间
            if(cnc_now[next]) {//如果cnc有工件
                result2[cnc_now[next]].last_end = time + clean + updown[next & 1];//记录成品
                if(result2[cnc_now[next]].last_end < 28800)
                    cnt_end ++ ; //加工完
                result2[cnc_now[next]].second_end = time; // 记录开始下料时间
                cnc_now[next] = rgv_cnt; // 更新现在cnc上的工件

                result2[cnc_now[next]].i = cnc_now[next];
                result2[cnc_now[next]].second_start = time; // 记录开始上料时间

                time+=updown[next&1];//上下料
                time+=clean;//  清洗

                result2[cnc_now[next]].second_cnc = next;

                v.clear();
                cout << time << '\n';

                pair<bool,int>p = lucky_Roulette();
                if(p.first){
                    ++fault_size;
                    fault[fault_size].cnc = next;
                    int fst = (rand()%complete2_2) + time - clean;//减去多加的清洗时间
                    fault[fault_size].start_time = fst;
                    fault[fault_size].end_time = fst+p.second;
                    fault[fault_size].cnc_now = cnc_now[fault[fault_size].cnc];
                    fault[fault_size].i = fault_size;

                    result2[cnc_now[next]].second_end = -1;
                    result2[cnc_now[next]].last_end = -1;


                    cnc_now[next] = 0;
                    cnc_endtime[next] = 0;
                    cnc_fault_endtime[next] = fst+p.second;

                }

                rgv_hand = false; // rgv手上没有了
                continue;
            }
            else{
                cnc_now[next] = rgv_cnt; // 更新现在cnc上的工件

                result2[cnc_now[next]].i =cnc_now[next];
                result2[cnc_now[next]].second_start = time; // 记录开始上料时间
                time+=updown[next&1];//上下料
                result2[cnc_now[next]].second_cnc = next;
                v.clear();
                cout << time << '\n';

                pair<bool,int>p = lucky_Roulette();
                if(p.first){
                    ++fault_size;
                    fault[fault_size].cnc = next;
                    int fst = (rand()%complete2_2) + time;
                    fault[fault_size].start_time = fst;
                    fault[fault_size].end_time = fst+p.second;
                    fault[fault_size].cnc_now = cnc_now[fault[fault_size].cnc];
                    fault[fault_size].i = fault_size;

                    result2[cnc_now[next]].second_end = -1;
                    result2[cnc_now[next]].last_end = -1;


                    cnc_now[next] = 0;
                    cnc_endtime[next] = 0;
                    cnc_fault_endtime[next] = fst+p.second;


                }

                rgv_hand = false; // rgv手上没有了
                continue;
            }
        }
        //rgv手上没有加工件

        bool flag = false;
        for(int i=1;i<=8;i++){
            if(!cnc_pp[i] && cnc_endtime[i] <= time && cnc_fault_endtime[i] <= time){
                flag |= 1;
                break;
            }
        }
        if(!flag){
            //提前移动
            int index = 1;
            while(index<=8 &&(cnc_pp[index] || cnc_fault_endtime[index] > time ))index++; //找到第一个是第一工序的cnc
            if(index == 9){//所有的都故障了
                //找到故障时间最短的
                index = 1;
                while(cnc_pp[index])index++;
                for(int i=2;i<=8;i++){
                    if(!cnc_pp[i] && cnc_fault_endtime[index] > cnc_fault_endtime[i]){
                        index = i;
                    }
                    else if(!cnc_pp[i] && cnc_endtime[index] == cnc_endtime[i]){
                        if(abs(cnc_pos[index] - rgv_pos) > abs(cnc_pos[i] - rgv_pos))
                            index = i;
                    }
                }
#if early
                time += max(move_time[abs(cnc_pos[index] - rgv_pos)] , cnc_fault_endtime[index] - time);//pass time
                rgv_pos = cnc_pos[index];
#else
                time +=  cnc_fault_endtime[index] - time;//pass time
#endif
                continue;
            }//都故障
            for(int i=2;i<=8;i++){
                if(!cnc_pp[i] && cnc_endtime[index] > cnc_endtime[i] && cnc_fault_endtime[i] <= time){
                    index = i;
                }
                else if(!cnc_pp[i] && cnc_endtime[index] == cnc_endtime[i]  && cnc_fault_endtime[i] <= time){
                    if(abs(cnc_pos[index] - rgv_pos) > abs(cnc_pos[i] - rgv_pos))
                        index = i;
                }
            }

#if early
            time += max(move_time[abs(cnc_pos[index] - rgv_pos)] , cnc_endtime[index] - time);//pass time
            rgv_pos = cnc_pos[index];
#else
            time +=  cnc_endtime[index] - time;//pass time
#endif
            continue;
        }

        vector<int>v;
        for(int i=1;i<=8;i++){
            if(!cnc_pp[i] && cnc_endtime[i] <= time && cnc_fault_endtime[i] <= time){
                v.push_back(i);
                cout << i << ' ';
            }
        }
        //jude
        cout << '*';
        int next = jude2_find_first(v,time);//rgv下一个要到的地点为next个cnc
        cout << next << '\n';

        time+=move_time[abs(cnc_pos[next] - rgv_pos)]; //增加移动的时间
        rgv_pos = cnc_pos[next];


        cnc_endtime[next] = time+complete2_1+updown[next&1]; // 更新结束时间
        result2[cnc_now[next]].first_end = time; // 记录开始下料时间
        rgv_cnt = cnc_now[next];
        cnc_now[next] = ++cnt; // 更新现在cnc上的工件

        result2[cnc_now[next]].i = cnt;
        result2[cnc_now[next]].first_start = time; // 记录开始上料时间

        time+=updown[next&1];//上下料

        result2[cnc_now[next]].first_cnc = next;
        v.clear();
        cout << time << '\n';

        pair<bool,int>p = lucky_Roulette();
        if(p.first){
            ++fault_size;
            fault[fault_size].cnc = next;
            int fst = (rand()%complete2_1) + time;
            fault[fault_size].start_time = fst;
            fault[fault_size].end_time = fst+p.second;
            fault[fault_size].cnc_now = cnc_now[fault[fault_size].cnc];
            fault[fault_size].i = fault_size;


            result2[cnc_now[next]].first_end = -1;
            result2[cnc_now[next]].second_start = -1;
            result2[cnc_now[next]].second_end = -1;
            result2[cnc_now[next]].second_cnc = -1;
            result2[cnc_now[next]].last_end = -1;

            cnc_now[next] = 0;
            cnc_endtime[next] = 0;
            cnc_fault_endtime[next] = fst+p.second;

        }

        rgv_hand = true; // rgv手上有了
    }
}
void outfile(){
    std::ofstream file("ans.xls"); // 创建ofstream对象并打开文件
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
    }
    file << "加工物料序号\t加工CNC编号\t上料开始时间\t下料开始时间\t清晰结束时间\n";
    for(int i=1;i<=cnt_end;i++){
        file << result[i].i << '\t';
        file << result[i].cnc << '\t' << result[i].start << '\t' << result[i].end << '\t' <<  result[i].last_end << '\n';
    }
    file.close(); // 关闭文件
}
void outfile2(){
    std::ofstream file("ans.xls"); // 创建ofstream对象并打开文件
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
    }
    file << "加工物料序号\t工序1的CNC编号\t上料开始时间\t下料开始时间\t工序2的CNC编号\t上料开始时间\t下料开始时间\t清洗结束时间\n";
    for(int i=1;i<=cnt_end;i++){
        file << result2[i].i << '\t' << result2[i].first_cnc << '\t' << result2[i].first_start << '\t'<< result2[i].first_end << '\t';
        file << result2[i].second_cnc << '\t' << result2[i].second_start << '\t' << result2[i].second_end << '\t' << result2[i].last_end << '\n';
    }
    file.close(); // 关闭文件
}
void outfile3_3(){
    std::ofstream file("jun.xls"); // 创建ofstream对象并打开文件
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
    }
    file << "故障时的物料序号\t故障CNC编号\t故障开始时间\t故障结束时间\n";
    for(int i=1;i<=fault_size;i++){
        file << fault[i].cnc_now << '\t' << fault[i].cnc << '\t' << fault[i].start_time << '\t' << fault[i].end_time << '\n';
    }
    file.close(); // 关闭文件
}
void outfile3_1(){
    std::ofstream file("ans_fault.xls"); // 创建ofstream对象并打开文件
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
    }
    file  << "物料数量\t系统工作效率\n故障数量\n";
    file  << cnt_end << '\t' <<  ((double)cnt_end/390.84) << '\t' << fault_size<<'\n';
    file.close(); // 关闭文件
}
void init(){
    //init constant 初始化常量
#if GROUP==1
    move_t1 = 20;
    move_t2 = 33;
    move_t3 = 46;
    complete = 560;
    complete2_1 = 400;
    complete2_2 = 378;
    updown_odd = 31;
    updown_even = 28;
    clean = 25;
    a2_size = 4;
#elif GROUP == 2
    move_t1 = 23;
    move_t2 = 41;
    move_t3 = 59;
    complete = 580;
    complete2_1 = 280;
    complete2_2 = 500;
    updown_odd = 35;
    updown_even = 30;
    clean = 30;
    a2_size = 4;
#elif GROUP == 3
    move_t1 = 18;
    move_t2 = 32;
    move_t3 = 46;
    complete = 545;
    complete2_1 = 455;
    complete2_2 = 182;
    updown_odd = 32;
    updown_even = 27;
    clean = 25;
    a2_size = 5;
#endif
    move_time[0]=0;
    move_time[1]=move_t1;
    move_time[2]=move_t2;
    move_time[3]=move_t3;
    updown[0] = updown_odd;
    updown[1] =updown_even;
    //init 初始化调度情况
    //得到调度指令
#ifdef OPEN_HAND_PROPORTION
    a2_size = PROPORTION;
#endif

    //init cnc_pp
    for(int i=1;i<=8;i++)cnc_pp[i] = true;
}
void init(int x){
    switch (x) {
        case 1:move_t1 = 20;
            move_t2 = 33;
            move_t3 = 46;
            complete = 560;
            complete2_1 = 400;
            complete2_2 = 378;
            updown_odd = 31;
            updown_even = 28;
            clean = 25;
            a2_size = 4;
            break;
        case 2: move_t1 = 23;
            move_t2 = 41;
            move_t3 = 59;
            complete = 580;
            complete2_1 = 280;
            complete2_2 = 500;
            updown_odd = 35;
            updown_even = 30;
            clean = 30;
            a2_size = 4;
            break;
        case 3: move_t1 = 18;
            move_t2 = 32;
            move_t3 = 46;
            complete = 545;
            complete2_1 = 455;
            complete2_2 = 182;
            updown_odd = 32;
            updown_even = 27;
            clean = 25;
            a2_size = 5;
            break;
        default:return ;
    }
    move_time[0]=0;
    move_time[1]=move_t1;
    move_time[2]=move_t2;
    move_time[3]=move_t3;
    updown[0] = updown_odd;
    updown[1] =updown_even;
    //init cnc_pp
    for(int i=1;i<=8;i++)cnc_pp[i] = true;
}


inline pair<bool,int> lucky_Roulette(){
    //srand((rand()%100)+10);
    //srand(time(nullptr));
    //mt19937 Rnd(random_device{}());

    std::random_device rd;  // 将用于为随机数引擎获得种子
    std::mt19937 gen(rd()); // 以播种标准 mersenne_twister_engine
    std::uniform_int_distribution<> dis(1, 100),dis2(600,1200);
    int x = dis(gen);
    if(x!=30)return make_pair(false,0);
    //return make_pair(false,0);
    //srand(time(nullptr));
    //int lucky_time = (rand()%600)+600;
    int lucky_time = dis2(gen);
    return make_pair(true,lucky_time);
}