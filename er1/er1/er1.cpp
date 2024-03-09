#include<iostream>
using namespace std;

int su[32767] = { 0 };
bool s(int a)
{
	for (int i = 2; i <= a / 2; i++)
	{
		if (a % i == 0)
			return 0;
	}
	return 1;
}


int main()
{
	int q[10];
	int n, a;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a;
		int sum = 0;
		for (int i = 3; i <= a / 2; i++)
		{
			if (s(i) == 1 && s(a - i) == 1)
				sum++;
		}
		q[i] = sum;
	}
	for (int i = 0; i < n; i++)
		cout << q[i] << endl;
}