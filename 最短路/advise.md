
为了方便叙述，这里先给出下文将会用到的一些记号的含义。
$n$为图上点的数目，$m$为图上边的数目，
$s$为最短路的源点;
$D(u)$为$s$点到$u$点的**实际**最短路长度;
$dis(u)$为$s$点到$u$点的**估计**最短路长度。任何时候都有$dis(u)>D(u)$。特别地，当最短路算法终止时，应有$dis(u)= D(u)$。
$w(u,u)$为$(u,v)$这一条边的边权。
# Floyd 算法
定义一个数组 $f[k][x][y]$，表示只允许经过结点 $1$ 到 $k$，结点 $x$ 到结点 $y$ 的最短路长度。

$f[0][x][y]$表示$x,y$的边权，当没有边连接时候为无穷大，当$x=y$时候等于0

为了求$f[k][x][y]$,首先我们有不经过节点$k$的最短路$f[k-1][x][y]$和经过$k$的最短路$f[k-1][x][k] + f[k-1][x][y]$

所以$f[k][x][y]$为上述两者取最小值，即为允许经过k的最短路

# Dijkstra 算法

将结点分成两个集合:已确定最短路长度的点集(记为$S$集合)的和未确定最短路长度的点集(记为 $T$ 集合)。一开始所有的点都属于 $T$ 集合,初始化 $dis(s)=0$，其他点的 $dis$ 均为 $+∞$。然后重复这些操作:
1.从 $T$ 集合中，选取一个最短路长度最小的结点，移到 $S$ 集合中。
2.对那些刚刚被加入 $S$ 集合的结点的所有出边执行松弛操作。
直到 $T$ 集合为空，算法结束。
对于边$(u,v)$，松弛操作对应下面的式子:$dis(v)= min(dis(v),dis(u)+ w(u,v))$。
# lingo求解起点到终点的最短路
假设图为无向图
已知两点(点$i,j$)间距离为$d_{ij}$,如果无边连接，$d_{ij}$为无穷大
设$x_{ij}=1$为选择两点(点$i,j$)的边为路径中的边，反之不选择
已知起点为$a$，终点为$b$.有$N$个节点
$\begin{cases}
\min \displaystyle\sum_{i=1}^N\displaystyle\sum_{j=1}^N d_{ij}x_{ij}\\
\displaystyle\sum_{i=1}^N x_{ib} = 2 \\ 
\displaystyle\sum_{i=1}^N x_{ai} = 2 \\ 
\displaystyle\sum_{i=1}^N x_{ij} \le \displaystyle\sum_{k=1}^N x_{jk}\\
x_{ij} \in \set{0,1}\\
i = 1,2,3...N , j =1,2,3...N , k = 1,2,3...N
\end{cases}$

```LINGO
sets:
 aa/1..6/:;
 cc(aa,aa):x,d;
endsets
data:
 d=@ole("graph.xls",A1:F6);
enddata
min=@sum(cc(i,j):d(i,j)*x(i,j));
@sum(aa(i):x(i,6))=2;
@sum(aa(i):x(1,i))=2;
@for(aa(j):@sum(aa(i):x(i,j))<@sum(aa(k):x(j,k)));
@for(cc(i,j):@bin(x(i,j)));
```