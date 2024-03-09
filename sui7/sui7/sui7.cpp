#include<iostream>
using namespace std;

char a[20][10] = {};
int b[20] = {};
void swapstr(int j, int k)
{
	char temp[10];
	for (int i = 0; i < 10; i++)
		temp[i] = a[j][i];
	for (int i = 0; i < 10; i++)
		a[j][i] = a[j - 1][i];
	for (int i = 0; i < 10; i++)
		a[j - 1][i] = temp[i];
}

void swap(int i, int j)
{
	int temp = b[i];
	b[i] = b[j];
	b[j] = temp;
}

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i] >> b[i];
	for (int i = 0; i < n; i++)
	{
		for (int j = n - 1; j > i; j--)
		{
			if (b[j] > b[j - 1])
			{
				swapstr(j, j - 1);
				swap(j, j - 1);
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		int j = 0;
		while (a[i][j] != '\0')
			cout << a[i][j++];
		cout << endl;
	}
	return 0;
}