#include<iostream>
using namespace std;

int main()
{
	int a[45] = {};
	int num[20] = {};
	a[0] = 1;
	a[1] = 1;
	a[2] = 1;
	a[3] = 2;
	for (int i = 4; i < 44; i++)
		a[i] = a[i - 1] + a[i - 3];
	int n;
	cin >> n;
	if (n <= 0 || n >= 20)
	{
		cout << "WRONG!";
		return 0;
	}
	int m;
	for (int i = 0; i < n; i++)
	{
		cin >> m;
		if (m <= 0 || m >= 45)
			num[i] = -1;
		else
			num[i] = a[m - 1];
	}
	for (int i = 0; i < n; i++)
	{
		if (num[i] == -1)
			cout << "WRONG!" << endl;
		else
			cout << num[i] << endl;
	}
}