#include <iostream>
#include <memory>

using namespace std;

void bubbleSort(int* start, int* end)
{
	if (start == end) //start和end重合即没有数待排序
		return;
	for (int i = 0; i < end - start - 1; i++) //对end - start - 1个元素检查大小关系即可
	{
		if (*(start + i) > *(start + i + 1))
			swap(*(start + i), *(start + i + 1));
	}
	bubbleSort(start, end - 1);
}

int main()
{
	int cnt;
	cout << "How many numbers:";
	cin >> cnt; //输入待排序的数组大小
	
	int* arr = new int[cnt * sizeof(cnt)]; //动态开辟内存
	cout << "Input numbers:";
	for (int i = 0; i < cnt; i++)
		cin >> arr[i]; //输入待排序的数字

	bubbleSort(arr, arr + cnt); //对[arr, arr + cnt)排序

	for (int i = 0; i < cnt; i++)
		cout << arr[i] << " ";
	delete[] arr;
	return 0;
}
