#include<iostream>
using namespace std;

int main()
{
	int sum = 0, a, b, c, d, e, f, n;
	cin >> a >> b >> c >> d >> e >> f >> n;
	if (a > d && b > e && c > f && d >= 0 && e >= 0 && f >= 0)
	{
		for (int i = d; i <= n; i += a)
		{
			if (i % b == e && i % c == f)
			{
				sum++;
				if (sum == 1)
					cout << i;
				else
					cout << " " << i;
			}
		}
		if (sum == 0)
			cout << "No solution!" << endl;
	}
	else
		cout << "Incorrect input!" << endl;
	return 0;
}