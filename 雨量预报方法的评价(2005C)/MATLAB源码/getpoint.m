%读取经纬度，通过墨卡托投影法将经纬度转换为平面坐标，再将对应平面坐标保存坐标进execl
lon = importdata('lon.dat');%经度-预测点
lat = importdata('lat.dat');%纬度-预测点

%墨卡托投影法
earthRad = 6378137.0;
x = ((lon .* pi) ./ 180) .* earthRad;
a = (lat .* pi) ./ 180;
y = (earthRad ./ 2) .* log((1.0 + sin(a)) ./ (1.0 - sin(a)));
%保存进execl
xlswrite('xpoint.xls',x);
xlswrite('ypoint.xls',y);

mea=cell(7,30);%月份,日期, 测量实际值
for month = 6:7 
    for day = 1:30
        if month==6 && day<18 || day > 28
            continue;
        end
        mea{month,day}=importdata(['02',num2str(month,'%02d'),num2str(day,'%02d'),'.SIX']);%读取文件
    end
end


lon2 = zeros(91,1);%经度-实测点
lat2 = zeros(91,1);%纬度-实测点

for i=1:91
    lon2(i) = mea{7,1}(i,3);
    lat2(i) = mea{7,1}(i,2);
end

x2 = ((lon2 .* pi) ./ 180) .* earthRad;
a2 = (lat2 .* pi) ./ 180;
y2 = (earthRad ./ 2) .* log((1.0 + sin(a2)) ./ (1.0 - sin(a2)));
xlswrite('shice_xpoint.xls',x2);
xlswrite('shice_ypoint.xls',y2);