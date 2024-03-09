#include<iostream>
using namespace std;

int main()
{
	int m, n;
	float ma[10][10] = {};
	cin >> m >> n;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			cin >> ma[i][j];
	}
	int i, j;
	cin >> i >> j;
	if (i < 0 || i >= m || j < 0 || j >= n)
	{
		cout << "WRONG INPUT!";
		return 0;
	}
	float a[4][2] = {};
	for (int k = 0; k < m; k++)
	{
		for (int l = 0; l < n; l++)
		{
			if (k <= i && l <= j)
			{
				a[0][0] += ma[k][l];
				a[0][1]++;
			}
			else if (k > i && l <= j)
			{
				a[1][0] += ma[k][l];
				a[1][1]++;
			}
			else if (k <= i && l > j)
			{
				a[3][0] += ma[k][l];
				a[3][1]++;
			}
			else
			{
				a[4][0] += ma[k][l];
				a[4][1]++;
			}
		}
	}
	float max = a[0][0] / a[0][1];
	for (int k = 1; k < 4; k++)
	{
		if (a[k][1] != 0)
		{
			if (a[k][0] / a[k][1] > max)
				max = a[k][0] / a[k][1];
		}
	}
	cout << max;
	return 0;
}