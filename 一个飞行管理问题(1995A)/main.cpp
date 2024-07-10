#include <iostream>
#include <queue>
#include <deque>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>
#include <set>

#include <cmath>
#include <sstream>
#include <valarray>
#include <bitset>
#include <cassert>
#include <tuple>
#include <ctime>

#define endn {cout<<"NO\n"; return ;};
#define endy {cout<<"YES\n"; return;}

#define int long long


using namespace std;
typedef pair<int, int> PII;
const int  inf = 0x3f3f3f3f3f3f3f3f , INF = 0x3f3f3f3f3f3f3f3f;
const int N =2e6+10;
const int mod = 1e9+7;
const double PI = acos(-1);
const double round_ = 3.6;//控制范围(-round_ ~ round)
const double round_add = 0.01;//控制精度
double mn = 60*6; // 控制已知最小答案

namespace cv{
    class Point2i{
    public:
        double x,y;
        Point2i(double x,double y){
            this->x = x;
            this->y = y;
        }
        Point2i(){
            this->x = 0;
            this->y = 0;
        }
    };
    class Point_line{
        double x1 , x2 , y1 , y2;
        Point_line(double x1,double x2,double y1,double y2){
            this->x1 = x1;
            this->x2 = x2;
            this->y1 = y1;
            this->y2 = y2;
        }
        Point_line(){
            x1 = x2 = y1 = y2 = 0;
        }
    };
}

double cos_pi[2500000];
double sin_pi[2500000];

void init();// 预处理,优化
void sole_rand();//随机处理

bool getCrossPoint(cv::Point2i *out, cv::Point2i* p1, cv::Point2i* p2, cv::Point2i* p3, cv::Point2i* p4)
{ //求两直线（线段）的交点 点斜式 解方程
    double x1 = p1->x;
    double y1 = p1->y;
    double x2 = p2->x;
    double y2 = p2->y;

    double x3 = p3->x;
    double y3 = p3->y;
    double x4 = p4->x;
    double y4 = p4->y;

    double k1, b1;
    bool k1_None = false;
    if (x2 - x1 == 0)
    {
        k1_None = true;
    }
    else
    {
        k1 = (y2 - y1) / (x2 - x1); //求出LineA斜率
        b1 = y1 - x1 * k1; // 原本斜率
    }

    double k2, b2;
    bool k2_None = false;
    if (x4 - x3 == 0)
    {
        k2_None = true;
        b2 = 0;
    }
    else
    {
        k2 = (y4 - y3) / (x4 - x3); //求出LineB斜率
        b2 = y3 - x3 * k2;
    }

    if (k1_None) // LineA 水平
    {
        if (!k2_None) // LineB 非水平线
        {
            out->x = x1;
            out->y = k2 * x1 + b2;
            //cout << "1 x=" << out.x << ", y=" << out.y;
            return true;
        }
    }
    else if (k2_None) // LineA 非水平 LineB 水平
    {
        out->x = x3;
        out->y = k1 * x3 + b1;
        //cout << "2 x=" << out.x << ", y=" << out.y;
        return true;
    }
    else if (k2 != k1) // LineA 非水平 LineB 水平
    {
        out->x = (b2 - b1) / (k1 - k2);
        out->y = k1 * out->x + b1;
       // cout << "3 x=" << out.x << ", y=" << out.y;
        return true;
    }

    out->x = 0;
    out->y = 0;
    return false;
}

inline bool getCross_twoPoint(cv::Point2i * out , cv::Point2i* p1, cv::Point2i* p2, cv::Point2i* p3, cv::Point2i* p4){//求两个直线(每条直线给两个点)的交点
    double x1 = p1->x;
    double y1 = p1->y;
    double x2 = p2->x;
    double y2 = p2->y;

    double x3 = p3->x;
    double y3 = p3->y;
    double x4 = p4->x;
    double y4 = p4->y;
    if(((x3-x4) * (y1-y2) - (x1-x2) * (y3-y4)) == 0 || ((y3-y4) * (x1-x2) - (y1-y2) * (x3-x4)) == 0) {
        out->x = out -> y = -1;
        return false;
    }
    out->x = ((x3-x4) * (x2*y1 - x1*y2) - (x1-x2) * (x4*y3 - x3*y4)) / ((x3-x4) * (y1-y2) - (x1-x2) * (y3-y4));
    out->y = ((y3-y4) * (y2*x1 - y1*x2) - (y1-y2) * (y4*x3 - y3*x4)) / ((y3-y4) * (x1-x2) - (y1-y2) * (x3-x4));
    return true;
}

