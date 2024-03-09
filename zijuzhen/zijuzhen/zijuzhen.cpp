#include<iostream>
using namespace std;

int main()
{
	int m, n, a, b, c, d, q, sum[100][2] = {};
	int array[10][10];
	cin >> m >> n;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			cin >> array[i][j];
	}
	cin >> q;

	for (int k = 0; k < q; k++)
	{
		cin >> a >> b >> c >> d;
		for (int i = a - 1; i < c; i++)
		{
			for (int j = b - 1; j < d; j++)
				sum[k][0] += array[i][j];
		}
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (i >= (a - 1) && i < c && j >= (b - 1) && j < d)
					;
				else
				{
					if(sum[k][1]<array[i][j])
						sum[k][1] = array[i][j];
				}

			}
		}
	}
	for (int i = 0; i < q; i++)
		cout << sum[i][0] << " " << sum[i][1] << endl;
	return 0;
}