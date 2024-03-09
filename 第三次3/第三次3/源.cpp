#include<iostream>
using namespace std;
char** p = NULL;
bool f(int i, int j)
{
	int k;
	for (k = 0; *(*(p + i) + k) != '\0' && *(*(p + j) + k) != '\0'; k++)
	{
		if (*(*(p + i) + k) != *(*(p + j) + k))
			return *(*(p + i) + k) < *(*(p + j) + k);
	}
	return *(*(p + i) + k) != '\0';
}

int main()
{
	int n;
	cin >> n;
	p = new char* [n];
	for (int i = 0; i < n; i++)
	{ 
		*(p + i) = new char[100];
		cin >> *(p + i);
	}
	int* pc = new int[n];
	for (int i = 0; i < n; i++)
		*(pc + i) = i + 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = n - 1; j > i; j--)
		{
			if (f(j, j - 1) == 1)
			{
				char* temp1 = *(p + j);
				*(p + j) = *(p + j - 1);
				*(p + j - 1) = temp1;
				int temp2 = *(pc + j);
				*(pc + j) = *(pc + j - 1);
				*(pc + j - 1) = temp2;
			}
		}
	}
	for (int i = 0; i < n - 1; i++)
		cout << *(pc + i) << " ";
	cout << *(pc + n - 1);
	delete pc;
	delete[] p;
}