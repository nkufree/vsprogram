#include<iostream>
using namespace std;

void select_sort(int a[50],int m)
{
	for (int i = 0; i < m - 1; i++)
	{
		int* p = &a[i];
		for (int j = i+1; j < m; j++)
		{
			if (a[j] < *p)
				p = &a[j];
		}
		int temp = a[i];
		a[i] = *p;
		*p = temp;
		cout << a[0];
		for (int j = 1; j < m; j++)
			cout << " " << a[j];
		cout << endl;
	}
}

double Median(int a[50],int m)
{
	if (m % 2 == 0)
		return (a[m / 2] + a[m / 2 - 1]) / 2.0;
	else
		return a[(m - 1) / 2]/1;
}

int main()
{
	int a[50] = {};
	int m;
	cin >> m;
	for (int i = 0; i < m; i++)
		cin >> a[i];
	select_sort(a, m);
	cout <<Median(a, m);
}