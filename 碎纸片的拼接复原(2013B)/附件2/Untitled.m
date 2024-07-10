d =cell(1,19);
for i = 1:19
    imageName=strcat(num2str(i-1,'%03d'),'.bmp');
    d{i}=imread(imageName);
end
ansd = [d{4},d{7},d{3},d{8},d{16},d{19},d{12},d{1},d{6},d{2},d{10},d{14},d{11},d{9},d{13},d{15},d{18},d{17},d{5}];
imshow(ansd);
imwrite(ansd,'result.bmp');
%{
a = cell(19,19);
for i = 1:19
    for j = 1:19
        sum = 0;
        for jj = 1:1980
            sum = sum + abs( double(d{i}(jj,72))-double(d{j}(jj,1)) );% j在i后面的差值
        end
        a{i,j} = sum; % 顺序是 i j
    end
end
xlswrite('D:\homewrok\建模\纸片\201391394826489\2013年全国大学生数学建模竞赛B题附件\附件2\a.xls', a);
%}