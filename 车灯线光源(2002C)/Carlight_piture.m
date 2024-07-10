clear,clc
a=2;
u=0:0.01:2*pi;
theta=0:pi/100:2*pi;
[U,Theta]=meshgrid(u,theta);   %生成二维网格序列
X=U.*sin(Theta);
Y=U.*cos(Theta);
Z=U.^2.*a;
mesh(X,Y,Z)
xlabel('x轴')
ylabel('y轴')
zlabel('z轴')
title('z=sin(x)绕z轴旋转')
%surf(X,Y,Z)