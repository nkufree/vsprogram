#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

#define MAXSIZE 10000
#define BUBBLE 0
#define QUICK 1
#define INSERT 2
#define SELECT 3
#define SHELL 4
using namespace std;
long cmpNum[5] = {};
long exNum[5] = {};
long digui = 0;
int arr[MAXSIZE] = {};

void bubbleSort(int arr[])
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		for (int j = 0; j < MAXSIZE - i + 1; j++)
		{
			cmpNum[0]++;
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				exNum[0]++;
			}
		}
	}
}

void quickSort(int arr[], int left, int right)
{
	digui++;
	if (NULL == arr)
	{
		return;
	}

	if (left < right)
	{
		int pivot = arr[left];
		int low = left, high = right;
		while (low < high)
		{
			while (arr[high] >= pivot && low < high)
			{
				high--;
				cmpNum[1]++;
			}
			arr[low] = arr[high];

			while (arr[low] <= pivot && low < high)
			{
				low++;
				cmpNum[1]++;
			}
			arr[high] = arr[low];
			exNum[1]++;
		}
		arr[low] = pivot;

		quickSort(arr, left, low - 1);
		quickSort(arr, low + 1, right);
	}
}

void insertSort(int* a, int len)
{
	for (int j = 1; j < len; j++)
	{
		int key = a[j];
		int i = j - 1;
		while (i >= 0 && a[i] > key)
		{
			a[i + 1] = a[i];
			i--;
			cmpNum[2]++;
		}
		a[i + 1] = key;
		exNum[2]++;
	}
}

void selectSort(int arr[], int n) {

	for (int i = 0; i < n; i++) {
		// 寻找[i, n)区间里的最小值
		int minIndex = i;
		for (int j = i + 1; j < n; j++)
		{
			cmpNum[3]++;
			if (arr[j] < arr[minIndex])
				minIndex = j;
		}
		int temp = arr[i];
		arr[i] = arr[minIndex];
		arr[minIndex] = temp;
		exNum[3]++;
	}
}

void shellSort(int a[], int n)  //a -- 待排序的数组, n -- 数组的长度
{
	int i, j, gap;   // gap为步长，每次减为原来的一半。
	for (gap = n / 2; gap > 0; gap /= 2)
	{
		// 共gap个组，对每一组都执行直接插入排序
		for (i = 0; i < gap; i++)
		{
			for (j = i + gap; j < n; j += gap)
			{
				cmpNum[4]++;
				// 如果a[j] < a[j-gap]，则寻找a[j]位置，并将后面数据的位置都后移。
				if (a[j] < a[j - gap])
				{
					int tmp = a[j];
					int k = j - gap;
					while (k >= 0 && a[k] > tmp)
					{
						a[k + gap] = a[k];
						k -= gap;
					}
					a[k + gap] = tmp;
					exNum[4]++;
				}
			}
		}
	}
}

int main()
{

	ifstream num_in("input.txt");
	for (int i = 0; i < MAXSIZE; i++)
	{
		num_in >> arr[i];
	}
	num_in.close();
	bubbleSort(arr);
	cout << "冒泡排序" << setw(10) << cmpNum[0] << setw(10) << exNum[0] << endl;
	for (int i = 0; i < 100; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	cout << endl;
	num_in.open("input.txt");
	for (int i = 0; i < MAXSIZE; i++)
	{
		num_in >> arr[i];
	}
	num_in.close();
	quickSort(arr, 0, MAXSIZE - 1);
	cout << "快速排序" << setw(10) << cmpNum[1] << setw(10) << exNum[1] << endl;

	for (int i = 0; i < 100; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	cout << endl;

	num_in.open("input.txt");
	for (int i = 0; i < MAXSIZE; i++)
	{
		num_in >> arr[i];
	}
	num_in.close();
	insertSort(arr, MAXSIZE);
	cout << "插入排序" << setw(10) << cmpNum[2] << setw(10) << exNum[2] << endl;

	for (int i = 0; i < 100; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	cout << endl;

	num_in.open("input.txt");
	for (int i = 0; i < MAXSIZE; i++)
	{
		num_in >> arr[i];
	}
	num_in.close();
	selectSort(arr, MAXSIZE);
	cout << "选择排序" << setw(10) << cmpNum[3] << setw(10) << exNum[3] << endl;

	for (int i = 0; i < 100; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	cout << endl;

	num_in.open("input.txt");
	for (int i = 0; i < MAXSIZE; i++)
	{
		num_in >> arr[i];
	}
	num_in.close();
	shellSort(arr, MAXSIZE);
	cout << "希尔排序" << setw(10) << cmpNum[4] << setw(10) << exNum[4] << endl;

	for (int i = 0; i < 100; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	cout << endl;

	cout << "递归" << digui << endl;
	return 0;
}