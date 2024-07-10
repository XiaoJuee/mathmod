d =cell(1,19);
for i = 1:19
    imageName=strcat(num2str(i-1,'%03d'),'.bmp');
    d{i}=imread(imageName);
end
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
xlswrite('D:\homewrok\建模\纸片\201391394826489\2013年全国大学生数学建模竞赛B题附件\附件1\a.xls', a);
%{
for i = 1:19
    for j = 1:19
        sum = 0;
        for jj = 1:1980
            if d{i}(jj,1) == d{j}(jj,72)
                sum=sum+1;
            end
        end
        a{i,j} = sum;
    end
end

c = cell(1,19);
for i = 1:19
    jj = 1;
    maxa = 0;
    for j = 1:19
        if maxa < a{j,i}
            jj = j;
            maxa = a{j,i};
        end
    end
    c{1,i} = jj;
end
disp(c);
i = 9;
ansd=[];
while i~=7
    ansd=[ansd,d{i}];
    i = c(i);
end
ansd=[ansd,d{7}];
imshow(ansd);
%}


