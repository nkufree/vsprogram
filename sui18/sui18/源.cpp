#include<iostream>
#include<iomanip>
using namespace std;
char words[50][101] = {};
bool f(int i, int j)
{
	int k,lengthi,lengthj;
	for (lengthi = 0; words[i][lengthi] != '\0'; lengthi++);
	for (lengthj = 0; words[j][lengthj] != '\0'; lengthj++);
	if (lengthi != lengthj)
		return 0;
	for (k = 0; words[i][k] != '\0'; k++)
	{
		if (words[i][k] != words[j][k])
			return 0;
	}
	return 1;
}

int main()
{
	char str[101] = {};
	cin.getline(str, 101);
	for (int i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] > 'Z' && str[i] < 'a') || str[i] < 'A' || str[i] > 'z')
			str[i] = ' ';
		else if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 32;
	}
	int wordCNT = 0;

	int j = 0; 

	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] != ' ')
		{
			words[wordCNT][j] = str[i];
			j++;
		}
		else
		{
			if (i != 0 && str[i - 1] != ' ')
				wordCNT++;
			j = 0;
		}
	}
	cout << words[0];
	int cnt = 1;
	for (int i = 1; i <= wordCNT; i++)
	{
		int g = 0;
		for (int j = 0; j < i; j++)
		{
			if (f(i, j) == 1)
				g++;
		}
		if (g == 0&&words[i][0]!='\0')
		{
			cout << " "  << words[i];
			cnt++;
		}
	}
	cout << endl;
	cout << cnt;
}