#include<iostream>
using namespace std;

bool f(char p)
{
	if ((p >= 'A' && p <= 'Z') || (p >= '0' && p <= '9') || (p >= 'a' && p <= 'z'))
		return 1;
	else
		return 0;
}

int main()
{
	int length = 0;
	char b[200] = {};
	char a[200] = {};
	cin.getline(b,200);
	for (int i = 0; b[i] != '\0'; i++) 
	{
		if (f(b[i]) == 1)
		{
			a[length++] = b[i];
		}
	}
	int j = length - 1;
	for (int i = 0; i < j; i++,j--)
	{
		if (a[i] != a[j])
		{
			cout << "False";
			return 0;
		}
	}
	cout << "True";
	return 1;
}