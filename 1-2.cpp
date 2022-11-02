#include <iostream>
#include <memory>

using namespace std;

void quickSort(int* start, int* end)
{
	int* l = start;
	int* r = end;
	int mid = *(start + (end - start) / 2); //取中点为比较点
	while (l <= r)
	{
		while (*r > mid)
			r--;
		while(*l < mid)
			l++;
		if(l <= r)
		{
			swap(*l, *r); //将不符合次序的两个数交换
			r--;
			l++;
		}
	}
	if(l < end)
		quickSort(l, end); //递归处理右半边
	if(r > start)
		quickSort(start, r); //递归处理左半边
}
int main()
{
	int cnt;
	cout << "How many numbers:";
	cin >> cnt;
	
	int* arr = new int[cnt * sizeof(cnt)];
	cout << "Input numbers:";
	for (int i = 0; i < cnt; i++)
		cin >> arr[i];

	quickSort(arr, arr + cnt - 1); //对[arr, arr + cnt - 1]排序

	for (int i = 0; i < cnt; i++)
		cout << arr[i] << " ";
	delete[] arr;
	return 0;
}
