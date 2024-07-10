y1 = zeros(1,1000);
y2 = zeros(1,1000);
x = zeros(1,1000);
y1(1)=1;
y2(1)=2;
x(1)=0;
h=0.01;
xlim([0,6]);
ylim([0,100]);

for n=1:1000
    y2(n+1)=y2(n)+h*(2*y2(n)-y1(n));
    y1(n+1)=y1(n)+h*y2(n);
    x(n+1)=x(n)+h;
end

%plot(x,y1,'-');
hold on;
%四阶龙格-库塔方法
y1 = zeros(1,1000);
y2 = zeros(1,1000);
x = zeros(1,1000);
y1(1)=1;
y2(1)=2;
x(1)=0;
for n=1:1000
    k1 = h*(2*y2(n)-y1(n));%h*f(x(n),y(n))
    k2 = h*(2*(y2(n)+k1/2)-(y1(n)+h/2));%h*f(x(n)+h/2,y(n)+k1/2)
    k3 = h*(2*(y2(n)+k2/2)-(y1(n)+h/2));%h*f(x(n)+h/2,y(n)+k2/2)
    k4 = h*(2*(y2(n)+k3)-(y1(n)+h));%h*f(x(n)+h,y(n)+k3)

    y2(n+1)=y2(n)+(1/6)*(k1+2*k2+2*k3+k4);
    
    k1 = h*y2(n);%h*f(x(n),y1(n))
    k2 = h*(y2(n)+h/2);%h*f(x(n)+h/2,y(n)+k1/2)
    k3 = h*(y2(n)+h/2);%h*f(x(n)+h/2,y(n)+k2/2)
    k4 = h*(y2(n)+h);%h*f(x(n)+h,y(n)+k3)
    y1(n+1)=y1(n)+(1/6)*(k1+2*k2+2*k3+k4);
    
    x(n+1)=x(n)+h;
end
plot(x,y1,'-');

%

ezplot('exp(x)+x*exp(x)');
xlim([0,6]);
ylim([0,100]);