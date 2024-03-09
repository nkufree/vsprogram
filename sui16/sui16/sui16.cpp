#include<iostream>
using namespace std;
char arr[20][17] = {}, s[16] = {};
int length;
void fl(int a, int b)
{
	for (int i = b; i < length; i++)
		arr[a][i - b] = s[i];
	for (int i = 0; i < b; i++)
		arr[a][length - b + i] = s[i];
}
void fr(int a, int b)
{
	for (int i = length - b; i < length; i++)
		arr[a][i - length + b] = s[i];
	for (int i = 0; i < length - b; i++)
		arr[a][i + b] = s[i];
}

int main()
{
	char b;
	int n,c;

	cin >> n;
	for(int i=0;i<n;i++)
	{
		cin >> s>>b>>c;
		for (length = 0; s[length] != '\0'; length++);
		c %= length;
		if (b == 'L')
			fl(i, c);
		else if (b == 'R')
			fr(i, c);
		else
		{
			for (int j = 0; j < length; j++)
				arr[i][j] = s[j];
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; arr[i][j] != '\0'; j += 2)
			cout << arr[i][j];
		cout << endl;
	}
}