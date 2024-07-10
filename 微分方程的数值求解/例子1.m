% y = zeros(1,1000);
% x = zeros(1,1000);
% y(1)=1;
% x(1)=0;
% h=0.01;
% 
% for n=1:1000
%     y(n+1)=y(n)+h*x(n)*y(n);
%     x(n+1)=x(n)+h;
% end
% plot(x,y,'-');
% hold on;

ezplot('exp(x^2/2)');
hold on;
%四阶龙格-库塔方法
y = zeros(1,1000);
x = zeros(1,1000);
y(1)=1;
x(1)=0;
h=0.1;
for n=1:1000
    k1 = h*(x(n)*y(n));%h*f(x(n),y(n))
    k2 = h*((x(n)+h/2)*(y(n)+k1/2));%h*f(x(n)+h/2,y(n)+k1/2)
    k3 = h*((x(n)+h/2)*(y(n)+k2/2));%h*f(x(n)+h/2,y(n)+k2/2)
    k4 = h*((x(n)+h)*(y(n)+k3));%h*f(x(n)+h,y(n)+k3)
    y(n+1)=y(n)+(1/6)*(k1+2*k2+2*k3+k4);
    y(1)=1;
    x(n+1)=x(n)+h;
end
plot(x,y,'-');
xlim([0,6]);
ylim([0,100]);
