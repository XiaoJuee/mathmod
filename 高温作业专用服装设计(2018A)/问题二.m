rho = [300, 862, 74.2, 1.18]; %密度
c = [1377, 2100, 1726, 1005]; %比热
k = [0.082, 0.37, 0.045, 0.028]; %热传导系数
kd =1 ;
for k_d2 = 0.0006:0.0001:0.025
    
k_out = 108; 
k_skin = 8.3;

d = [0.0006, k_d2, 0.0036, 0.0055]; %每层的厚度
dt = 1; %温度步长
dx = 0.1 * 10^(-3); %距离步长

r1 = k(1) * dt / (c(1) * rho(1) * dx * dx);
r2 = k(2) * dt / (c(2) * rho(2) * dx * dx);
r3 = k(3) * dt / (c(3) * rho(3) * dx * dx);
r4 = k(4) * dt / (c(4) * rho(4) * dx * dx);

N = round(sum(d) / dx + 1);
A = zeros(N); %等式左边（中间变量矩阵）

%左边界条件
A(1, 1) = 1 + 2 * r1 + 2 * dx * k_out * r1 / k(1);

%第I层
A(1, 2) = -2 * r1;
d1 = round(d(1) / dx + 1); %步数
for i = 2 : d1 - 1
    A(i, i) = 1 + 2 * r1;
    A(i, i - 1) = -r1;
    A(i, i + 1) = -r1;
end

%第I层与第II层接触面
A(d1, d1 - 1) = -k(1) / dx;
A(d1, d1 + 1) = -k(2) / dx;
A(d1, d1) = -(A(d1, d1 - 1) + A(d1, d1 + 1));

%第II层
d2 = d1 + round(d(2) / dx);
for i = d1 + 1 : (d2 - 1)
    A(i, i) = 1 + 2 * r2;
    A(i, i - 1) = -r2;
    A(i, i + 1) = -r2;
end

%第II层与第III层接触面
A(d2, d2 - 1) = -k(2) / dx;
A(d2, d2 + 1) = -k(3) / dx;
A(d2, d2) = -(A(d2, d2 - 1) + A(d2, d2 + 1));

%第III层
d3 = d2 + round(d(3) / dx);
for i = d2 + 1 : (d3 - 1)
    A(i, i) = 1 + 2 * r3;
    A(i, i - 1) = -r3;
    A(i, i + 1) = -r3;
end

%第III层与第IV层接触面
A(d3, d3 - 1) = -k(3) / dx;
A(d3, d3 + 1) = -k(4) / dx;
A(d3, d3) = -(A(d3, d3 - 1) + A(d3, d3 + 1));

%第IV层
d4 = d3 + round(d(4) / dx);
for i = d3 + 1 : (d4 - 1)
    A(i, i) = 1 + 2 * r4;
    A(i, i - 1) = -r4;
    A(i, i + 1) = -r4;
end

%右边界条件
A(d4, d4) = 1 + 2 * r4 + 2 * dx * k_skin * r4 / k(4);
A(d4, d4 - 1) = -2 * r4;

%温度
U = zeros(3601, N);
U(1, :) = 37;

%解线性方程，求出温度
for i = 1 : 3600
    b = U(i, :)';
    b(1) = b(1) + 2 * dx * k_out * 65 * r1 / k(1);
    b(N) = b(N) + 2 * dx * r4 * k_skin * 37 / k(4);
    b(d1) = 0;
    b(d2) = 0;
    b(d3) = 0;
    U(i + 1, :) = A \ b;
end
sum_ = 0;
for i = 1:3601
    if U(i,d4) > 44.0000
        sum_ = sum_ + 1;
    end
end
if sum_ <= 300
    kd = min(k_d2,kd);
    break;
end
end
k_d2 = kd;


%%%%%%%%%%%%%%%%
    
k_out = 108; 
k_skin = 8.3;

d = [0.0006, k_d2, 0.0036, 0.0055]; %每层的厚度
dt = 1; %温度步长
dx = 0.1 * 10^(-3); %距离步长

r1 = k(1) * dt / (c(1) * rho(1) * dx * dx);
r2 = k(2) * dt / (c(2) * rho(2) * dx * dx);
r3 = k(3) * dt / (c(3) * rho(3) * dx * dx);
r4 = k(4) * dt / (c(4) * rho(4) * dx * dx);

N = round(sum(d) / dx + 1);
A = zeros(N); %等式左边（中间变量矩阵）

%左边界条件
A(1, 1) = 1 + 2 * r1 + 2 * dx * k_out * r1 / k(1);

%第I层
A(1, 2) = -2 * r1;
d1 = round(d(1) / dx + 1); %步数
for i = 2 : d1 - 1
    A(i, i) = 1 + 2 * r1;
    A(i, i - 1) = -r1;
    A(i, i + 1) = -r1;
end

%第I层与第II层接触面
A(d1, d1 - 1) = -k(1) / dx;
A(d1, d1 + 1) = -k(2) / dx;
A(d1, d1) = -(A(d1, d1 - 1) + A(d1, d1 + 1));

%第II层
d2 = d1 + round(d(2) / dx);
for i = d1 + 1 : (d2 - 1)
    A(i, i) = 1 + 2 * r2;
    A(i, i - 1) = -r2;
    A(i, i + 1) = -r2;
end

%第II层与第III层接触面
A(d2, d2 - 1) = -k(2) / dx;
A(d2, d2 + 1) = -k(3) / dx;
A(d2, d2) = -(A(d2, d2 - 1) + A(d2, d2 + 1));

%第III层
d3 = d2 + round(d(3) / dx);
for i = d2 + 1 : (d3 - 1)
    A(i, i) = 1 + 2 * r3;
    A(i, i - 1) = -r3;
    A(i, i + 1) = -r3;
end

%第III层与第IV层接触面
A(d3, d3 - 1) = -k(3) / dx;
A(d3, d3 + 1) = -k(4) / dx;
A(d3, d3) = -(A(d3, d3 - 1) + A(d3, d3 + 1));

%第IV层
d4 = d3 + round(d(4) / dx);
for i = d3 + 1 : (d4 - 1)
    A(i, i) = 1 + 2 * r4;
    A(i, i - 1) = -r4;
    A(i, i + 1) = -r4;
end

%右边界条件
A(d4, d4) = 1 + 2 * r4 + 2 * dx * k_skin * r4 / k(4);
A(d4, d4 - 1) = -2 * r4;

%温度
U = zeros(3601, N);
U(1, :) = 37;

%解线性方程，求出温度
for i = 1 : 3600
    b = U(i, :)';
    b(1) = b(1) + 2 * dx * k_out * 65 * r1 / k(1);
    b(N) = b(N) + 2 * dx * r4 * k_skin * 37 / k(4);
    b(d1) = 0;
    b(d2) = 0;
    b(d3) = 0;
    U(i + 1, :) = A \ b;
end



t = 1:3601;
xlabel('时间(s)');
ylabel('温度(度)');
title('皮肤外侧的温度随时间变化图');
hold on
plot(t, U(:, d4), 'r')

figure
mesh(U)
xlabel('位置');
ylabel('时间');
zlabel('温度');

