%对平行于等深线的情况进行分析求解
%弧度计算
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
alpha = deg2rad(1.5);
theta =deg2rad(120);
Dmin = 110;%海域中心点处的海水深度
dwest = -4/2 * 1852;
Dwest = Dmin - dwest * tan(alpha); %最深的

WRwest = Dwest/(sin(pi/2 + alpha - theta/2)) * sin(theta/2);%假设最深处有船，算其WRwest
D1 = WRwest * (sin(pi/2 - alpha - theta/2))/sin(theta/2);%根据WRwest当作WL1反推深度D1
d1 = (Dmin - D1)/tan(alpha);%深度D1反推距离海域中心点的距离

deast = 4/2 * 1852;
Deast = Dmin - deast * tan(alpha); %最浅的

WLeast = Deast/(sin(pi/2 - alpha - theta/2)) * sin(theta/2);%假设最深处有船，算其WLeast
Dn = WLeast * (sin(pi/2 + alpha - theta/2))/sin(theta/2);%根据WLeast当作WRn反推深度Dn
dn = (Dmin - Dn)/tan(alpha);%深度Dn反推距离海域中心点的距离

%
WR1 = D1/(sin(pi/2 + alpha - theta/2)) * sin(theta/2);
WL1 = D1/(sin(pi/2 - alpha - theta/2)) * sin(theta/2);
%

D = [D1];%海深
d = [d1];%距离海域中心点的距离
WR = [WR1];
WL = [WL1];
W = [WR1+WL1];
n = 1;
while 1
    Dnext_Numerator = ( WR(n) - 0.1*W(n) + 0.1*WR(n) - 0.1*(D(n)/(tan(alpha)*cos(alpha))) - D(n)/(tan(alpha)*cos(alpha)) ); %Dnext分子
    Dnext_denominator = 0.1* sin(theta/2) * (1/(sin(pi/2 + alpha - theta/2))) -  sin(theta/2) * (1/(sin(pi/2 - alpha - theta/2))) -  0.1*(1/(tan(alpha)*cos(alpha))) - (1/(tan(alpha)*cos(alpha))); %Dnext分母
    Dnext = Dnext_Numerator/Dnext_denominator;
    if Dnext < Dn || D(n) == Dnext
        break;
    end
    dnext = (Dmin - Dnext) / tan(alpha);
    WRnext = Dnext/(sin(pi/2 + alpha - theta/2)) * sin(theta/2);
    WLnext = Dnext/(sin(pi/2 - alpha - theta/2)) * sin(theta/2);
    Wnext = WRnext + WLnext;
    D = [D , Dnext];
    WR = [WR , WRnext];
    WL = [WL , WLnext];
    W = [W,Wnext];
    d = [d,dnext];
    n = n+1;
end

%画图
%对平行于等深线的情况
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
x_ = [];
y_ = [];
for i = 1:n
     y = 1;
     x_ = [x_ , d(i)];
     y_ = [y_ , y];
     while 1
         if y+1 > 2*1852
             break;
         end
         y = y + 1;
         x_ = [x_ , d(i)];
         y_ = [y_ , y];
     end
end
plot(x_,y_,'.');
