某露天矿有铲位10个，卸点5个，现有铲车7台，卡车20辆。各卸点一个班次的产量要求：矿石漏1.2万吨、倒装场Ⅰ1.3万吨、倒装场Ⅱ1.3万吨、岩石漏1.9万吨、岩场1.3万吨。

设某露天矿有铲位$cw$，卸点$sd$，现有铲车$cc$，卡车$ck$。
各卸点一个班次的产量要求：矿石漏$kl$万吨、第$i$个倒装场$d_i$万吨、岩石漏$yl$万吨、岩场$yc$万吨。

$t = s/v$

各铲位和各卸点之间的距离为$s_{ij}$ , 根据$t = {s/}{v}$得到各铲位和各卸点之间的路程时间$t_{ij}$

各铲位矿石、岩石数量(万吨)和矿石的平均铁含量为$ks_i,ys_i,te_i$万吨

已知:
1.卡车载重量为154吨
2.平均时速$v=28 km/h$
3.每个铲位的矿石含铁量$te_i$

要求

设$x_{ijk}$为从第i个点到第j个点第$k$俩卡车运输矿石次数
设$y_{ijk}$为从第i个点到第j个点第$k$俩卡车运输岩石次数
$\min{ \displaystyle\sum_{k=ck_1}^{ck_n} (\displaystyle\sum_{i=cw_1}^{cw_n} \displaystyle\sum_{j=sd_1}^{sd_n}  (x_{ijk}+y_{ijk})*d_{ij}) }$




要满足要求
1.满足每个**矿石卸点**都有各自的产量要求
设矿石漏位第一个卸点，岩石漏第二个卸点、岩场第三个卸点，第$i$个倒装场为第$i+3$个卸点。

$\begin{cases}
kl \le \displaystyle\sum_{k=ck_1}^{ck_n} \displaystyle\sum_{i=cw_1}^{cw_n} x_{i1k}\\
yl \le \displaystyle\sum_{k=ck_1}^{ck_n} \displaystyle\sum_{i=cw_1}^{cw_n} x_{i2k} \\
yc \le \displaystyle\sum_{k=ck_1}^{ck_n} \displaystyle\sum_{i=cw_1}^{cw_n} x_{i3k} \\
sd_j \le \displaystyle\sum_{k=ck_1}^{ck_n} \displaystyle\sum_{i=cw_1}^{cw_n} x_{i,sd_j,k} 
\end{cases}$

总结就是
$sd_j*10000 \le 154\displaystyle\sum_{k=ck_1}^{ck_n} \displaystyle\sum_{i=cw_1}^{cw_n} x_{i,sd_j,k}$

2.品位限制,尽量把矿石按**矿石卸点**需要的铁含量搭配起来送到卸点（假设要求都为29.5 +- 1%)
第i个铲位到第j个卸点

$28.5\% \le \frac{\displaystyle\sum_{k=ck_1}^{ck_n} \displaystyle\sum_{i=cw_1}^{cw_n} 154x_{ijk}*te_i }{\displaystyle\sum_{k=ck_1}^{ck_n} \displaystyle\sum_{i=cw_1}^{cw_n} 154x_{ijk}}\le 30.5\%$


3.有铲车的地方才能挖矿,并且一个班次内铲车位置不变
设0/1变量$f_i$表示该铲位是否有铲车
$\displaystyle\sum_{j=sd_1}^{sd_n} (x_{ijk}+y_{ijk}) \le f_i , i = 1,2 ... ,cw$
$\displaystyle\sum_{i=cw_1}^{cw_n} f_i\le cc$

4.时间，在一个班次（8小时）内
卡车的平均卸车时间为3分钟，电铲的平均装车时间为5分钟
$  \displaystyle\sum_{i=1}^{n} \displaystyle\sum_{j=1}^{n} ((x_{ijk}+y_{ijk})*t_{ij}+3+5) \le 8*60 ,k = 1,2...ck$

5.卡车路线得连续
$\displaystyle\sum_{i=1}^{n} (x_{ijk}+y_{ijk}) \ge \displaystyle\sum_{l=1}^{n} (x_{jlk}+y_{jlk}),k = 1,2...ck$

6.铲位的卡车上限(时间上限)
$ \displaystyle\sum_{k=1}^{ck_n} (x_{ijk}+y_{ijk})*5 \le 8*60 , i = cw_1 , cw_2 , ... cw_n$
注:$i$为卡车装好车了出去
7.卸点的时间上限
$ \displaystyle\sum_{k=1}^{ck_n} (x_{ijk}+y_{ijk})*3 \le 8*60 , j = sd_1 , sd_2 , ... sd_n$
注:$j$为卡车卸车了出去 

8.铲位的产能
$\begin{cases} \displaystyle\sum_{k=ck_1}^{ck_n} \displaystyle\sum_{j=矿石卸点_1}^{矿石卸点_n} 154x_{ijk} \le {ks_i}*{10000}\\
\displaystyle\sum_{k=ck_1}^{ck_n} \displaystyle\sum_{j=岩石卸点_1}^{岩石卸点_n} 154y_{ijk} \le {ys_i}*{10000}
\end{cases}$