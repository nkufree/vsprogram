#include<iostream>
using namespace std;
char name[10000][20] = {};
char sex[10000];
int score[10000];
char c[10000][20] = {};

void strcpy(int x,int i)
{
	for (int j = 0; j < 20; j++)
		c[x][j] = name[i][j];
}

bool f(int j, int k)
{
	int i = 0;
	while (c[j][i] != '\0' && c[k][i] != '\0')
	{
		if (c[j][i] == c[k][i])
			i++;
		else if (c[j][i] > c[k][i])
			return 0;
		else if (c[j][i] < c[k][i])
			return 1;
	}
	if (c[j][i] == '\0')
		return 1;
	else
		return 0;
}

void swapstr(int j, int k)
{
	char b[20] = {};
	for (int i = 0; i < 20; i++)
		b[i] = name[j][i];
	for (int i = 0; i < 20; i++)
		name[j][i] = name[j - 1][i];
	for (int i = 0; i < 20; i++)
		name[j - 1][i] = b[i];
}
void swapstrc(int j, int k)
{
	char b[20] = {};
	for (int i = 0; i < 20; i++)
		b[i] = c[j][i];
	for (int i = 0; i < 20; i++)
		c[j][i] = c[k][i];
	for (int i = 0; i < 20; i++)
		c[k][i] = b[i];
}

int main()
{
	int n, m, k, x = 0, male = 0;
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
		cin >> name[i] >> sex[i] >> score[i];
	for (int i = 0; i < n; i++)
	{
		for (int j = n-1; j > i; j--)
		{
			if (score[j] > score[j - 1])
			{
				int temp = score[j];
				score[j] = score[j - 1];
				score[j - 1] = temp;
				swapstr(j, j - 1);
				char temp1 = sex[j];
				sex[j] = sex[j - 1];
				sex[j - 1] = temp1;
			}
		}
	}
	for (int i = 0; i < n; i++)
		cout << name[i] << " " << sex[i] << " " << score[i] << endl;
	//³É¼¨ÅÅÐò
	int i;
	for (i = 0; i < n && x != k; i++)
	{
 		if (sex[i] == 'F')
		{
			strcpy(x, i);
			x++;
		}
	}
	if (i != n)
	{
		for (int j = i;j < n && score[j] == score[i - 1]; j++)
		{
			if (sex[j] == 'F')
			{
				strcpy(x, j);
				x++;
			}
		}
	}
	int j = 0;
	if (x < m)
	{
		for (j = 0; x + male < n && male < m - x; j++)
		{ 
			if (sex[j] == 'M')
			{
				strcpy(x + male, j);
				male++;
			}
		}
		for (k = j; k<n && score[k] == score[j - 1]; k++)
		{
			if (sex[k] == 'M')
			{
				strcpy(x + male, k);
				male++;
			}
		}
	}
	for (k = 0; k < x + male; k++)
	{
		for (int l = x + male - 1; l > k; l--)
		{
			if (f(l, l - 1) == 1)
				swapstrc(l, l - 1);
		}
	}
	for (k = 0; k < x + male; k++)
		cout << c[k] <<endl;
}