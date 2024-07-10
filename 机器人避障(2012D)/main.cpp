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

#define endn {cout<<"NO\n"; return ;};
#define endy {cout<<"YES\n"; return;}

#define int long long

using namespace std;
typedef pair<int, int> PII;
const int  inf = 0x3f3f3f3f3f3f3f3f , INF = 0x3f3f3f3f3f3f3f3f;
const int N =2e6+10;
const int mod = 1e9+7;



int n;
double x[10] , y[10];



void solve(){
    double r = 10;
    double v0 = 5;
    //start
    x[1] = y[1] = 0;
    //end
    x[2] = y[2] = 300;
    //圆心
    x[5] = 80 ; y[5] = 210;
    //切点
    x[3] = 8064.0/101.0 - pow(252*14,(1/2))/101.0;
    y[3] = pow(96*14,(1/2))/101 + 21168.0/101.0;

    x[4] = 9084.0/113 - pow(36*141,(1/2))/113.0;
    y[4] = pow(88*141,(1/2))/113 + 23748.0/113;
    double a = sqrt((x[2]-x[1])*(x[2]-x[1]) + (y[2]-y[1])*(y[2]-y[1]) );
    double b = sqrt((x[5]-x[1])*(x[5]-x[1]) + (y[5]-y[1])*(y[5]-y[1]) );
    double c = sqrt((x[4]-x[2])*(x[4]-x[2]) + (y[4]-y[2])*(y[4]-y[2]) );
    double ans = (sqrt(b*b-r*r)+sqrt(c*c-r*r)) / v0;

    double a1 = acos((b*b+c*c-a*a)/(2*c*b));
    double a2 = acos(r/b);
    double a3 = acos(r/c);

    //             pi
    ans += r * (2* acos(-1) - a1 - a2 - a3) / (v0/(1+exp(10-0.1*r*r)));
    cout << ans;

}

signed main(){
    int _=1;
    //cin>>_;
    while(_--) { solve();}
    return 0;
}