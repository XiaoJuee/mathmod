%%算重叠率超过百分之20的部分
%
% 读取数据
data = xlsread('问题4数据.xlsx');
% 提取坐标和深度数据
x = data(1, 2:end); % 第一行除去第一个元素为 x 坐标
y = data(2:end, 1); % 第一列除去第一个元素为 y 坐标
depth = data(2:end, 2:end); % 深度数据
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%init
AG = 0; %3017
AC_tiao = 4053; % 提前跑出来  4053
AC = 0; %3248
AB = 0; %5956
EB = 0; %3207
BC = 0; %4577
CB = 0;
CF = 0; %107

WB = zeros(3*1852,1);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%A区 坡面 A 超出部分。
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
long = 4.5-1.5;
short = 2.5-0;
x = 1:short*1852;
%角度计算
theta =120;
alpha = atan(0.0304);
beta = 180;
lambda = atan(-tan(alpha) * cosd(beta));

WR = zeros(long*1852,1);
WL = zeros(long*1852,1);
W = zeros(long*1852,1);
D = zeros(long*1852,1);

Dnorth = depth(1,201); %最深的

l = 1:long*1852;
for i = 1:long*1852
    D(i) = Dnorth - l(i) * tan(lambda);
    WR(i) = D(i)/(sind(90 + lambda - theta/2)) * sind(theta/2);
    WL(i) = D(i)/(sind(90 - lambda- theta/2)) * sind(theta/2);
    W(i) = WR(i) + WL(i);
end

%每m的海深度求出，宽度求出，按照平坦的去算

%eta = 1 - d/w
%d = w*(1 - eta)
d = zeros(long*1852,1);
for i = 1:long*1852
    d(i) = W(i) * (1-0.1);
end

%估计侧线的数量
sum = 0;
for i = 1:long*1852
    sum = short*1852/d(i) + sum;
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% A
Aover = zeros(long*1852,1);
for i = 1:long*1852
     y = WL(i);
     while 1
         if y+WR(i) > short*1852
             Aover(i) = short*1852 - y+WR(i);
             break;
         end
         y = y + d(i);
         if i > long*1852-59.327414166212040
             AG = AG + 1;
         end
     end
     %if i <=  4053
     %    AC = AC + Aover(i);
     %end
end

%
%坡面 B over。
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
long = 4-1;
short = 1.5-0;
x = 1:short*1852;
%角度计算
theta =120;
alpha = atan(0.0076);
beta = 180;
lambda = atan(-tan(alpha) * cosd(beta));

WR = zeros(long*1852,1);
WL = zeros(long*1852,1);
W = zeros(long*1852,1);
D = zeros(long*1852,1);

Dnorth = 68.54; %最深的

l = 1:long*1852;
for i = 1:long*1852
    D(i) = Dnorth - l(i) * tan(lambda);
    WR(i) = D(i)/(sind(90 + lambda - theta/2)) * sind(theta/2);
    WL(i) = D(i)/(sind(90 - lambda- theta/2)) * sind(theta/2);
    W(i) = WR(i) + WL(i);
    WB(i) = W(i);
end

%每m的海深度求出，宽度求出，按照平坦的去算

%eta = 1 - d/w
%d = w*(1 - eta)
d = zeros(long*1852,1);
for i = 1:long*1852
    d(i) = W(i) * (1-0.1);
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% B
Bover = zeros(long*1852,1);
for i = 1:long*1852
     y = WL(i);
     sumAB =  0;
     sumEB = 0;
     while 1
         if y+WR(i) > short*1852
             Bover(i) = short*1852 - y+WR(i);
             if 1-(d(i)/(WR(i)+WL(i))) > 0.2
                CB = CB + 1;
             end
             break;
         end
         y = y + d(i);
         sumAB = sumAB + 1;
         if Eover(int16(y)) > i - Eover(int16(y))
             EB = EB + 1;
         end
     end
     if i < Aover(i)
             AB = AB + sumAB;
     end
     
end

%
%坡面 Cover。
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
long = 4-1.5;
short = 4-2.5;
x = 1:short*1852;
%角度计算
theta =120;
alpha = atan(0.02654);
beta = 180;
lambda = atan(-tan(alpha) * cosd(beta));

WR = zeros(long*1852,1);
WL = zeros(long*1852,1);
W = zeros(long*1852,1);
D = zeros(long*1852,1);

Dnorth = 123.1; %最深的

l = 1:long*1852;
for i = 1:long*1852
    D(i) = Dnorth - l(i) * tan(lambda);
    WR(i) = D(i)/(sind(90 + lambda - theta/2)) * sind(theta/2);
    WL(i) = D(i)/(sind(90 - lambda- theta/2)) * sind(theta/2);
    W(i) = WR(i) + WL(i);
end

%每m的海深度求出，宽度求出，按照平坦的去算

