// 题目来源：https://www.luogu.com.cn/problem/P3366
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
#include <unordered_set>
#include <queue>
#include <vector>

using namespace std;

typedef struct Edge // 定义结构体，用于存边
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
	bool operator()(const Edge& x, const Edge& y) // 仿函数重载，用于优先队列中的比较
	{
		if (x.w == y.w)
			return x.u > y.u;
		return x.w > y.w;
	}
} comp;

int main()
{
	int n, m;
	cin >> n >> m;
	int total = 0;
	unordered_set<int> s; // 点的集合，查找只需O(1)复杂度
	priority_queue<Edge, vector<Edge>, comp> pq; // 优先队列，用于动态对边排序
	vector<vector<Edge> > edges(n + 1, vector<Edge>()); // 边的集合，用于存边
	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		cin >> u >> v >> w; // 读入边
		edges[u].push_back(Edge(u, v, w));
		edges[v].push_back(Edge(v, u, w)); // 由于是无向图，所以需要反向存边
	}
	cout << endl;
	s.insert(1); // 向集合中放入结点1作为起点
	for (auto i : edges[1])
		pq.push(i); // 向优先队列中放入结点1对应的边
	while (s.size() < n && !pq.empty())
	{
		auto edge = pq.top(); // 取出边权最小的一条边
		pq.pop();
		if (s.find(edge.v) == s.end()) // 如果边的终点不在集合内，代表这条边在最小生成树内
		{
			cout << edge.u << " " << edge.v << " " << edge.w << endl;
			s.insert(edge.v); // 将终点加入集合内，代表选中了这条边
			total += edge.w;
			for (auto i : edges[edge.v]) // 将终点对应的边也加入优先队列
				pq.push(i);
		}
	}
	if (s.size() != n)
		cout << "无法构成最小生成树" << endl;
	else
		cout << total << endl;
	return 0;
}
