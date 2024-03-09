#include<iostream>
using namespace std;

char a[51];
int length = 0;
void reverse()
{
	for (int i = 0; i < length; i++)
	{
		char b[51] = {};
		int j = 0;
		while (a[i] <= '9' && a[i + 1] <= '9'&&a[i+1]!='\0'&&a[i]!='\0')
		{
			j = 0;
			while (a[i] <= '9' && a[i] != '\0')
			{
				b[j++] = a[i++];
			}
			j--;
			i--;
			for (int k = 0; k <= j; k++)
				a[i - k] = b[k];
		}
	}

}

int main()
{
	cin >> a;
	int i = 0;
	while (a[i] != '\0')
	{
		length++;
		i++;
	}
	reverse();
	for (i = 0; i < length; i++)
		cout << a[i];
	return 0;
}