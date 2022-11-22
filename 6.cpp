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

using namespace std;

int t = 0, m = 0, total = 0, maxi = 0; // 记录当前值和最大值
int w[100] = {0}; // 每种草药的时间
int v[100] = {0}; // 每种草药的价值

void dfs(int floor)
{
	if (floor == m) // 代表已经对每一种草药都遍历完成
	{
		if (total > maxi)
			maxi = total; // 将最大值替换为当前值
		return;
	}
	if (t >= w[floor]) // 代表还有足够的时间采集草药
	{
		t -= w[floor];
		total += v[floor]; // 采集草药

		dfs(floor + 1); // 往下迭代

		total -= v[floor];
		t += w[floor]; // 复原没有采集的状态
	}
	dfs(floor + 1); // 假设不采集当前草药，往下迭代
}

int main()
{
	cin >> t >> m;
	for (int i = 0; i < m; i++)
		cin >> w[i] >> v[i];
	dfs(0);
	cout << maxi << endl;
	return 0;
}
