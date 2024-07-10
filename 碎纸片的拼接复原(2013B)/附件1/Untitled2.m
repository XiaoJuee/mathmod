d =cell(1,19);
for i = 1:19
    imageName=strcat(num2str(i-1,'%03d'),'.bmp');
    d{i}=imread(imageName);
end
%ansd = [d{9},d{15},d{13},d{16},d{4},d{11},d{3},d{17},d{2},d{5},d{6},d{10},d{14},d{19},d{12},d{8},d{18},d{7}];
ansd = [d{9},d{15},d{13},d{16},d{4},d{11},d{3},d{17},d{2},d{5},d{6},d{10},d{14},d{19},d{12},d{8},d{18},d{1},d{7}];
imshow(ansd);
imwrite(ansd,'result.bmp');