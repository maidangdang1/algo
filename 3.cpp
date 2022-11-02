#include <iostream>
#include <memory>

using namespace std;

int binarySearch(int arr[], int start, int end, int target)
{
	if (start > end) //越界时代表未找到，返回-1
		return -1;
	double rate = (target - arr[start]) * 1.0 / (arr[end] - arr[start]); //确定目标值在序列的位置
	int mid = start + int((end - start) * rate);
	if (arr[mid] == target)
		return mid;
	else if (arr[mid] < target)
		return binarySearch(arr, mid + 1, end, target); //递归处理右半边
	else
		return binarySearch(arr, start, mid - 1, target); //递归处理左半边
}

bool isSorted(int* start, int* end) //验证序列是否非降序
{
	for (int* i = start + 1; i < end; i++)
	{
		if (*(i - 1) > *i)
			return false;
	}
	return true;
}

int main()
{
	int cnt;
	cout << "How many numbers:";
	cin >> cnt;

	int* arr = new int[cnt * sizeof(int)];
	cout << "Input sorted numbers(from low to high):";
	for (int i = 0; i < cnt; i++)
		cin >> arr[i];

	if (isSorted(arr, arr + cnt)) //校验所输入的序列是否有序
	{
		int target;
		cout << "Input target:";
		cin >> target;
		int index = binarySearch(arr, 0, cnt - 1, target); //在[arr, arr + cnt)中寻找target
		if (index == -1)
			cout << "Cannot find target." << endl;
		else
			cout << "Index: " << index << endl;
	}
	else
		cout << "Array is not sorted." << endl;

	delete[] arr;
	return 0;
}