inline bool getCross_xieJie(cv::Point2i * out , double k1 ,double  b1 , double k2 , double b2){//求两个直线(斜截式)的交点
    if(k1 == k2){
        out -> x = out -> y = -1;
        return false; // 平行 , 不存在交点
    }
    out->x = (b2-b1)/(k1-k2);
    out->y = k1 * out->x + b1;
    return true;
}

inline double twoPoint_dis(cv::Point2i* p1, cv::Point2i* p2){//求两点之间距离
    return sqrt( (p1->x - p2->x)*(p1->x - p2->x) + (p1->y - p2->y)*(p1->y - p2->y) );
}


double x[10]= {0,150, 85, 150, 145, 130, 0},y[10]= {0,140, 85, 155, 50, 150, 0},p0[10]= {0,243, 236, 220.5, 159, 230, 52};//已知飞机坐标和飞行角度
double nx[10] , ny[10]; // 临时变量


void solve(){
    double jude_sum = 0; // 已改变角度之和
    for(double a = -round_ ; a <= round_ ; a+=round_add){ // 枚举变化角度

        jude_sum+=fabs(a);
        if(jude_sum >= mn ) { jude_sum-=fabs(a);continue; } // 剪枝
        p0[1]+=a;
        for(double b = -round_ ; b <= round_ ; b+=round_add) {

            jude_sum+=fabs(b);
            if(jude_sum >= mn ) { jude_sum-=fabs(b);continue; }
            p0[2]+=b;
            for (double c = -round_; c <=  round_; c += round_add) {

                jude_sum+=fabs(c);
                if(jude_sum >= mn ) { jude_sum-=fabs(c);continue; }
                p0[3]+=c;
                for (double d = -round_; d <=  round_; d += round_add) {

                    jude_sum+=fabs(d);
                    if(jude_sum >= mn ) {jude_sum-=fabs(d); continue; }
                    p0[4]+=d;
                    for (double e = -round_; e <=  round_; e += round_add) {

                        jude_sum+=fabs(e);
                        if(jude_sum >= mn ) {jude_sum-=fabs(e); continue; }
                        p0[5]+=e;
                        for (double f = -round_; f <=  round_; f += round_add) {
                            jude_sum+=fabs(f);
                            if(jude_sum >= mn ) { jude_sum-=fabs(f);continue; }
                            p0[6]+=f;
#if 1 //判断碰撞模型1 轨迹交点 有点问题
                            for(int i=1;i<=6;i++){
                                nx[i] = x[i] + 200 *  cos(PI * p0[i] / 180.00); // 求t = 200 时候的飞机坐标
                                ny[i] = y[i] + 200 *  sin(PI * p0[i] / 180.00);
                            }

                            //jude 判断是否碰撞
                            bool flag = false;
                            for(int i=1;i<=6;i++){
                                for(int j=i+1;j<=6;j++){
                                    cv::Point2i *point11 = new cv::Point2i(nx[i],ny[i]);
                                    cv::Point2i *point12 = new cv::Point2i(x[i],y[i]);

                                    cv::Point2i *point21 = new cv::Point2i(nx[j],ny[j]);
                                    cv::Point2i *point22 = new cv::Point2i(x[j],y[j]);

                                    cv::Point2i *answer_point = new cv::Point2i();

#if 1 //新方案 解决擦边碰撞 , 上下平移直线4单位距离 然后分别判断 4 次 之间碰撞问题

                                    double k1 =  (y[i] - ny[i]) / (x[i] - nx[i]);
                                    double b1 = -(nx[i]*y[i] - x[i]*ny[i]) / (x[i] - nx[i]) ;

                                    double k2 =  (y[j] - ny[j]) / (x[j] - nx[j]);
                                    double b2 = -(nx[j]*y[j] - x[j]*ny[j]) / (x[j] - nx[j]) ;

                                    if(k1 == k2){ // 斜率相同
                                        if(twoPoint_dis(point12,point22) < twoPoint_dis(point11,point21)){
                                            //角度相反 && 飞行方向相反
                                            continue;
                                        }
                                        if(fabs(b1 - b2)<=8){ // 飞机之间的安全距离
                                            flag = true; // 相撞
                                            break;
                                        }
                                        continue;
                                    }

                                    double bt_[9] = {-4,4 }; // 平移距离

                                    for(int bt_i = 0; bt_i<2;bt_i++){
                                        for(int bt_j = 0; bt_j<2;bt_j++){

                                            b1 += bt_[bt_i];//平移直线
                                            b2 += bt_[bt_j];

                                            //判断交点
                                            if(getCross_xieJie(answer_point , k1,b1,k2,b2)){
                                                //算的有点问题

                                                //算时间 (用 i 飞机)
                                                double t =( answer_point->x - x[i]  - bt_[bt_i] )/cos(PI * p0[i] / 180.00) ;

                                                //负数不符合射线定义
                                                if(t<0)continue;

                                                //算该时间下另一个飞机在哪里 (算 j 飞机)
                                                double plan2_x = x[j] + t *  cos(PI * p0[j] / 180.00) + bt_[bt_j];
                                                double plan2_y = y[j] + t *  sin(PI * p0[j] / 180.00) + bt_[bt_j];

                                                double plan1_x = x[i] + t *  cos(PI * p0[j] / 180.00) + bt_[bt_i];
                                                double plan1_y = y[i] + t *  sin(PI * p0[j] / 180.00) + bt_[bt_i];

                                                //计算是否碰撞
                                                for(int k = -4 ; k <= 4 ; k++){//时刻偏差

                                                    for(int ki=1; ki <= 6; ki++){
                                                        nx[ki] = x[ki] + (double)(t + k) * cos(PI * p0[ki] / 180.00); // 求t时候的飞机坐标
                                                        ny[ki] = y[ki] + (double)(t + k) * sin(PI * p0[ki] / 180.00);
                                                    }

                                                    for(int ki=1; ki <= 6; ki++) {
                                                        for (int kj = ki + 1; kj <= 6; kj++) {
                                                            if (sqrt((nx[ki] - nx[kj]) * (nx[ki] - nx[kj]) +
                                                                     (ny[ki] - ny[kj]) * (ny[ki] - ny[kj])) <= 8) {
                                                                flag = true;
                                                                break;
                                                            }
                                                        }
                                                        if(flag)break;
                                                    }
                                                    if(flag)break;
                                                }
//                                                if(plan2_x == plan1_x && plan1_y == plan2_y){
//                                                    flag = true;
//                                                    break;
//                                                }
//                                                if(sqrt( (plan2_x - answer_point->x)*(plan2_x - answer_point->x) + (plan2_y - answer_point->y)*(plan2_y - answer_point->y) ) <= 8 ){
//                                                    flag = true;
//                                                    break;
//                                                }

                                            }


                                        }
                                        if(flag)break;
                                    }

#endif
#if 0//旧方案 如果是擦边碰撞无法判断
                                    //if(getCrossPoint(answer_point,point11,point12,point21,point22)){
                                    if(getCross_twoPoint(answer_point,point11,point12,point21,point22)){
                                        //如果有交点

                                        //算时间 (用 i 飞机)
                                        double t =( answer_point->x - x[i] )/cos(PI * p0[i] / 180.00);

                                        //负数不符合射线定义
                                        if(t<0)continue;

                                        //算该时间下另一个飞机在哪里 (算 j 飞机)
                                        double plan2_x = x[j] + t *  cos(PI * p0[j] / 180.00);
                                        double plan2_y = y[j] + t *  sin(PI * p0[j] / 180.00);

                                        //计算是否碰撞
                                        if(sqrt( (plan2_x - answer_point->x)*(plan2_x - answer_point->x) + (plan2_y - answer_point->y)*(plan2_y - answer_point->y) ) <= 8 ){
                                            flag = true;
                                            break;
                                        }
                                    }
                                    else if(answer_point->x == answer_point->y && answer_point->y == -1){//还有一个条件 平行但射线距离小于8
                                        if(twoPoint_dis(point12,point22) < twoPoint_dis(point11,point21)){
                                            //角度相反 && 飞行方向相反
                                            continue;
                                        }

                                        double A1 = ny[i] - y[i];
                                        double B1 = x[i] - nx[i];
                                        double C1 = nx[i]*y[i] - x[i]*ny[i];

                                        double A2 = ny[j] - y[j];
                                        double B2 = x[j] - nx[j];
                                        double C2 = nx[j]*y[j] - x[j]*ny[j];

                                        double d = fabs(C1-C2)/sqrt(A1*A1+B1*B1);
                                        if(d <= 8){
                                            flag = true;
                                            break;
                                        }
                                    }
#endif

                                }
                                //已经有飞机发生碰撞
                                if(flag)break;
                            }

                            if(!flag){
                                //cout << jude_sum<<'\n';
                                if(jude_sum <= 5){ // 求已知最小的答案中每个飞机转向
                                    cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << ' ' << f << '\n';
                                    for(int k = 1;k<=6;k++)
                                        cout << p0[k] << ' ';
                                    cout << '\n';
                                }
                                mn = min(mn,jude_sum);//如果没有碰撞求最小值
                            }
#endif
#if 0 //判断碰撞模型2 枚举时刻
                            bool flag = false;
                            for(int t = 0 ; t <= 200 ; t++){//枚举每一时刻,判断是否碰撞

                                for(int i=1;i<=6;i++){
                                    nx[i] = x[i] + (double)t *  cos(PI * p0[i] / 180.00); // 求t时候的飞机坐标
                                    ny[i] = y[i] + (double)t *  sin(PI * p0[i] / 180.00);
                                }

                                for(int i=1;i<=6;i++) {
                                    for (int j = i + 1; j <= 6; j++) {
                                        if (sqrt((nx[i] - nx[j]) * (nx[i] - nx[j]) +
                                                 (ny[i] - ny[j]) * (ny[i] - ny[j])) <= 8) {
                                            flag = true;
                                            break;
                                        }
                                    }
                                    if(flag)break;
                                }
                                if(flag)break;
                            }

                            if(!flag){
                                if(jude_sum == 4){ // 求已知最小的答案中每个飞机转向
                                    cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << ' ' << f << '\n';
                                    for(int k = 1;k<=6;k++)
                                        cout << p0[k] << ' ';
                                    cout << '\n';
                                }
                                mn = min(mn,jude_sum);//如果没有碰撞求最小值
                            }
#endif

                            p0[6]-=f;
                            jude_sum-=fabs(f);
                        }
                        p0[5]-=e;
                        jude_sum-=fabs(e);
                    }
                    p0[4]-=d;
                    jude_sum-=fabs(d);

                }
                p0[3]-=c;
                jude_sum-=fabs(c);

            }
            p0[2]-=b;
            jude_sum-=fabs(b);

        }
        p0[1]-=a;
        jude_sum-=fabs(a);

    }


#if 0 // 模板1
    for(double a = p0[1]-round_ ; a <= p0[1]+round_ ; a+=round_add){
        for(double b = p0[2]-round_ ; b <= p0[2]+round_ ; b+=round_add) {
            for (double c = p0[3] - round_; c <= p0[3] + round_; c += round_add) {
                for (double d = p0[4] - round_; d <= p0[4] + round_; d += round_add) {
                    for (double e = p0[5] - round_; e <= p0[5] + round_; e += round_add) {
                        for (double f = p0[6] - round_; f <= p0[6] + round_; f += round_add) {


                        }

                    }

                }

            }

        }

    }
#endif
}

