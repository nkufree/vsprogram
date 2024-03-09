#include<iostream>
#include<cmath>
using namespace std;

int main()
{
	int N;
	cin >> N;
	int r[1001] = {};
	for (int i = 1; i <= N; i++)
	{
		int A = 0, B = 0, sum=0;
		cin >> A >> B;
		for (int j = A; j <= B; j++)
		{
			int C = j , a = 0;
			while (C != 0)
			{
				C /= 10;
				a++;
			}
			int array[5] = {};
			for(int k=1;k<a;k++)
			{
				C = j;
				C = (C % static_cast<int>(pow(10,k)))* static_cast<int>(pow(10,a-k)) + C / static_cast<int>(pow(10,k));
				if (C > j && C <= B)
				{
					sum++;
					array[k] = C;
				}
			}
			for (int k = 0; k <= a - 1; k++)
			{
				for (int p = k+1; p <= a - 1; p++)
					if (array[p] == array[k] && array[p] != 0)
					{
						sum--;
						array[p] = 0;
					}
			}
		}
		r[i-1] = sum;
	}
	for (int k = 0; k <= N-1; k++)
		cout << r[k] << endl;
	return 0;
}