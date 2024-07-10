%读取经纬度，通过墨卡托投影法将经纬度转换为平面坐标,然后通过反距离加权插值计算

%预测点坐标获取
lon = importdata('lon.dat');%经度-预测点
lat = importdata('lat.dat');%纬度-预测点

%墨卡托投影法
earthRad = 6378137.0;
x = ((lon .* pi) ./ 180) .* earthRad;% 53*47
a = (lat .* pi) ./ 180;
y = (earthRad ./ 2) .* log((1.0 + sin(a)) ./ (1.0 - sin(a)));

%实测点坐标获取
mea=cell(7,30);%月份,日期, 测量实际值
for month = 6:7 
    for day = 1:30
        if month==6 && day<18 || day > 28
            continue;
        end
        mea{month,day}=importdata(['02',num2str(month,'%02d'),num2str(day,'%02d'),'.SIX']);
    end
end


lon2 = zeros(91,1);%经度-实测点
lat2 = zeros(91,1);%纬度-实测点
for i=1:91
    lon2(i) = mea{7,1}(i,3);
    lat2(i) = mea{7,1}(i,2);
end

x2 = ((lon2 .* pi) ./ 180) .* earthRad;%91*1
a2 = (lat2 .* pi) ./ 180;
y2 = (earthRad ./ 2) .* log((1.0 + sin(a2)) ./ (1.0 - sin(a2)));




%反距离加权插值法
p = 1;%取值为 1

%计算di-样点与待插值位置的距离
%计算权重 wi ， 是第 i 个样点的权重 wi = 1/(di)^p
d = zeros(53,47,91);%第i行j列的预测点对应的第k个实测点的距离 % 距离和月份,日期,时段无关
wi = zeros(53,47,91);%第i行j列的预测点对应的第k个实测点的权重 % 权重和月份,日期,时段无关
sum_wi = zeros(53,47);%权值求和

for i = 1:53
    for j = 1:47
        for k = 1:91
            d(i,j,k) = sqrt((x(i,j)-x2(k))^2 + (y(i,j)-y2(k))^2);
            if(d(i,j,k) == 0)%如果预测点和实测点重合
                wi(i,j,k) = 0;
                continue;
            end
            sum_wi(i,j) = sum_wi(i,j) + 1/(d(i,j,k));
        end
    end
end


for i = 1:53
    for j = 1:47
        for k = 1:91
            if(d(i,j,k) == 0)%如果预测点和实测点重合
                wi(i,j,k) = 0;
                continue;
            end
            wi(i,j,k) = (1/d(i,j,k))/(sum_wi(i,j));
        end
    end
end

z = cell(7,30,4);%月份,日期,时段



for month = 6:7 
    for day = 1:30
        if month==6 && day<18 || day > 28
            continue;
        end
        for time = 1:4 %时段
            for i=1:53
                for j=1:47
                    sum_wizi = 0;
                    for k = 1:91
                        if(wi(i,j,k)==0)%如果预测点和实测点重合
                            sum_wizi = mea{month,day}(k,time+3)*sum_wi(i,j); % 使后面z等式为实测值
                            break;%直接计算z等式
                        end
                        sum_wizi = sum_wizi + mea{month,day}(k,time+3)*wi(i,j,k);
                    end%k
                    z{month,day,time}(i,j) = sum_wizi;
                end%j
            end%i
        end%time
    end%day
end%moth

%将反距离加权插值法求得数值写入excel文件 or cvs 文件

for month = 6:7 
    for day = 1:30
        if month==6 && day<18 || day > 28
            continue;
        end
        for time = 1:4
            csvwrite(['m',num2str(month,'%02d'),'d',num2str(day,'%02d'),'t',num2str(time,'%02d'),'.cvs'],z{month,day,time});
            xlswrite(['m',num2str(month,'%02d'),'d',num2str(day,'%02d'),'t',num2str(time,'%02d'),'.xls'],z{month,day,time});
        end
    end
end