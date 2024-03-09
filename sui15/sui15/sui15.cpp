#include<iostream>
using namespace std;
char arr[20][17] = {}, s[16] = {};
int length = 0;
void reverse(int i)
{
	for (int j = length - 1; j > -1; j--)
		arr[i][length - 1 - j] = s[j];
}
void fi(int a, int b, char c)
{
	if(b < length)
	{
		for (int i = 0; i < b; i++)
			arr[a][i] = s[i];
		arr[a][b] = c;
		for (int i = b+1;i<=length+2 ; i++)
			arr[a][i] = s[i - 1];
	}
	else
	{
		for (int i = 0; i <= length; i++)
			arr[a][i] = s[i];
		arr[a][length] = c;
	}
}
void fd(int a, int b)
{
	for (int i = 0; i <= length; i++)
	{
		if (i != b - 1)
			arr[a][i] = s[i];
		else
			arr[a][i] = ' ';
	}
	if (b > length)
		reverse(a);
}
void fr(int a, int b, char c)
{
	for (int i = 0; i <= length; i++)
	{
		if (i != b - 1)
			arr[a][i] = s[i];
		else
			arr[a][i] = c;
	}
	if (b > length)
		reverse(a);
}


int main()
{
	char a, c;
	int b, n;
	cin >> s >> n;
	for (length = 0; s[length] != '\0'; length++);
	for (int i = 0; i < n; i++)
	{
		cin >> a >> b;
		if (a != 'd')
			cin >> c;
		if (a == 'i')
			fi(i, b, c);
		else if (a == 'd')
			fd(i, b);
		else if (a == 'r')
			fr(i, b, c);
		else
			reverse(i);
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; arr[i][j] != '\0'; j++)
		{
			if(arr[i][j]!=' ')
				cout << arr[i][j];
		}
		cout << endl;
	}
}