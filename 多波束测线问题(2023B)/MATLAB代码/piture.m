%{
data = [1918.973204	2330.487032	3325.537551	2330.487032	1918.973204	2330.487032	3325.537551	2330.487032];
x = [0 45 90 135 180 225 270 315];
plot(x,data);
%}
theta =120;
alpha = 1.5;
beta = 0:360;
lambda = atan(-tand(alpha) * cosd(beta));

Wa = zeros(361,360);
Wb = zeros(361,360);
W = zeros(361,360);
D = zeros(361,360);
D(1,1) = 120;
d = 0:0.1:3.6 * 1852;

for i = 1:361
    for j = 1:360
        D(i,j) = D(1,1) - d(j) * tan(lambda(i));
        Wa(i,j) = D(i,j)/(sind(90 + lambda(i) - theta/2)) * sind(theta/2);
        Wb(i,j) = D(i,j)/(sind(90 - lambda(i) - theta/2)) * sind(theta/2);
        W(i,j) = Wa(i,j) + Wb(i,j);
    end
end
data = zeros(361,1);
for i = 1:361
    for j = 1:360
        data(i) = data(i) + W(i,j);
    end
end

x = 0:360;
plot(x,data);
