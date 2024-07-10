%problem 1
clear
clc 
M=600;N=600; 
t=20;d=4000;f=200;k=1500; 
sigma=196.6292;mu=600; 
for m=1:M 
    m
    for n=1:N 
        w1=t*(m/n)+k; 
        S=normcdf(m,mu,sigma); %刀具生产零件故障概率
        p1=1-S/0.95; 
        Ew1=w1*p1; 
        Ew2=0;Eq2=0; 
        for idx=1:m-1
            num=floor(idx/n)+1;
            w2=t*num+d+f*(n*num-idx); 
            p2=normpdf(idx+1,mu,sigma)/0.95; %刀具生产零件故障概率
            Ew2=Ew2+w2*p2;
            Eq2=Eq2+idx*p2; 
        end
        Ew=Ew1+Ew2;
        Eq1=m*p1;
        Eq=Eq1+Eq2; 
        E(m,n)=Ew/Eq;
    end
end
minE=min(min(E)) 
[minm,minn]=find(E==minE) 
