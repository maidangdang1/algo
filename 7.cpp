// https://www.luogu.com.cn/problem/P1048
/*
输入格式
第一行有 2 个整数 T（1≤T≤1000）和 M（1≤M≤100），用一个空格隔开，T 代表总共能够用来采药的时间，M 代表山洞里的草药的数目。

接下来的 M 行每行包括两个在 1 到 100 之间（包括 1 和 100）的整数，分别表示采摘某株草药的时间和这株草药的价值。

输出格式
输出在规定的时间内可以采到的草药的最大总价值。

【数据范围】

对于 30% 的数据，M≤10；
对于全部的数据，M≤100。

*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef struct Status
{
	int curWeight; // 目前的重量
	int curValue; // 目前的价值
	int curChooseIndex; // 现在需要抉择的物品序号
	double ratio; // 该状态的价值率

	friend bool operator<(const Status &x, const Status &y) // 用于优先队列的排序，价值率高的节点优先级高
	{
		return x.ratio < y.ratio;
	}

	Status(int w, int v, int index) : curWeight(w), curValue(v), curChooseIndex(index)
	{
		if (curValue == 0) // 防止0÷0的情况发生
			ratio = 0;
		else
			ratio = curValue * 1.0 / curWeight;
	}

	Status() = default;

	~Status() = default;

} Status;

int main()
{
	priority_queue<Status, vector<Status>> pq; // 优先队列初始化
	int w[100], v[100];
	int t, m;
	int maxValue = 0;
	cin >> t >> m;
	for (int i = 0; i < m; i++)
		cin >> w[i] >> v[i];
	pq.push(Status(0, 0, 0)); // 插入初始状态
	while (!pq.empty())
	{
		auto status = pq.top(); // 获取优先级最高的状态
		pq.pop();
		if (status.curChooseIndex == m) // 已经到达叶节点
		{
			if (status.curValue > maxValue)
				maxValue = status.curValue;
		}
		else
		{
			if (status.curWeight + w[status.curChooseIndex] <= t) // 还有容量可以装载
				pq.push(Status(status.curWeight + w[status.curChooseIndex], status.curValue + v[status.curChooseIndex], status.curChooseIndex + 1));
			pq.push(Status(status.curWeight, status.curValue, status.curChooseIndex + 1)); // 没有容量装载
		}
	}
	cout << maxValue << endl;
	return 0;
}