void solve_more(){
    //求更高精度答案
//    0 0 3 0 0 1
//    243 236 223.5 159 230 53
//    4
//            2.56           1.07
//    243 236 223.06 159 230 53.07
//    3.63

//    243 236 223.009 159 230 53.071 ×
//    243 236 223.013 159 230 53.066 ×
//    243 236 223.02 159 230 53.058 ×
//    243 236 223.021 159 230 53.057 ×
//    243 236 223.027 159 230 53.05 ×
//    243 236 223.034 159 230 53.042 ×
//    243 236 223.035 159 230 53.041 ×
//    243 236 223.041 159 230 53.034 ×
//    243 236 223.047 159 230 53.027 ×
//    3.574 ×

//    243 236 223.046 159 230 53.074
//    243 236 223.047 159 230 53.072
//    243 236 223.048 159 230 53.069
//    243 236 223.049 159 230 53.067
//    243 236 223.05 159 230 53.065
//    243 236 223.051 159 230 53.063 ×
//    3.614

//    243 236 223.059 159 230 53.066 ✔
//    3.625 ✔

    double jude_sum = 0; // 已改变角度之和

            for (double c = -round_; c <=  round_; c += round_add) {

                jude_sum += fabs(c);
                if (jude_sum >= mn) {
                    jude_sum -= fabs(c);
                    continue;
                }
                p0[3] += c;

                for (double f = -round_; f <= round_; f += round_add) {
                    jude_sum += fabs(f);
                    if (jude_sum >= mn) {
                        jude_sum -= fabs(f);
                        continue;
                    }
                    p0[6] += f;

#if 1 //判断碰撞模型1 轨迹交点 有点问题
                    for(int i=1;i<=6;i++){
                        //nx[i] = x[i] + 200 *  cos(PI * p0[i] / 180.00); // 求t = 200 时候的飞机坐标
                        //ny[i] = y[i] + 200 *  sin(PI * p0[i] / 180.00);
                        nx[i] = x[i] + 200 *   cos_pi[(int)(p0[i]*10000)]; // 优化
                        ny[i] = y[i] + 200 *  sin_pi[(int)(p0[i]*10000)];
//                        nx[6] = x[6] + 200 *   cos_pi[(int)(p0[6]*10000)]; // 优化
//                        ny[6] = y[6] + 200 *  sin_pi[(int)(p0[6]*10000)];
                    }

                    //jude 判断是否碰撞
                    bool flag = false;
                    for(int i=1;i<=6;i++){
                        for(int j=i+1;j<=6;j++){
                            cv::Point2i *point11 = new cv::Point2i(nx[i],ny[i]);
                            cv::Point2i *point12 = new cv::Point2i(x[i],y[i]);

                            cv::Point2i *point21 = new cv::Point2i(nx[j],ny[j]);
                            cv::Point2i *point22 = new cv::Point2i(x[j],y[j]);

                            cv::Point2i *answer_point = new cv::Point2i();

#if 1 //新方案 解决擦边碰撞 , 上下平移直线4单位距离 然后分别判断 4 次 之间碰撞问题

                            double k1 =  (y[i] - ny[i]) / (x[i] - nx[i]);
                            double b1 = -(nx[i]*y[i] - x[i]*ny[i]) / (x[i] - nx[i]) ;

                            double k2 =  (y[j] - ny[j]) / (x[j] - nx[j]);
                            double b2 = -(nx[j]*y[j] - x[j]*ny[j]) / (x[j] - nx[j]) ;

                            if(k1 == k2){ // 斜率相同
                                if(twoPoint_dis(point12,point22) < twoPoint_dis(point11,point21)){
                                    //角度相反 && 飞行方向相反
                                    continue;
                                }
                                if(fabs(b1 - b2)<=8){ // 飞机之间的安全距离
                                    flag = true; // 相撞
                                    break;
                                }
                                continue;
                            }

                            double bt_[9] = {-4,4 }; // 平移距离

                            for(int bt_i = 0; bt_i<2;bt_i++){
                                for(int bt_j = 0; bt_j<2;bt_j++){

                                    b1 += bt_[bt_i];//平移直线
                                    b2 += bt_[bt_j];

                                    //判断交点
                                    if(getCross_xieJie(answer_point , k1,b1,k2,b2)){
                                        //算的有点问题

                                        //算时间 (用 i 飞机)
                                        double t =( answer_point->x - x[i]  - bt_[bt_i] )/cos(PI * p0[i] / 180.00) ;

                                        //负数不符合射线定义
                                        if(t<0)continue;


                                        //计算是否碰撞
                                        for(int k = -3 ; k <= 3 ; k++){//时刻偏差

                                            for(int ki=1; ki <= 6; ki++){
                                                //nx[ki] = x[ki] + (double)(t + k) * cos(PI * p0[ki] / 180.00); // 求t时候的飞机坐标
                                                //ny[ki] = y[ki] + (double)(t + k) * sin(PI * p0[ki] / 180.00);
                                                nx[ki] = x[ki] + (double)(t + k) * cos_pi[(int)(p0[ki]* 10000)]; // 求t时候的飞机坐标
                                                ny[ki] = y[ki] + (double)(t + k) * sin_pi[(int)(p0[ki] * 10000)];
                                            }

                                            for(int ki=1; ki <= 6; ki++) {
                                                for (int kj = ki + 1; kj <= 6; kj++) {
                                                    if (sqrt((nx[ki] - nx[kj]) * (nx[ki] - nx[kj]) +
                                                             (ny[ki] - ny[kj]) * (ny[ki] - ny[kj])) <= 8) {
                                                        flag = true;
                                                        break;
                                                    }
                                                }
                                                if(flag)break;
                                            }
                                            if(flag)break;
                                        }


                                    }


                                }
                                if(flag)break;
                            }

#endif
                        }
                        //已经有飞机发生碰撞
                        if(flag)break;
                    }

                    if(!flag){
                        //cout << jude_sum<<'\n';
                        //if(jude_sum <= 4){ // 求已知最小的答案中每个飞机转向
                            //cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << ' ' << f << '\n';
                            for(int k = 1;k<=6;k++)
                                cout << p0[k] << ' ';
                            cout << '\n';
                        //}
                        mn = min(mn,jude_sum);//如果没有碰撞求最小值
                    }
#endif
#if 0 //判断碰撞模型2 枚举时刻
                    bool flag = false;
                    for(int t = 0 ; t <= 200 ; t++){//枚举每一时刻,判断是否碰撞

                        for(int i=1;i<=6;i++){
                            nx[i] = x[i] + (double)t *  cos(PI * p0[i] / 180.00); // 求t时候的飞机坐标
                            ny[i] = y[i] + (double)t *  sin(PI * p0[i] / 180.00);
                        }

                        for(int i=1;i<=6;i++) {
                            for (int j = i + 1; j <= 6; j++) {
                                if (sqrt((nx[i] - nx[j]) * (nx[i] - nx[j]) +
                                         (ny[i] - ny[j]) * (ny[i] - ny[j])) <= 8) {
                                    flag = true;
                                    break;
                                }
                            }
                            if(flag)break;
                        }
                        if(flag)break;
                    }

                    if(!flag){
                        //if(jude_sum == 3.63){ // 求已知最小的答案中每个飞机转向
                            cout <<  c << ' ' << f << '\n';
                            for(int k = 1;k<=6;k++)
                                cout << p0[k] << ' ';
                            cout << '\n';
                        //}
                        mn = min(mn,jude_sum);//如果没有碰撞求最小值
                    }
#endif

                    p0[6] -= f;
                    jude_sum -= fabs(f);
                }

                p0[3] -= c;
                jude_sum -= fabs(c);
            }

}
void sole_rand(){
    //best 3.68
    srand(time(nullptr));
    //0-3.625 0.001
    double jude_sum = 0; // 已改变角度之和
    for(int _ = 0;_<1000000000;_++){
        srand(time(nullptr));
        // for(double a = -round_ ; a <= round_ ; a+=round_add)
        { // 随机变化角度
            double a = (rand()%3625)*0.001 * ((rand()%2 ? 1: -1) );
            a = 0;//不改
            jude_sum+=fabs(a);
            if(jude_sum >= mn ) { jude_sum-=fabs(a);continue; } // 剪枝
            p0[1]+=a;
            //for(double b = -round_ ; b <= round_ ; b+=round_add)
            {
                double b = (rand()%3625)*0.001 * ((rand()%2 ? 1: -1) );
                b = 0;//不改
                jude_sum+=fabs(b);
                if(jude_sum >= mn ) { jude_sum-=fabs(b);continue; }
                p0[2]+=b;
                //for (double c = -round_; c <=  round_; c += round_add)
                {
                    double c = (rand()%3625)*0.001 * ((rand()%2 ? 1: -1) );
                    jude_sum+=fabs(c);
                    if(jude_sum >= mn ) { jude_sum-=fabs(c);continue; }
                    p0[3]+=c;
                    //for (double d = -round_; d <=  round_; d += round_add)
                    {
                        double d = (rand()%3625)*0.001 * ((rand()%2 ? 1: -1) );
                        d = 0;//不改
                        jude_sum+=fabs(d);
                        if(jude_sum >= mn ) {jude_sum-=fabs(d); continue; }
                        p0[4]+=d;
                        //for (double e = -round_; e <=  round_; e += round_add)
                        {
                            double e = (rand()%3625)*0.001 * ((rand()%2 ? 1: -1) );
                            e = 0;//不改
                            jude_sum+=fabs(e);
                            if(jude_sum >= mn ) {jude_sum-=fabs(e); continue; }
                            p0[5]+=e;
                            //for (double f = -round_; f <=  round_; f += round_add)
                            {
                                double f = (rand()%3625)*0.001 * ((rand()%2 ? 1: -1) );
                                jude_sum+=fabs(f);
                                if(jude_sum >= mn ) { jude_sum-=fabs(f);continue; }
                                p0[6]+=f;

#if 1 //判断碰撞模型2 枚举时刻
                                bool flag = false;
                            for(int t = 0 ; t <= 200 ; t++){//枚举每一时刻,判断是否碰撞

                                for(int i=1;i<=6;i++){
                                    nx[i] = x[i] + (double)t *  cos(PI * p0[i] / 180.00); // 求t时候的飞机坐标
                                    ny[i] = y[i] + (double)t *  sin(PI * p0[i] / 180.00);
                                }

                                for(int i=1;i<=6;i++) {
                                    for (int j = i + 1; j <= 6; j++) {
                                        if (sqrt((nx[i] - nx[j]) * (nx[i] - nx[j]) +
                                                 (ny[i] - ny[j]) * (ny[i] - ny[j])) <= 8) {
                                            flag = true;
                                            break;
                                        }
                                    }
                                    if(flag)break;
                                }
                                if(flag)break;
                            }

                            if(!flag){
                                if(jude_sum == mn){ // 求已知最小的答案中每个飞机转向
                                    cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << ' ' << f << '\n';
                                    for(int k = 1;k<=6;k++)
                                        cout << p0[k] << ' ';
                                    cout << '\n';
                                }
                                mn = min(mn,jude_sum);//如果没有碰撞求最小值
                                cout << mn << '\n';
                            }
#endif
                                p0[6]-=f;
                                jude_sum-=fabs(f);
                            }
                            p0[5]-=e;
                            jude_sum-=fabs(e);
                        }
                        p0[4]-=d;
                        jude_sum-=fabs(d);

                    }
                    p0[3]-=c;
                    jude_sum-=fabs(c);

                }
                p0[2]-=b;
                jude_sum-=fabs(b);

            }
            p0[1]-=a;
            jude_sum-=fabs(a);
        }
    }


}
void init(){
    for(int i=0;i<2500000;i++){
        cos_pi[i] = cos(PI * ((double)i*0.0001) / 180.00);
    }
    for(int i=0;i<2500000;i++){
        sin_pi[i] = sin(PI * ((double)i*0.0001) / 180.00);
    }
    // i * 10000
    //eg : 530340 -> 53.034



}

