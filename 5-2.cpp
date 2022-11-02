/*
输入格式
第一行包含两个整数 N,M，表示该图共有 N 个结点和 M 条无向边。

接下来 M 行每行包含三个整数 X_i,Y_i,Z_i，表示有一条长度为 Z_i 的无向边连接结点 X_i,Y_i。

输出格式
如果该图连通，则输出一个整数表示最小生成树的各边的长度之和。

数据规模：

对于 20% 的数据，N≤5，M≤20。

对于 40% 的数据，N≤50，M≤2500。

对于 70% 的数据，N≤500，M≤10^4。

对于 100% 的数据：1≤N≤5000，1≤M≤2×10^5，1≤Z_i≤10^4。
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct Edge // 定义结构体，用来存边
{
	int u;
	int v;
	int w;

	Edge(int u, int v, int w): u(u), v(v), w(w) // 构造函数
	{
		;
	}

	Edge() = default;
} Edge;

typedef struct
{
	bool operator()(const Edge& x, const Edge& y) // 仿函数重载，用来给sort提供排序
	{
		return x.w < y.w;
	}
} comp;

int father[5010]; // 定义父节点数组，用于并查集

int find(int number) // 寻找父节点
{
	if (father[number] == number)
		return number;
	else
	{
		father[number] = find(father[number]); // 路径压缩
		return father[number];
	}
}

int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		father[i] = i; // 初始化父节点，令其指向自己
	vector<Edge> edges;
	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		edges.push_back(Edge(u, v, w));
	}
	sort(edges.begin(), edges.end(), comp()); // 对边权排序
	int k = 0, total = 0;
	for (int i = 0; i < m; i++)
	{
		if (k == n - 1) // 代表最小生成树已经构建完毕
			break;
		if (find(edges[i].u) != find(edges[i].v)) // 父节点不相同，代表它们所处的集合不同
		{
			father[find(edges[i].u)] = find(edges[i].v); // 两个集合合并
			total += edges[i].w;
			k++;
		}
	}
	if (k != n - 1)
		cout << "无法构成最小生成树" << endl;
	else
		cout << total << endl;
	return 0;
}