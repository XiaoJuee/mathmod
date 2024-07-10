# question1
## question1.1

建立租赁模型:
设有$x$张DVD，想看会员数为两万，满足度为$50\%$
有$a\%$个会员租赁两次，$(1-a)\%$个会员租赁一次
可得：$2x*a\% + x*(1-a)\% = 20000 * 0.5$
根据题目可知$a = 60$
解得$x = 6250$

将模型一般化，设统计中愿意观看的人数为$b$,满足度为$w$,则想看会员数为$b/1000*100000$
$x = \lceil(b/1000*100000  w)/(2*a\% + (1-a\%))\rceil$

| DVD名称| 	DVD1| 	DVD2	| DVD3| 	DVD4| 	DVD5| 
|--|--|--|--|--|--|
|愿意观看的人数|	200|	100|	50|	25|	10|
|需要准备张数|6250|3125|1563|782|313|

## question1.2  如果要求保证在三个月内至少95%的会员能够看到该DVD呢？

以下模型建立在租两次的会员月初租赁，月末还 ， 租一次的会员月初租，下月初还

建立会员重复模型：
设第$i$个月来的会员数为$y_i$个会员
每个月有$a\%$个会员租赁两次，$(1-a)\%$个会员租赁一次，$a = 60$
设会员重复率为$C\%$ , $C=50$
则其中$\min{(a\%y_{j}*C\%,a\%y_{i}*C\%)}$和是同一个会员
其中$\min{((1-a)\%y_{j}*C\%,(1-a)\%y_{i}*C\%)}$和是同一个会员

引入question1.1的模型 
设统计中愿意观看的人数为$b$,满足度为$w$,则想看会员数为$b/1000*100000$

设第$i$个月有$x$张DVD
有$a\%$个会员租赁两次，$(1-a)\%$个会员租赁一次
第$i$个月~~来的~~满足的会员数为$y_i$个会员
可得：$2*x_i*a\% + x_i*(1-a)\%= y_i$

来的会员总数减去重复会员数必须大于等于要满足的会员数
$\begin{cases}
   y_1+y_2+y_3 - \min{(a\%y_{2}*C\%,a\%y_{1}*C\%)} - \min{(a\%y_{3}*C\%,a\%y_{2}*C\%)} - \min{(a\%y_{1}*C\%,a\%y_{3}*C\%)} - \min{((1-a)\%y_{2}*C\%,(1-a)\%y_{1}*C\%)} - \min{((1-a)\%y_{3}*C\%,(1-a)\%y_{2}*C\%)} - \min{((1-a)\%y_{1}*C\%,(1-a)\%y_{3}*C\%)} \ge b/1000*100000*w \\
   2*x_i*a\% + x_i*(1-a)\%= y_i , i = 1,2,3
   \\
   ans = min{(x_1+x_2+x_3)}
\end{cases}$


# question2

设变量$x_{ij}$为租赁给第$i$个会员第$j$种DVD的情况，设定$x_{ij}=1$为租，$x_{ij}=0$为不租
如果有$n$个客户,$m$种DVD,客户在线订单数为$order_{ij}$
则单个会员满意量为$b_{ij} = \begin{cases} (11-order_{ij}) , order_{ij} \gt 0 \\
0,order_{ij}=0 
\end{cases}$
那么客户总满意~~度~~量:$\max ans = \sum_{1\le i \le n , 1\le j \le m}x_{ij} b_{ij}$

要保证DVD数量不能超标
设第$j$种DVD有$sum_j$个，**题目已知$sum_j$**
$\sum_{1\le i \le n}x_{ij} \le sum_j , j = 1,2,3....,m$

每个客户发3张不同的DVD或者不发DVD：
设0/1变量 $y_i$
$\sum_{ 1\le j \le m}x_{ij} = 3y_i ,i=1,2,3,..n $

需要保证每个人都不会收到自己不喜欢的DVD，即客户在线订单数为0时候，不可以租给他。
$x_{ij} \le order_{ij} ,i=1,2,3,..n , j= 1,2,3,..m$

LINGO求解：

