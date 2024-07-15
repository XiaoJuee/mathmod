theta =deg2rad(120);
alpha =deg2rad(1.5);
%D = 70;
%{
Wa0 = D/(sin(pi/2 + alpha - theta/2)) * sin(theta/2);
Wb0 = D/(sin(pi/2 - alpha - theta/2)) * sin(theta/2);
W0 = Wa0 + Wb0;

d = 200;
D200 = D - d * tan(alpha);
Wa200 = D200/(sin(pi/2 + alpha - theta/2)) * sin(theta/2);
Wb200 = D200/(sin(pi/2 - alpha - theta/2)) * sin(theta/2);
W200 = Wa200 + Wb200;
%}
W = zeros(9,1);
Wa = zeros(9,1);
Wb = zeros(9,1);
D = zeros(9,1);
D(5) = 70;
for d = -800 : 200 : 800
    D((d+1000)/200) = D(5) - d * tan(alpha);
    Wa((d+1000)/200) = D((d+1000)/200)/(sin(pi/2 + alpha - theta/2)) * sin(theta/2);
    Wb((d+1000)/200) = D((d+1000)/200)/(sin(pi/2 - alpha - theta/2)) * sin(theta/2);
    W((d+1000)/200) = Wa((d+1000)/200) + Wb((d+1000)/200);
end
C = zeros(9,1);
C(1) = -1;
for d = -600 : 200 : 800
    C((d+1000)/200) = Wa((d+1000-200)/200) + Wb((d+1000)/200) - (200/cos(alpha));
end