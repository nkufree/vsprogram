#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
	int a[5][5], b[5][5], c[5][5];
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			cin >> a[i][j];
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			cin >> b[i][j];
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			int sum = 0;
			for (int k = 0; k < 5; k++)
				sum += a[i][k] * b[k][j];
			c[i][j] = sum;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			cout << setw(6)<<c[i][j];
		cout << endl;
	}
}