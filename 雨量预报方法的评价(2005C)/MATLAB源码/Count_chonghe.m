%计算实测点和预测点重合的点

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

