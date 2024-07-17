%对垂直于等深线的情况进行分析求解
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
x = 1:2*1852;

%角度计算
theta =120;
alpha = 1.5;
beta = 180;
lambda = atan(-tand(alpha) * cosd(beta));

WR = zeros(4*1852,1);
WL = zeros(4*1852,1);
W = zeros(4*1852,1);
D = zeros(4*1852,1);
Dmid = 110;
dnorth = -2/2 * 1852;
Dnorth = Dmid - dnorth * tan(alpha); %最深的
%l = [-x , x];%离散化
l = -1852*2:2*1852;
for i = 1:4*1852
    D(i) = Dmid - l(i) * tan(lambda);
    WR(i) = D(i)/(sind(90 + lambda - theta/2)) * sind(theta/2);
    WL(i) = D(i)/(sind(90 - lambda - theta/2)) * sind(theta/2);
    W(i) = WR(i) + WL(i);
end

%每m的海深度求出，宽度求出，按照平坦的去算

%eta = 1 - d/w
%d = w*(1 - eta)
d = zeros(4*1852,1);
for i = 1:4*1852
    d(i) = W(i) * (1-0.1);
end

%估计侧线的数量
sum = 0;
for i = 1:4*1852
    sum = 2*1852/d(i) + sum;
end
sum

%对平行于等深线的情况进行分析求解
%已求出测线组数n = 35
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
n = 35;
sum2 = 2*1852*n;

%画图
%对垂直于等深线的情况
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
x_ = [];
y_ = [];
for i = 1:4*1852
     y = WL(i);
     x_ = [x_ , i];
     y_ = [y_ , y];
     while 1
         if y+WR(i) > 2*1852
             break;
         end
         y = y + d(i);
         x_ = [x_ , i];
         y_ = [y_ , y];
     end
end
plot(x_,y_,'.');
