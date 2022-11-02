#include <iostream>
#include <memory>

using namespace std;

int* lowerBound(int* start, int* end, int target)
{
	if (start >= end) //此时start和end之间已无区域，返回start
		return start;
	int* mid = start + (end - start) / 2;
	if (target <= *mid)
		return lowerBound(start, mid, target); //递归处理左半边
	else
		return lowerBound(mid + 1, end, target); //递归处理右半边
}

int binarySearch(int* start, int* end, int target) //返回第一个出现target的位置，或-1
{
	int* index = lowerBound(start, end, target); //在序列中找第一个不小于target的位置
	if (index == end || *index != target) //校验该位置是否和target相等或越界
		return -1;
	else
		return index - start;
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
		int index = binarySearch(arr, arr + cnt, target); //在[arr, arr + cnt)中寻找target
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