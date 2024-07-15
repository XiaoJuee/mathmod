theta =deg2rad(120);
alpha = deg2rad(1.5);
beta = deg2rad([0 45 90 135 180 225 270 315]);
lambda = tan(alpha) * cos(beta);

Wa = zeros(8,8);
Wb = zeros(8,8);
W = zeros(8,8);
D = zeros(8,8);
D(1,1) = 120;
d = [0,0.3,0.6,0.9,1.2,1.5,1.8,2.1];
for i = 1:8
    for j = 1:8
        D(i,j) = D(1,1) - d(j) * tan(lambda(i));
        Wa(i,j) = D(i,j)/(sin(pi/2 + lambda(i) - theta/2)) * sin(theta/2);
        Wb(i,j) = D(i,j)/(sin(pi/2 - lambda(i) - theta/2)) * sin(theta/2);
        W(i,j) = Wa(i,j) + Wb(i,j);
    end
end
