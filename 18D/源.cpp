#include <iostream>
#include <algorithm>
using namespace std;

int arr[5000000]{};

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	sort(arr, arr + n);
	if (n < 3)
	{
		cout << 0;
		return 0;
	}
	int num = 0;
	int* p1 = &arr[0];
	int* p2 = &arr[n - 2];
	int* p3 = &arr[n - 1];
	while (p3 != p2 && p1 != p2)
	{
		if (*p1 + *p2 == *p3)
		{
			num++;
			if (*(p1 + 1) == *p1)
			{
				p1++;
			}
			else if (*(p2 - 1) == *p2)
			{
				p2--;
			}
			else
			{
				p3--;
				p2 = p3 - 1;
				p1 = arr;
			}
		}
		else if(*p1 + *p2 > *p3)
		{
			while (*p1 != *p2)
			{
				p2--;
				if (*p1 + *p2 < *p3)
				{
					p1 = p3 - 1;
					break;
				}
				else if (*p1 + *p2 == *p3)
				{
					break;
				}
			}
		}
		else if (*p1 + *p2 < *p3)
		{
			while (*p1 != *p2)
			{
				p1++;
				if (*p1 + *p2 > *p3)
				{
					p1 = arr;
					p2--;
					break;
				}
				else if (*p1 + *p2 == *p3)
				{
					break;
				}
			}
		}
	}
	cout << (num << 1);
	return 0;
}