%eta = 1 - d/w
%d = w*(1 - eta)
d = zeros(long*1852,1);
for i = 1:long*1852
    d(i) = W(i) * (1-0.1);
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% C

Cover = zeros(long*1852,1);
for i = 1:long*1852
     y = WL(i);
     sumAC = 0;
     while 1
         if y+WR(i) > short*1852
             Cover(i) = short*1852 - y+WR(i);
             %if 1-(d(i)/(WR(i)+WL(i))) > 0.2
             %   BC = BC + 1;
             %end
             if (Bover(i) + Cover(i))/(WB(i)+W(i)-(Bover(i) + Cover(i)))>0.2
                 BC = BC + 1;
             end
             break;
         end
         y = y + d(i);
         %if i == long*1852
         %   AC_tiao = AC_tiao + 1;
         %end
         sumAC = sumAC + 1;
     end
     if i < Aover(i)
         AC = AC + sumAC;
     end
     if i > long*1852 - 1.060927859705716e+02
         CF = CF + 1;
     end
end

%
%坡面 E over。
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
long = 2.5-0;
short = 5-4.5;
x = 1:short*1852;
%角度计算
theta =120;
alpha = atan(0.0108);
beta = 180;
lambda = atan(-tan(alpha) * cosd(beta));

WR = zeros(long*1852,1);
WL = zeros(long*1852,1); 
W = zeros(long*1852,1);
D = zeros(long*1852,1);

Dnorth = 82; %最深的

l = 1:long*1852;
for i = 1:long*1852
    D(i) = Dnorth - l(i) * tan(lambda);
    WR(i) = D(i)/(sind(90 + lambda - theta/2)) * sind(theta/2);
    WL(i) = D(i)/(sind(90 - lambda- theta/2)) * sind(theta/2);
    W(i) = WR(i) + WL(i);
end

%每m的海深度求出，宽度求出，按照平坦的去算

%eta = 1 - d/w
%d = w*(1 - eta)
d = zeros(long*1852,1);
for i = 1:long*1852
    d(i) = W(i) * (1-0.1);
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% E
Eover = zeros(long*1852,1);
for i = 1:long*1852
     y = WL(i);
     while 1
         if y+WR(i) > short*1852
             Eover(i) = short*1852 - y+WR(i);
             break;
         end
         y = y + d(i);
     end
end


%
%平面 G over。
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
long = 1.5-0;
short = 1-0;
x = 1:short*1852;
%角度计算
theta =120;
alpha = atan(0);
beta = 180;
lambda = atan(-tan(alpha) * cosd(beta));

WR = zeros(long*1852,1);
WL = zeros(long*1852,1); 
W = zeros(long*1852,1);
D = zeros(long*1852,1);

Dnorth = 23; %最深的

l = 1:long*1852;
for i = 1:long*1852
    D(i) = Dnorth - l(i) * tan(lambda);
    WR(i) = D(i)/(sind(90 + lambda - theta/2)) * sind(theta/2);
    WL(i) = D(i)/(sind(90 - lambda- theta/2)) * sind(theta/2);
    W(i) = WR(i) + WL(i);
end

%每m的海深度求出，宽度求出，按照平坦的去算

%eta = 1 - d/w
%d = w*(1 - eta)
d = zeros(long*1852,1);
for i = 1:long*1852
    d(i) = W(i) * (1-0.1);
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% G
Gover = zeros(long*1852,1);
for i = 1:long*1852
     y = WL(i);
     while 1
         if y+WR(i) > short*1852
             Gover(i) = short*1852 - y+WR(i);
             break;
         end
         y = y + d(i);
     end
end


%
%平面 F。
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
long = 4-2.5;
short = 5-4;
x = 1:short*1852;
%角度计算
theta =120;
alpha = atan(0);
beta = 180;
lambda = atan(-tan(alpha) * cosd(beta));

WR = zeros(long*1852,1);
WL = zeros(long*1852,1); 
W = zeros(long*1852,1);
D = zeros(long*1852,1);

Dnorth = 70; %最深的

l = 1:long*1852;
for i = 1:long*1852
    D(i) = Dnorth - l(i) * tan(lambda);
    WR(i) = D(i)/(sind(90 + lambda - theta/2)) * sind(theta/2);
    WL(i) = D(i)/(sind(90 - lambda- theta/2)) * sind(theta/2);
    W(i) = WR(i) + WL(i);
end

%每m的海深度求出，宽度求出，按照平坦的去算

%eta = 1 - d/w
%d = w*(1 - eta)
d = zeros(long*1852,1);
for i = 1:long*1852
    d(i) = W(i) * (1-0.1);
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  F
Fover = zeros(long*1852,1);
for i = 1:long*1852
     y = WL(i);
     while 1
         if y+WR(i) > short*1852
             Fover(i) = short*1852 - y+WR(i);
             break;
         end
         y = y + d(i);
     end
end

