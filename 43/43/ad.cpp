#include<iostream>
using namespace std;
int ma[10][10];


int main()
{
	int m=0, n = 0;
	cin >> m>> n;
	int r = m, c = n;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			cin >> ma[i][j];
	}
	if (m == 1)
	{
		cout << ma[0][0];
		for (int i = 1; i < n; i++)
			cout <<" " << ma[0][i];
		cout << endl;
		cout << ma[0][0];
		for (int i = 1; i < n; i++)
			cout << " " << ma[0][i];
		return 0;
	}
	if (n == 1)
	{
		cout << ma[0][0];
		for (int i = 1; i < m; i++)
			cout << " " << ma[i][0];
		cout << endl;
		cout << ma[0][0];
		for (int i = 1; i < m; i++)
			cout << " " << ma[i][0];
		return 0;
	}
	for (int i = 0; i < m; i++)
	{
		if (i == 0)
		{
			cout << ma[0][0];
			for (int j = 1; j < n; j++)
				cout << " " << ma[i][j];
		}
		else if (i % 2 == 0)
		{
			for (int j = 0; j < n; j++)
				cout <<" "<< ma[i][j];
		}
		else
		{
			for (int j = n - 1; j > -1; j--)
				cout <<" "<< ma[i][j];
		}
	}
	cout <<endl;
	int k;
	for (k = 0;r>1&&c>1; k++)
	{
		int i;
		if (k == 0)
		{
			cout << ma[0][0];
			i = k+1;
			while (i < n - k)
			{
				cout << " " << ma[k][i++];
			}
		}
		else
		{
			i = k;
			while (i < n - k)
			{
				cout << " " << ma[k][i++];
			}
		}
		i = k + 1;
		while (i < m - k)
		{
			cout << " " << ma[i++][n - k - 1];
		}
		i = n - k - 2;
		while (i >= k)
		{
			cout <<" " << ma[m - k - 1][i--];
		}
		i = m - k - 2;
		while (i > k)
		{
			cout <<" " << ma[i--][k];
		}
		r -= 2;
		c -= 2;
	}
	if (r == 1)
	{
		for (int i = k;i<n-k; i++)
			cout <<" "<< ma[k][i];
	}
	else if (c == 1)
	{
		for (int i = k; i < m - k; i++)
			cout <<" "<< ma[i][k];
	}
	return 0;
}