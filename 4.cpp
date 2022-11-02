#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <utility>

using namespace std;

typedef struct 
{
	int u; //始点
	int v; //终点
	int w; //边的权值
} Edge; //有向图表示边的结构体

typedef struct
{
	int next; //指向下一层中离汇点最近的结点，方便回溯
	int v = 0x0ff; //边的最短权值
} Node; //表示结点的结构体

int main()
{
	int cnt;
	cout << "多段图层数 = ";
	cin >> cnt;

	vector<vector<Edge> > edges(cnt, vector<Edge>()); //存放图中的边
	vector<unordered_set<int> > nodes(cnt + 1, unordered_set<int>()); //存放图中的结点，按层存储
	nodes[0].insert(0);

	for (int i = 1; i <= cnt; i++)
	{
		cout << "第" << i << "层，前驱节点：";
		for (auto j : nodes[i - 1])
			cout << j << ' ';
		cout << endl;
		cout << "请依次输入源点 目标点 权值，0 0 0结束" << endl;
		int a, b, c;
		cin >> a >> b >> c; //读入每条边的始点、终点、边权
		while (a || b || c)
		{
			if (nodes[i - 1].find(a) != nodes[i - 1].end()) //检查读入的始点是否是上一层的结点
			{
				edges[i - 1].push_back(Edge({a, b, c}));
				nodes[i].insert(b);
			}
			cin >> a >> b >> c;
		}
	}

	int s = 0; //源点
	int t = *nodes[cnt].begin(); //汇点
	vector<Node> dis(t + 1); //各结点到汇点的最短距离
	dis[t].v = 0;
	for (auto i = edges.rbegin(); i != edges.rend(); i++)
	{
		for (auto j : *i)
		{
			if (dis[j.v].v + j.w < dis[j.u].v) //松弛操作
			{
				dis[j.u].v = dis[j.v].v + j.w;
				dis[j.u].next = j.v;
			}
		}
	}
	cout << "最短距离：" << dis[0].v << endl;
	cout << "路径：" << 0;
	int node = 0;
	while (node != t) //迭代输出最短路径
	{
		node = dis[node].next;
		cout << "->" << node;
	}
	cout << endl;
	return 0;
}