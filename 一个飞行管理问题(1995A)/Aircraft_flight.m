
x = [150,85,150,145,130,0];
y = [140,85,155,50,150,0];
%angle = [243,236,220.5,159,230,52];
angle = [243,236,2.209133521384421e+02,159,2.308646018878953e+02,52.809933356945920];
round = 0:pi/180:2*pi;
%plot(x,y,'o');
%grid on;
xlim([0,160]);
ylim([0,160]);
title('飞机位置分布图');
%hold on;
%for i=1:6
%    text(x(i)+0.2,y(i),int2str(i));
%end

%手动修改角度
%answer = 4
%angle(6) = 53;
%angle(3) = 223.5;

%angle(5) = 231;
%angle(6) = 53;

%飞行图 + 判断相撞
flag = false;
for t=1:130
    for i=1:6
        xx = x(i) + t * cosd(angle(i)) ;
        yy = y(i) + t * sind(angle(i)) ;
        
        %判断是否相撞
        for j=1:6
            if i==j
                continue;
            end
            xxj = x(j) + t * cosd(angle(j)) ;
            yyj = y(j) + t * sind(angle(j)) ;
            juli = sqrt((xxj-xx)^2 + (yyj-yy)^2);
            if juli<=8
                flag = true;
                break;
            end
        end
        %画图
        xlim([0,160]);
        ylim([0,160]);  
        grid on;
        plot(xx+ 4*cos(round),yy + 4*sin(round));
        hold on;
        text(xx,yy,int2str(i));
    end
    hold off;
    pause(0.01);
end

%changeangle(x,y,angle,1,0)

