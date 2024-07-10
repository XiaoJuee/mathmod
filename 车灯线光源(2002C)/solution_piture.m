cost1 = zeros(31,1);
cost2 = zeros(31,1);
l = 4;
cha = 1;
for i = 1:0.1:4
    
    for x1 = -i:0.1:i
        for x0 = -36:0.1:36
            for z0 = -36:0.1:36
                y0 = (x0^2+z0^2)/60;
                t = (2*x1*x0-2*x0^2+60*y0-2*z0^2-900) / (4*x0^2+3600+4*z0^2);
                x2 = 4*x0*t + 2*x0 - x1;
                y2 = -120*t + 2*y0 - 15;
                z2 = 4*z0*t + 2*z0;
                %在焦点F正前方25米处的A(0,25015,0)点;
                %G点
                x3 = (25015-y0)/(y2-y0)*(x2-x0)+x0;
                z3 = (25015-y0)/(y2-y0)*(z2-z0)+z0;
                %C(2600,25015,0)
                if sqrt((x3-2600)^2 + z3^2)<cha
                    cost1(i*10-9)=cost1(i*10-9)+1;
                elseif sqrt((x3-1300)^2 + z3^2)<cha
                    cost2(i*10-9)=cost2(i*10-9)+1;
                end
            end
        end
    end
    if cost1(i*10-9) >= 2 && cost2(i*10-9) >=4 && abs(x1)<l
       l = abs(i);
   end
end
l %3.1126