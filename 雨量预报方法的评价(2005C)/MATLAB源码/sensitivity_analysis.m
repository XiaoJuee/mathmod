%敏感度分析，求出合理的平滑值

%{
z = cell(7,30,4);%月份,日期,时间段-加权值
dis=cell(7,30,4,2);%月份,日期,时段，方法 %预测
for month = 6:7 
    for day = 1:30
        if month==6 && day<18 || day > 28
            continue;
        end
        for time = 1:4
            z{month,day,time}=importdata(['m',num2str(month,'%02d'),'d',num2str(day,'%02d'),'t',num2str(time,'%02d'),'.cvs']);
            for method = 1:2
                dis{month,day,time,method} = importdata(['f',num2str(month),num2str(day,'%02d'),num2str(time),'_dis',num2str(method)]);
            end
        end
    end
end
%}

%绝对误差
Ea = cell(7,30,4,2);%月份,日期,时间段,方法
%相对误差 R
R =  cell(7,30,4,2);%月份,日期,时间段,方法
ping = 100;%平滑值
wubao_wutoyou = zeros(2,1);
wubao_youtowu = zeros(2,1);
count = zeros(2,1);
for month = 6:7 
    for day = 1:30
        if month==6 && day<18 || day > 28
            continue;
        end
        for time = 1:4 %时段
            for method = 1:2
                R{month,day,time,method} = zeros(53,47);
                for i = 1:53
                    for j = 1:47
                        Ea{month,day,time,method}(i,j) = abs(dis{month,day,time,method}(i,j)-z{month,day,time}(i,j));
                        if(z{month,day,time}(i,j)==0)%加平滑值 + 计数
                            if(dis{month,day,time,method}(i,j)>0.1)%误报计数
                                wubao_wutoyou(method) = wubao_wutoyou(method) + 1;
                            end
                            count(method) = count(method) + 1;
                            dis{month,day,time,method}(i,j) = dis{month,day,time,method}(i,j) + ping;
                            z{month,day,time}(i,j) = z{month,day,time}(i,j) + ping;
                            R{month,day,time,method}(i,j) = abs(dis{month,day,time,method}(i,j)-z{month,day,time}(i,j))/(z{month,day,time}(i,j));
                            z{month,day,time}(i,j) = z{month,day,time}(i,j) - ping;
                            dis{month,day,time,method}(i,j) = dis{month,day,time,method}(i,j) - ping;
                        else
                            R{month,day,time,method}(i,j) = abs(dis{month,day,time,method}(i,j)-z{month,day,time}(i,j))/(z{month,day,time}(i,j));
                        end
                        if(dis{month,day,time,method}(i,j)<=0.1)
                            if(z{month,day,time}(i,j)>0.1)
                                 wubao_youtowu(method) = wubao_youtowu(method) + 1;
                            end
                        end
                            
                    end
                end
            end%method
        end%time
    end%day
end%moth

%计算两个方法的相对误差平均值 和 绝对误差平均值
PEa = zeros(2,1);
PR = zeros(2,1);
for method = 1:2
    for month = 6:7 
        for day = 1:30
            if month==6 && day<18 || day > 28
                continue;
            end
            for time = 1:4 %时段
               for i = 1:53
                   for j = 1:47
                           PEa(method) = PEa(method) + Ea{month,day,time,method}(i,j);
                           PR(method) = PR(method) + R{month,day,time,method}(i,j);
                   end
               end
            end%time
        end%day
    end%moth
    PEa(method) = PEa(method)/(41*4*53*47);
    PR(method) = PR(method)/(41*4*53*47);
end

%PR
%100
%方法一 0.730072429550441
%方法二 0.728545491308364

%10
%方法一 0.730127208097747
%方法二 0.728597758279525

%5
%方法一 0.730188073150308
%方法二 0.728655832691922

%1.111111
%方法一 0.730614128573019
%方法二 0.729062353630984

%1.1
%方法一 0.730619661704834
%方法二 0.729067633070754

%1
%方法一 0.730674993570798
%方法二 0.729120427991114

%0.1
%方法一 0.736152848301342
%方法二 0.734347125106995

%0.01
%方法一 0.790931395606751
%方法二 0.786614096265792

%0.001
%方法一 1.338716868660809
%方法二 1.309283807853811

%0.0001
%方法一 6.816571599201594
%方法二 6.535980923733801

%0.00001
%方法一 61.595118904607766
%方法二 58.802952082533860


