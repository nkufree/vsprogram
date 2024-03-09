#include<iostream>
using namespace std;
char str[100] = {};

bool r(int m, int length)
{
	for (int i = m; i < m + length; i++)
	{
		for (int j = m; j < i; j++)
		{
			if (str[i] == str[j])
				return 1;
		}
	}
	return 0;
}

int main()
{
	cin.getline(str, 100);
	int length;
	for (length = 0; str[length] != '\0'; length++);
	int max;
	for (max = length; max >= 1; max--)
	{
		for (int j = 0; j <= length - max; j++)
		{
			if (r(j, max) == 0)
			{
				cout << max;
				return 0;
			}
		}
	}
}