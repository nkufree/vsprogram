#include<iostream>
using namespace std;

int main()
{
	int num[100][51];
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 51; j++)
			num[i][j] = -1;
	}
	int n;
	cin >> n;
	for (int k = 0; k < n; k++)
	{
		char a[100] = {};
		cin >> a;
		int length;
		for (length = 0; a[length] != '\0'; length++)
		{
			if (a[length] == '5' || a[length] >= 'A')
				a[length] = ' ';
		}
		for (int i =0; i < length; i++)
		{
			int sum = 0;
			if (a[i] >= '0' && a[i] <= '9')
			{
				int x = 0;
				while (a[i]!='\0' && a[i] != ' ')
				{
					x *= 10;
					x += a[i++] - '0';
				}
				num[k][sum] = x;
				sum++;
			}
			for (int m = 0; m < sum; m++)
			{
				for (int j = sum - 1; j > m; j--)
				{
					if (num[k][j] < num[k][j - 1])
					{
						int temp = num[k][j];
						num[k][j] = num[k][j - 1];
						num[k][j - 1] = temp;
					}
				}
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		cout << num[i][0];
		for (int j = 1; num[i][j] != -1; j++)
		{ 
			if(num[i][j]!=num[i][j-1])
				cout << " " << num[i][j];
		}
	}
}