```lingo
sets:
  aa/1..1000/:y;
  bb/1..100/:sum;
  cc(aa,bb):order,x,b;
endsets
data:
order = @ole('D:\homewrok\建模\DVD租赁\B2005Table2.xls','order');
sum = @ole('D:\homewrok\建模\DVD租赁\B2005Table2.xls','dvdsumj');
enddata

@for(cc(i,j):b(i,j)=@if(order(i,j)#gt#0,11-order(i,j),0));
max=@sum(cc(i,j):x(i,j)*b(i,j));
@for(bb(j):@sum(aa(i):x(i,j))<=sum(j));
@for(aa(i):@sum(bb(j):x(i,j))=y(i)*3);
@for(cc(i,j):x(i,j)<=order(i,j));
@for(cc(i,j):@bin(x(i,j)));
@for(aa(i):@bin(y(i)));
```
| 客户/DVD ID| 	第一张| 	第二张	| 第三张| 
|--|--|--|--|
|C0001|D008|D041|D098|
|C0002|D006|D044|D062|
|C0003|D032|D050|D080|
|C0004|D007|D018|D041|
|C0005|D011|D066|D068|
|C0006|D019|D053|D066|
|C0007|D026|D066|D081|
|C0009|D053|D078|D100|
|C0010|D041|D055|D085|
|C0011|D059|D063|D066|
|C0012|D002|D031|D041|
|C0013|D021|D078|D096|
|C0014|D023|D052|D089|
|C0015|D013|D052|D085|
|C0016|D010|D084|D097|
|C0017|D047|D051|D067|
|C0018|D041|D060|D078|
|C0019|D066|D084|D086|
|C0020|D045|D061|D089|
|C0021|D045|D050|D053|
|C0022|D038|D055|D057|
|C0023|D029|D041|D095|
|C0024|D037|D041|D076|
|C0025|D009|D069|D081|
|C0026|D022|D068|D095|
|C0027|D050|D058|D078|
|C0028|D008|D034|D082|
|C0029|D026|D030|D055|
|C0030|D037|D062|D098|


# question3
在满足第二问的模型下:注意:$sum_j$是变量(未知)

$\begin{cases}
b_{ij} = \begin{cases} (11-order_{ij}) , order_{ij} \gt 0 \\
0,order_{ij}=0 
\end{cases}\\
\max = \sum_{1\le i \le n , 1\le j \le m}x_{ij}  b_{ij}\\
\sum_{1\le i \le n}x_{ij} \le sum_j , j = 1,2,3....,m\\
\sum_{ 1\le j \le m}x_{ij} = 3y_i ,i=1,2,3,..n \\
x_{ij} \le order_{ij} ,i=1,2,3,..n , j= 1,2,3,..m
\end{cases}$

因为$sum_j$是变量,我们决定每种DVD的购买量,需要满足DVD总量不变,设已知总量为$num_{sum}$
$\sum_{1\le j \le m}sum_j = num_{sum}$

要使一个月内95%的会员得到他想看的DVD,按照第二问的限制下即发三张DVD就是满足该客户，否则不满足
$\sum_{1\le i \le n}y_i\ge  95\%n $

>再加上要使一个月内95%的会员得到他想看的DVD(**舍弃**)
$\sum_{1\le i \le n}(\sum_{1\le j \le m} (order_{ij}!=0) = \sum_{1\le j \le m}x_{ij}*(order_{ij}!=0))\ge n*95\%$

LINGO求解：
```lingo
sets:
  aa/1..1000/:y;
  bb/1..100/:sum,num;
  cc(aa,bb):order,x,b;
endsets
data:
order = @ole('D:\homewrok\建模\DVD租赁\B2005Table2.xls','order');
num = @ole('D:\homewrok\建模\DVD租赁\B2005Table2.xls','dvdsumj');
enddata

@for(cc(i,j):b(i,j)=@if(order(i,j)#gt#0,11-order(i,j),0));
max=@sum(cc(i,j):x(i,j)*b(i,j));
@for(bb(j):@sum(aa(i):x(i,j))<=sum(j));
@for(aa(i):@sum(bb(j):x(i,j))=y(i)*3);
@for(cc(i,j):x(i,j)<=order(i,j));
@sum(bb(j):sum(j))=@sum(bb(j):num(j));
@sum(aa(i):y(i))>=950;
@for(cc(i,j):@bin(x(i,j)));
@for(aa(i):@bin(y(i)));
```