signed main() {

    init(); // 预处理,优化

    //solve();
    //sole_rand();
    solve_more();
    cout << '\n' << mn;
    return 0;


}


#if 0 //递归解法 ， 待确认
bool jude(double * x , double * y , double * angle ){
    bool flag = false;
    double xx[10] , yy[10];
    for(int t=0;t<200;t++){
        for(int i=1;i<=6;i++){
            xx[i] = x[i] + t * cos(PI * angle[i] / 180.00);
            yy[i] = y[i] + t * sin(PI * angle[i] / 180.00);
        }
        for(int i=1;i<=6;i++){
            for(int j=i+1;j<=6;j++){
                if(sqrt( (xx[i]-xx[j])*(xx[i]-xx[j]) + (yy[i]-yy[j])*(yy[i]-yy[j]) ) <= 8){
                    flag = true;
                    return flag;
                }
            }
        }
    }
    return flag;
}

//int n;
double anst = 0;
double ans_angle = 8.4334;
void changeangle(double * x , double * y , double * angle , int k){
    if(k == 3){
        if(!jude(x,y,angle)){
            ans_angle = min(ans_angle,anst);cout << anst << '\n';
        }
        return ;
    }
    for(double c = -8.4334 ; c<=8.4334 ; c+=0.0001){
        anst += fabs(c);
        angle[k] += c;

        if(ans_angle == 8.4334 || ans_angle > anst){
            changeangle(x,y,angle,k+1);
        }
        angle[k] -= c;
        anst -= fabs(c);
    }
}

double x[10] = {0,150,85,150,145,130,0} ,  y[10] = {0,140,85,155,50,150,0} , angle[10] = {0，243,236,220.5,159,230,52};
#endif

