#include<iostream>
using namespace std;

int main()
{
	long l, r;
	cin >> l >> r;
	long long s = 0, d = 0;
	for (long a = l; a <= r; a++)
	{
		s = 0;
		long long f = a, i = 1;
		for (long long b = a; b <= r; b++)
		{
			if (b > f * a)
			{
				i++;
				f *= a;
			}
			s += i;
		}
		d += a * s;
		d %= 998244353;
	}
	cout << d;
}