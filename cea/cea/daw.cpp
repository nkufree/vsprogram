#include<iostream>
using namespace std;

int main()
{
	int arr[5000] = {};
	int n=0, m=0, H=0, l=0, r=0, h=0, opt=0;
	cin >> n >> m >> H;
	for (int i = 0; i < n; i++)
		arr[i] = H;
	for (int i = 0; i < m; i++)
	{
		cin >> opt;
		if (opt == 1)
		{
			int sum = 0;
			cin >> l >> r;
			for (int j = l; j <= r; j++)
				sum += arr[j];
			cout << sum << endl;
		}
		else
		{
			cin >> l >> r >> h;
			for (int j = l; j <= r; j++)
			{
				if(arr[j]>h)
					arr[j] = h;
			}
		}
	}

}