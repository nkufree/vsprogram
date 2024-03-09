#include<iostream>
using namespace std;

int main()
{
	int n,sum=0;
	long long num=1;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		num *= i;
		if (num % 10 == 0)
		{
			num /= 10;
			sum++;
		}
	}
	while (num != 0)
	{
		if (num % 10 == 0)
			sum++;
		num /= 10;
	}
	cout << sum;
}