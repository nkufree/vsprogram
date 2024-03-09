#include<iostream>
#include<iomanip>
using namespace std;

int array[25][81];
void yanghui(int n)
{
	::array[1][1] = ::array[2][1] = ::array[2][2] = 1;
	for (int i = 3; i <= n; i++)
	{
		for (int j = 1; j <= i; j++)
			:: array[i][j] = ::array[i - 1][j - 1] + ::array[i - 1][j];
	}
}

int main()
{
	int n;
	cin >> n;
	yanghui(n);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			cout << ::array[i][j];
			if (j != i)
				cout << " ";
		}
		cout << endl;
	}
	return 0;
}