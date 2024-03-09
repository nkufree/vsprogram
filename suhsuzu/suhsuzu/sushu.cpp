#include<iostream>
using namespace std;

bool sushu(int n)
{
	for (int i = 2; i <= n ; i++)
	{
		if (n % i == 0 || n <= 1)
			return 0;
	}
	return 1;
}

int main()
{
	int n,m;
	int array[11] = {};
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> array[i];
		if (sushu(array[i]) == 0)
			array[i] = 0;
	}
	cin >> m;
	if (sushu(m) != 0)
		array[n] = m;
	for (int i = 0; i <= n; i++)
	{
		for (int j = n; j > i; j--)
		{
			if (array[j] > array[j - 1])
			{
				int temp = array[j];
				array[j] = array[j-1];
				array[j-1] = temp;
			}
		}
	}
	for (int i = n; i > -1; i--)
	{
		if (array[i] != 0)
		{
			cout << array[i];
			if (i != 0)
				cout << " ";
		}
	}
	return 0;
}